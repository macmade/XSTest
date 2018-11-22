/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2018 Jean-David Gadina - www.xs-labs.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        XSTestXCTestBridge.mm
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#import <XCTest/XCTest.h>
#import <XS/Test/Info.hpp>
#import <XS/Test/Suite.hpp>
#import <XS/Test/Case.hpp>
#import <objc/runtime.h>
#import <objc/message.h>

static id runTestCase( XCTestCase * self, SEL _cmd );

static std::vector< std::shared_ptr< XS::Test::Info > > * allInfos = nullptr;

@interface XSTestXCTestBridge: XCTestCase
{}

+ ( void )createAllTests;
+ ( void )createTestsSuite: ( const XS::Test::Suite & )suite;
+ ( void )addTestCase: ( const XS::Test::Info & )info toClass: ( Class )cls;

@end

@implementation XSTestXCTestBridge

+ ( void )initialize
{
    if( self != [ XSTestXCTestBridge self ] )
    {
        return;
    }
    
    [ self createAllTests ];
}

+ ( void )createAllTests
{
    allInfos = new std::vector< std::shared_ptr< XS::Test::Info > >();
    
    for( const auto & suite: XS::Test::Info::All() )
    {
        [ self createTestsSuite: suite ];
    }
}

+ ( void )createTestsSuite: ( const XS::Test::Suite & )suite
{
    Class cls;
    Class sup;
    
    sup = objc_getClass( "XCTestCase" );
    
    if( sup == nullptr )
    {
        return;
    }
    
    cls = objc_allocateClassPair( sup, suite.GetName().c_str(), 0 );
    
    if( cls == nullptr )
    {
        return;
    }
    
    for( const auto & info: suite.GetInfos() )
    {
        [ self addTestCase: info toClass: cls ];
    }
    
    objc_registerClassPair( cls );
}

+ ( void )addTestCase: ( const XS::Test::Info & )info toClass: ( Class )cls
{
    std::string                       name( "test." + info.GetName() );
    SEL                               sel;
    std::shared_ptr< XS::Test::Info > p;
    
    sel = sel_registerName( name.c_str() );
    
    if( sel == nullptr )
    {
        return;
    }
    
    p = std::make_shared< XS::Test::Info >( info );
    
    allInfos->push_back( p );
    class_addMethod( cls, sel, reinterpret_cast< IMP >( runTestCase ), "v@:" );
    objc_setAssociatedObject( cls, sel, ( __bridge id )( p.get() ), OBJC_ASSOCIATION_ASSIGN );
}

@end

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvariadic-macros"
#pragma clang diagnostic ignored "-Wgnu-statement-expression"
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif

static id runTestCase( XCTestCase * self, SEL _cmd )
{
    void * assoc;
    
    assoc = ( __bridge void * )objc_getAssociatedObject( [ self class ], _cmd );
    
    if( assoc == nullptr )
    {
        return nullptr;
    }
    
    {
        XS::Test::Info & info( *( static_cast< XS::Test::Info * >( assoc ) ) );
        
        if( info.Run( {} ) == false )
        {
            [ self recordFailureWithDescription: @"Failure" inFile: [ NSString stringWithUTF8String: info.GetFile().c_str() ] atLine: static_cast< NSUInteger >( info.GetLine() ) expected: YES ];
        }
    }
    
    return nullptr;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
