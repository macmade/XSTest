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
 * @file        XSTestAssertEqual.cpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#include <XSTest/XSTest.hpp>
#include <thread>
#include <chrono>

XSTest( Success, XSTestAssertEqual_Int )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertEqual( 0, 0 );
}

XSTest( Failure, XSTestAssertEqual_Int )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertEqual( 0, 1 );
}

XSTest( Success, XSTestAssertNotEqual_Int )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertNotEqual( 0, 1 );
}

XSTest( Failure, XSTestAssertNotEqual_Int )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertNotEqual( 0, 0 );
}

XSTest( Success, XSTestAssertEqual_String )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertEqual( std::string( "foo" ), std::string( "foo" ) );
}

XSTest( Failure, XSTestAssertEqual_String )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertEqual( std::string( "foo" ), std::string( "bar" ) );
}

XSTest( Success, XSTestAssertNotEqual_String )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertNotEqual( std::string( "foo" ), std::string( "bar" ) );
}

XSTest( Failure, XSTestAssertNotEqual_String )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
    
    XSTestAssertNotEqual( std::string( "foo" ), std::string( "foo" ) );
}