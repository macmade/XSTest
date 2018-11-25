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
 * @header      Assert.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_ASSERT_HPP
#define XS_TEST_ASSERT_HPP

#include <string>
#include <XSTest/Failure.hpp>
#include <sstream>
#include <cstring>
#include <stdexcept>
#include <functional>

namespace XS
{
    namespace Test
    {
        namespace Assert
        {
            inline void Boolean( bool value, bool expected, const std::string & expression, const std::string & file, size_t line )
            {
                if( value != expected )
                {
                    throw Failure
                    (
                        expression,
                        ( expected ) ? "True" : "False",
                        ( value    ) ? "True" : "False",
                        file,
                        line
                    );
                } 
            }
            
            template< typename T1, typename T2 >
            inline void Equality( const T1 & v1, const T2 & v2, bool expected, const std::string & expression, const std::string & file, size_t line )
            {
                if( ( v1 == v2 ) != expected )
                {
                    throw Failure
                    (
                        expression,
                        ( expected ) ? "Equal"     : "Not equal",
                        ( expected ) ? "Not equal" : "Equal",
                        file,
                        line
                    );
                }
            }
            
            inline void StringEquality( const char * s1, const char * s2, bool expected, bool caseInsensitive, const std::string & expression, const std::string & file, size_t line )
            {
                bool result;
                
                if( s1 == nullptr || s2 == nullptr )
                {
                    result = ( expected ) ? false : true;
                }
                else if( caseInsensitive )
                {
                    result = strcasecmp( s1, s2 ) == 0;
                }
                else
                {
                    result = strcmp( s1, s2 ) == 0;
                }
                
                if( result != expected )
                {
                    throw Failure
                    (
                        expression,
                        ( expected ) ? "Equal"     : "Not equal",
                        ( expected ) ? "Not equal" : "Equal",
                        file,
                        line
                    );
                }
            }
            
            template< typename T >
            inline void Throwing( const std::function< void( void ) > & f, const std::string & exception, const std::string & expression, const std::string & file, size_t line )
            {
                bool hasCaught( false );
                bool hasThrown( false );
                
                try
                {
                    if( f != nullptr )
                    {
                        f();
                    }
                }
                catch( const T & e )
                {
                    hasCaught = true;
                    hasThrown = true;
                }
                catch( ... )
                {
                    hasThrown = true;
                }
                
                if( hasThrown == false || hasCaught == false )
                {
                    throw Failure
                    (
                        expression,
                        "Throws " + exception,
                        ( hasThrown == false ) ? "Doesn't throw anything" : "Throws a different exception",
                        file,
                        line
                    );
                }
            }
            
            inline void Throwing( const std::function< void( void ) > & f, bool throws, const std::string & expression, const std::string & file, size_t line )
            {
                bool hasThrown( false );
                
                try
                {
                    if( f != nullptr )
                    {
                        f();
                    }
                }
                catch( ... )
                {
                    hasThrown = true;
                }
                
                if( hasThrown != throws )
                {
                    throw Failure
                    (
                        expression,
                        ( throws ) ? "Throws an exception"    : "Doesn't throw any exception",
                        ( throws ) ? "Doesn't throw anything" : "Throws an exception",
                        file,
                        line
                    );
                }
            }
        }
    }
}

#endif /* XS_TEST_ASSERT_HPP */
