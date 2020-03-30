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
 * @file        XSTestAssertFloatEqual.cpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#include <XSTest/XSTest.hpp>
#include <thread>
#include <chrono>

XSTest( Success, XSTestAssertFloatEqual )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertFloatEqual( 0.1, 0.1 );
}

XSTest( Success, XSTestAssertFloatNotEqual )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertFloatNotEqual( 0.1, 0.2 );
}

XSTest( Success, XSTestAssertFloatEqual_NextAfter )
{
    float   f1( static_cast< float >( 0.1 ) );
    float   f2( std::nextafter( f1, static_cast< float >( 0.2 ) ) );
    float   f3( std::nextafter( f1, static_cast< float >( 0.0 ) ) );
    int32_t i1( *( reinterpret_cast< int32_t * >( &f1 ) ) );
    int32_t i2( *( reinterpret_cast< int32_t * >( &f2 ) ) );
    int32_t i3( *( reinterpret_cast< int32_t * >( &f3 ) ) );
    
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertNotEqual( i1, i2 );
    XSTestAssertNotEqual( i1, i3 );
    XSTestAssertNotEqual( i2, i3 );
    
    XSTestAssertFloatEqual( f1, f2 );
    XSTestAssertFloatEqual( f1, f3 );
}

XSTest( Success, XSTestAssertFloatEqual_NextToward )
{
    float   f1( static_cast< float >( 0.1 ) );
    float   f2( std::nexttowardf( f1, static_cast< long double >( 0.2 ) ) );
    float   f3( std::nexttowardf( f1, static_cast< long double >( 0.0 ) ) );
    int32_t i1( *( reinterpret_cast< int32_t * >( &f1 ) ) );
    int32_t i2( *( reinterpret_cast< int32_t * >( &f2 ) ) );
    int32_t i3( *( reinterpret_cast< int32_t * >( &f3 ) ) );
    
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertNotEqual( i1, i2 );
    XSTestAssertNotEqual( i1, i3 );
    XSTestAssertNotEqual( i2, i3 );
    
    XSTestAssertFloatEqual( f1, f2 );
    XSTestAssertFloatEqual( f1, f3 );
}

XSTest( Success, XSTestAssertFloatEqual_INF )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertFloatEqual( std::numeric_limits< float >::infinity(), std::numeric_limits< float >::infinity() );
}

XSTest( Failure, XSTestAssertFloatNotEqual )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertFloatNotEqual( static_cast< float >( 0.1 ), static_cast< float >( 0.1 ) );
}

XSTest( Failure, XSTestAssertFloatEqual_NAN )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertFloatEqual( std::numeric_limits< float >::quiet_NaN(), std::numeric_limits< float >::quiet_NaN() );
}

XSTest( Failure, XSTestAssertFloatEqual_Sign )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertFloatEqual( 0.1, -0.1 );
}

XSTest( Failure, XSTestAssertFloatEqual_Epsilon )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertFloatEqual( 0.1f, 0.1f + std::numeric_limits< float >::epsilon() );
}
