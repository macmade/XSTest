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
#include <sstream>
#include <cstring>
#include <stdexcept>
#include <functional>
#include <type_traits>
#include <XSTest/Failure.hpp>

namespace XS
{
    namespace Test
    {
        namespace Assert
        {
            enum class Operator
            {
                Equal,
                NotEqual,
                Less,
                LessOrEqual,
                Greater,
                GreaterOrEqual
            };
            
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
            
            inline void Boolean( bool value, bool expected, const std::string & expression, const std::string & evaluated, const std::string & file, size_t line )
            {
                if( value != expected )
                {
                    throw Failure
                    (
                        expression,
                        evaluated,
                        ( expected ) ? "True" : "False",
                        ( value    ) ? "True" : "False",
                        file,
                        line
                    );
                } 
            }
            
            template< typename T1, typename T2 >
            inline auto Compare( const T1 & v1, const T2 & v2, Operator op, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if
                   <
                           ( std::is_integral< T1 >::value       && std::is_integral< T2 >::value )
                        || ( std::is_floating_point< T1 >::value && std::is_floating_point< T2 >::value )
                   >
                   ::type
            {
                if( op == Operator::Equal )
                {
                    Boolean( v1 == v2, true, expression1 + " == " + expression2, std::to_string( v1 ) + " == " + std::to_string( v2 ), file, line );
                }
                else if( op == Operator::NotEqual )
                {
                    Boolean( v1 != v2, true, expression1 + " != " + expression2, std::to_string( v1 ) + " != " + std::to_string( v2 ), file, line );
                }
                else if( op == Operator::Less )
                {
                    Boolean( v1 < v2, true, expression1 + " < " + expression2, std::to_string( v1 ) + " < " + std::to_string( v2 ), file, line );
                }
                else if( op == Operator::LessOrEqual )
                {
                    Boolean( v1 <= v2, true, expression1 + " <= " + expression2, std::to_string( v1 ) + " <= " + std::to_string( v2 ), file, line );
                }
                else if( op == Operator::Greater )
                {
                    Boolean( v1 > v2, true, expression1 + " > " + expression2, std::to_string( v1 ) + " > " + std::to_string( v2 ), file, line );
                }
                else if( op == Operator::GreaterOrEqual )
                {
                    Boolean( v1 >= v2, true, expression1 + " >= " + expression2, std::to_string( v1 ) + " >= " + std::to_string( v2 ), file, line );
                }
            }
            
            template< typename T1, typename T2 >
            inline auto Compare( const T1 & v1, const T2 & v2, Operator op, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if< ( std::is_same< T1, std::string >::value && std::is_same< T2, std::string >::value ) > ::type
            {
                if( op == Operator::Equal )
                {
                    Boolean( v1 == v2, true, expression1 + " == " + expression2, "\"" + v1 + "\" == \"" + v2 + "\"", file, line );
                }
                else if( op == Operator::NotEqual )
                {
                    Boolean( v1 != v2, true, expression1 + " != " + expression2, "\"" + v1 + "\" != \"" + v2 + "\"", file, line );
                }
                else if( op == Operator::Less )
                {
                    Boolean( v1 < v2, true, expression1 + " < " + expression2, "\"" + v1 + "\" < \"" + v2 + "\"", file, line );
                }
                else if( op == Operator::LessOrEqual )
                {
                    Boolean( v1 <= v2, true, expression1 + " <= " + expression2, "\"" + v1 + "\" <= \"" + v2 + "\"", file, line );
                }
                else if( op == Operator::Greater )
                {
                    Boolean( v1 > v2, true, expression1 + " > " + expression2, "\"" + v1 + " \"> \"" + v2 + "\"", file, line );
                }
                else if( op == Operator::GreaterOrEqual )
                {
                    Boolean( v1 >= v2, true, expression1 + " >= " + expression2, "\"" + v1 + "\" >= \"" + v2 + "\"", file, line );
                }
            }
            
            template< typename T1, typename T2 >
            inline auto Compare( const T1 & v1, const T2 & v2, Operator op, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if
                   <
                          ( !std::is_integral< T1 >::value          || !std::is_integral< T2 >::value )
                       && ( !std::is_floating_point< T1 >::value    || !std::is_floating_point< T2 >::value )
                       && ( !std::is_same< T1, std::string >::value || !std::is_same< T2, std::string >::value )
                   >
                   ::type
            {
                if( op == Operator::Equal )
                {
                    Boolean( v1 == v2, true, expression1 + " == " + expression2, file, line );
                }
                else if( op == Operator::NotEqual )
                {
                    Boolean( v1 != v2, true, expression1 + " != " + expression2, file, line );
                }
                else if( op == Operator::Less )
                {
                    Boolean( v1 < v2, true, expression1 + " < " + expression2, file, line );
                }
                else if( op == Operator::LessOrEqual )
                {
                    Boolean( v1 <= v2, true, expression1 + " <= " + expression2, file, line );
                }
                else if( op == Operator::Greater )
                {
                    Boolean( v1 > v2, true, expression1 + " > " + expression2, file, line );
                }
                else if( op == Operator::GreaterOrEqual )
                {
                    Boolean( v1 >= v2, true, expression1 + " >= " + expression2, file, line );
                }
            }
            
            inline void StringEquality( const char * cp1, const char * cp2, bool expected, bool caseInsensitive, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
            {
                bool result;
                
                if( cp1 == nullptr || cp2 == nullptr )
                {
                    result = ( expected ) ? false : true;
                }
                else if( caseInsensitive )
                {
                    result = strcasecmp( cp1, cp2 ) == 0;
                }
                else
                {
                    result = strcmp( cp1, cp2 ) == 0;
                }
                
                if( result != expected )
                {
                    {
                        std::string s1( ( cp1 == nullptr ) ? "NULL" : "\"" + std::string( cp1 ) + "\"" );
                        std::string s2( ( cp2 == nullptr ) ? "NULL" : "\"" + std::string( cp2 ) + "\"" );
                        std::string expression( ( expected ) ? expression1 + " == " + expression2 : expression1 + " != " + expression2 );
                        std::string evaluated(  ( expected ) ? s1          + " == " + s2          : s1          + " != " + s2 );
                        
                        Boolean( result, expected, expression, evaluated, file, line );
                    }
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
