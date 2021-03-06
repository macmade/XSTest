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
 * @header      Utility.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_UTILITY_HPP
#define XS_TEST_UTILITY_HPP

#include <string>
#include <random>

#ifdef __clang__
#include <cxxabi.h>
#endif

namespace XS
{
    namespace Test
    {
        namespace Utility
        {
            inline std::string Numbered( const std::string & s, size_t count, const std::string & plural )
            {
                if( count == 1 )
                {
                    return std::to_string( count ) + " " + s;
                }
                
                return std::to_string( count ) + " " + plural;
            }
            
            inline std::string Numbered( const std::string & s, size_t count )
            {
                return Numbered( s, count, s + "s" );
            }
            
            template< typename _T_ >
            void Shuffle( _T_ & o )
            {
                std::random_device rng;
                std::mt19937       urng( rng() );
                
                std::shuffle( std::begin( o ), std::end( o ), urng );
            }
            
            template< typename _T_ >
            std::string Typename( const _T_ & o )
            {
                std::string name( typeid( o ).name() );
                
                #ifdef __clang__
                {
                    int s( 0 );
                    
                    name = abi::__cxa_demangle( name.c_str(), nullptr, nullptr, &s );
                }
                #endif
                
                return name;
            }
        }
    }
}

#endif /* XS_TEST_UTILITY_HPP */
