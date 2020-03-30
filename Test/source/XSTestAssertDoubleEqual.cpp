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
 * @file        XSTestAssertDoubleEqual.cpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#include <XSTest/XSTest.hpp>
#include <thread>
#include <chrono>

XSTest( Success, XSTestAssertDoubleEqual )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertDoubleEqual( 0.1, 0.1 );
}

XSTest( Success, XSTestAssertFloatNotEqual )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertDoubleNotEqual( 0.1, 0.2 );
}

XSTest( Success, XSTestAssertDoubleEqual_NextAfter )
{
    double  f1( static_cast< double >( 0.1 ) );
    double  f2( std::nextafter( f1, static_cast< double >( 0.2 ) ) );
    double  f3( std::nextafter( f1, static_cast< double >( 0.0 ) ) );
    int64_t i1( *( reinterpret_cast< int64_t * >( &f1 ) ) );
    int64_t i2( *( reinterpret_cast< int64_t * >( &f2 ) ) );
    int64_t i3( *( reinterpret_cast< int64_t * >( &f3 ) ) );
    
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertNotEqual( i1, i2 );
    XSTestAssertNotEqual( i1, i3 );
    XSTestAssertNotEqual( i2, i3 );
    
    XSTestAssertDoubleEqual( f1, f2 );
    XSTestAssertDoubleEqual( f1, f3 );
}

XSTest( Success, XSTestAssertDoubleEqual_NextToward )
{
    double  f1( static_cast< double >( 0.1 ) );
    double  f2( std::nexttoward( f1, static_cast< long double >( 0.2 ) ) );
    double  f3( std::nexttoward( f1, static_cast< long double >( 0.0 ) ) );
    int64_t i1( *( reinterpret_cast< int64_t * >( &f1 ) ) );
    int64_t i2( *( reinterpret_cast< int64_t * >( &f2 ) ) );
    int64_t i3( *( reinterpret_cast< int64_t * >( &f3 ) ) );
    
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertNotEqual( i1, i2 );
    XSTestAssertNotEqual( i1, i3 );
    XSTestAssertNotEqual( i2, i3 );
    
    XSTestAssertDoubleEqual( f1, f2 );
    XSTestAssertDoubleEqual( f1, f3 );
}

XSTest( Success, XSTestAssertDoubleEqual_INF )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertDoubleEqual( std::numeric_limits< double >::infinity(), std::numeric_limits< double >::infinity() );
}

XSTest( Failure, XSTestAssertFloatNotEqual )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertDoubleNotEqual( static_cast< double >( 0.1 ), static_cast< double >( 0.1 ) );
}

XSTest( Failure, XSTestAssertDoubleEqual_NAN )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertDoubleEqual( std::numeric_limits< double >::quiet_NaN(), std::numeric_limits< double >::quiet_NaN() );
}

XSTest( Failure, XSTestAssertDoubleEqual_Sign )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertDoubleEqual( 0.1, -0.1 );
}

XSTest( Failure, XSTestAssertDoubleEqual_Epsilon )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertDoubleEqual( 0.1, 0.1 + std::numeric_limits< double >::epsilon() );
}
