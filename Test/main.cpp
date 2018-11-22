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
 * @file        Info.cpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#include <XS/Test.hpp>
#include <iostream>
#include <thread>

XS_TEST( Foo, Test1 )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
}

XS_TEST( Foo, Test2 )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 1010 ) );
}

XS_TEST( Foo, Test3 )
{
    throw std::runtime_error( "Failure" );
}

XS_TEST( Foo, Test4 )
{}

XS_TEST( Foo, Test5 )
{}

XS_TEST( Bar, Test1 )
{}

XS_TEST( Bar, Test2 )
{}

XS_TEST( Bar, Test3 )
{}

XS_TEST( Bar, Test4 )
{}

XS_TEST( Bar, Test5 )
{}

int main( void )
{
    return XS::Test::RunAll();
}
