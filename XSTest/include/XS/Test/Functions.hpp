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
 * @header      Functions.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_FUNCTIONS_HPP
#define XS_TEST_FUNCTIONS_HPP

#include <iostream>
#include <XS/Test/Optional.hpp>
#include <XS/Test/Runner.hpp>
#include <XS/Test/Info.hpp>
#include <XS/Test/Suite.hpp>

namespace XS
{
    namespace Test
    {
        inline int RunAll( Optional< std::reference_wrapper< std::ostream > > os = { std::cout } )
        {
            Runner runner( Suite::All() );
            
            return ( runner.Run( os ) ) ? 0 : -1;
        }
    }
}

#ifdef XS_TEST_MAIN

int main( void )
{
    return XS::Test::RunAll();
}

#endif

#endif /* XS_TEST_FUNCTIONS_HPP */
