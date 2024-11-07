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

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#import <XCTest/XCTest.h>
#ifdef __clang__
#pragma clang diagnostic pop
#endif

#import <XSTest/XSTest.hpp>
#import <objc/message.h>

static id runTestCase( XCTestCase * self, SEL _cmd );

static std::vector< std::shared_ptr< XS::Test::Info > > * allInfos = nullptr;

@interface XSTestXCTestBridge: XCTestCase
{}

+ ( void )createAllTests;
+ ( void )createTestSuite: ( const XS::Test::Suite & )suite;
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
    
    for( const auto & suite: XS::Test::Suite::All( { 0, nullptr } ) )
    {
        [ self createTestSuite: suite ];
    }
}

+ ( void )createTestSuite: ( const XS::Test::Suite & )suite
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
    std::string                       name( "test_" + info.GetCaseName() );
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
        XS::Test::Info                        & info( *( static_cast< XS::Test::Info * >( assoc ) ) );
        XS::Test::Optional< XS::Test::Failure > failure;
        std::string                             file;
        size_t                                  line;
        
        if( info.Run( {} ) == false )
        {
            failure = info.GetFailure();
            
            if( failure )
            {
                file = failure->GetFile();
                line = failure->GetLine();
            }
            else
            {
                file = info.GetFile();
                line = info.GetLine();
            }
            
            {
                NSString * objcDescription = [ NSString stringWithUTF8String: failure->GetDescription().c_str() ];
                NSString * objcFile        = [ NSString stringWithUTF8String: file.c_str() ];
                
                if( objcDescription != nil && objcFile != nil )
                {
                    #if defined( XCODE_VERSION_MAJOR ) && XCODE_VERSION_MAJOR >= 1200
                    
                    XCTSourceCodeLocation * location = [ [ XCTSourceCodeLocation alloc ] initWithFilePath: objcFile lineNumber: static_cast< NSInteger >( line ) ];
                    XCTSourceCodeContext  * context  = [ [ XCTSourceCodeContext alloc ] initWithLocation: location ];
                    
                    [ self recordIssue: [ [ XCTIssue alloc ] initWithType: XCTIssueTypeAssertionFailure compactDescription: objcDescription detailedDescription: nil sourceCodeContext: context associatedError: nil attachments: @[] ] ];
                    
                    #else
                    
                    [ self recordFailureWithDescription: objcDescription inFile: objcFile atLine: line expected: YES ];
                    
                    #endif
                }
            }
        }
    }
    
    return nullptr;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

namespace XS
{
    namespace Test
    {
        XS_TEST_GET_ALL_INFOS_DECLARATION
        XS_TEST_GET_ALL_INFOS_DEFINITION
    }
}
