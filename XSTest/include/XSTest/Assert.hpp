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
#include <XSTest/Utility.hpp>
#include <XSTest/FloatingPoint.hpp>

#ifdef _WIN32
#include <winerror.h>
#endif

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
            
            template< typename _T_, typename _U_ >
            inline auto CompareEqual( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if
                   <
                           ( std::is_integral< _T_ >::value       && std::is_integral< _U_ >::value )
                        || ( std::is_floating_point< _T_ >::value && std::is_floating_point< _U_ >::value )
                   >
                   ::type
            {
                Boolean( v1 == v2, true, expression1 + " == " + expression2, std::to_string( v1 ) + " == " + std::to_string( v2 ), file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareNotEqual( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if
                   <
                           ( std::is_integral< _T_ >::value       && std::is_integral< _U_ >::value )
                        || ( std::is_floating_point< _T_ >::value && std::is_floating_point< _U_ >::value )
                   >
                   ::type
            {
                Boolean( v1 != v2, true, expression1 + " != " + expression2, std::to_string( v1 ) + " != " + std::to_string( v2 ), file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareLess( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if
                   <
                           ( std::is_integral< _T_ >::value       && std::is_integral< _U_ >::value )
                        || ( std::is_floating_point< _T_ >::value && std::is_floating_point< _U_ >::value )
                   >
                   ::type
            {
                Boolean( v1 < v2, true, expression1 + " < " + expression2, std::to_string( v1 ) + " < " + std::to_string( v2 ), file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareLessOrEqual( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if
                   <
                           ( std::is_integral< _T_ >::value       && std::is_integral< _U_ >::value )
                        || ( std::is_floating_point< _T_ >::value && std::is_floating_point< _U_ >::value )
                   >
                   ::type
            {
                Boolean( v1 <= v2, true, expression1 + " <= " + expression2, std::to_string( v1 ) + " <= " + std::to_string( v2 ), file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareGreater( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if
                   <
                           ( std::is_integral< _T_ >::value       && std::is_integral< _U_ >::value )
                        || ( std::is_floating_point< _T_ >::value && std::is_floating_point< _U_ >::value )
                   >
                   ::type
            {
                Boolean( v1 > v2, true, expression1 + " > " + expression2, std::to_string( v1 ) + " > " + std::to_string( v2 ), file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareGreaterOrEqual( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if
                   <
                           ( std::is_integral< _T_ >::value       && std::is_integral< _U_ >::value )
                        || ( std::is_floating_point< _T_ >::value && std::is_floating_point< _U_ >::value )
                   >
                   ::type
            {
                Boolean( v1 >= v2, true, expression1 + " >= " + expression2, std::to_string( v1 ) + " >= " + std::to_string( v2 ), file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareEqual( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if< ( std::is_same< _T_, std::string >::value && std::is_same< _U_, std::string >::value ) > ::type
            {
                Boolean( v1 == v2, true, expression1 + " == " + expression2, "\"" + v1 + "\" == \"" + v2 + "\"", file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareNotEqual( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if< ( std::is_same< _T_, std::string >::value && std::is_same< _U_, std::string >::value ) > ::type
            {
                Boolean( v1 != v2, true, expression1 + " != " + expression2, "\"" + v1 + "\" != \"" + v2 + "\"", file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareLess( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if< ( std::is_same< _T_, std::string >::value && std::is_same< _U_, std::string >::value ) > ::type
            {
                Boolean( v1 < v2, true, expression1 + " < " + expression2, "\"" + v1 + "\" < \"" + v2 + "\"", file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareLessOrEqual( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if< ( std::is_same< _T_, std::string >::value && std::is_same< _U_, std::string >::value ) > ::type
            {
                Boolean( v1 <= v2, true, expression1 + " <= " + expression2, "\"" + v1 + "\" <= \"" + v2 + "\"", file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareGreater( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if< ( std::is_same< _T_, std::string >::value && std::is_same< _U_, std::string >::value ) > ::type
            {
                Boolean( v1 > v2, true, expression1 + " > " + expression2, "\"" + v1 + " \"> \"" + v2 + "\"", file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareGreaterOrEqual( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if< ( std::is_same< _T_, std::string >::value && std::is_same< _U_, std::string >::value ) > ::type
            {
                Boolean( v1 >= v2, true, expression1 + " >= " + expression2, "\"" + v1 + "\" >= \"" + v2 + "\"", file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareEqual( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if
                   <
                          ( !std::is_integral< _T_ >::value          || !std::is_integral< _U_ >::value )
                       && ( !std::is_floating_point< _T_ >::value    || !std::is_floating_point< _U_ >::value )
                       && ( !std::is_same< _T_, std::string >::value || !std::is_same< _U_, std::string >::value )
                   >
                   ::type
            {
                Boolean( v1 == v2, true, expression1 + " == " + expression2, file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareNotEqual( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if
                   <
                          ( !std::is_integral< _T_ >::value          || !std::is_integral< _U_ >::value )
                       && ( !std::is_floating_point< _T_ >::value    || !std::is_floating_point< _U_ >::value )
                       && ( !std::is_same< _T_, std::string >::value || !std::is_same< _U_, std::string >::value )
                   >
                   ::type
            {
                Boolean( v1 != v2, true, expression1 + " != " + expression2, file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareLess( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if
                   <
                          ( !std::is_integral< _T_ >::value          || !std::is_integral< _U_ >::value )
                       && ( !std::is_floating_point< _T_ >::value    || !std::is_floating_point< _U_ >::value )
                       && ( !std::is_same< _T_, std::string >::value || !std::is_same< _U_, std::string >::value )
                   >
                   ::type
            {
                Boolean( v1 < v2, true, expression1 + " < " + expression2, file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareLessOrEqual( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if
                   <
                          ( !std::is_integral< _T_ >::value          || !std::is_integral< _U_ >::value )
                       && ( !std::is_floating_point< _T_ >::value    || !std::is_floating_point< _U_ >::value )
                       && ( !std::is_same< _T_, std::string >::value || !std::is_same< _U_, std::string >::value )
                   >
                   ::type
            {
                Boolean( v1 <= v2, true, expression1 + " <= " + expression2, file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareGreater( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if
                   <
                          ( !std::is_integral< _T_ >::value          || !std::is_integral< _U_ >::value )
                       && ( !std::is_floating_point< _T_ >::value    || !std::is_floating_point< _U_ >::value )
                       && ( !std::is_same< _T_, std::string >::value || !std::is_same< _U_, std::string >::value )
                   >
                   ::type
            {
                Boolean( v1 > v2, true, expression1 + " > " + expression2, file, line );
            }
            
            template< typename _T_, typename _U_ >
            inline auto CompareGreaterOrEqual( const _T_ & v1, const _U_ & v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if
                   <
                          ( !std::is_integral< _T_ >::value          || !std::is_integral< _U_ >::value )
                       && ( !std::is_floating_point< _T_ >::value    || !std::is_floating_point< _U_ >::value )
                       && ( !std::is_same< _T_, std::string >::value || !std::is_same< _U_, std::string >::value )
                   >
                   ::type
            {
                Boolean( v1 >= v2, true, expression1 + " >= " + expression2, file, line );
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
                    #ifdef _WIN32
                    result = _stricmp( cp1, cp2 ) == 0;
                    #else
                    result = strcasecmp( cp1, cp2 ) == 0;
                    #endif
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
            
            template< typename _T_ >
            inline auto Throwing( const std::function< void( void ) > & f, const std::string & exception, const std::string & expression, const std::string & file, size_t line )
                -> typename std::enable_if< !std::is_base_of< std::exception, _T_ >::value || !std::is_same< std::exception, _T_ >::value >::type
            {
                bool        hasCaught( false );
                bool        hasThrown( false );
                std::string thrown;
                std::string what;
                
                try
                {
                    if( f != nullptr )
                    {
                        f();
                    }
                }
                catch( const _T_ & e )
                {
                    ( void )e;

                    hasCaught = true;
                    hasThrown = true;
                }
                catch( const std::exception & e )
                {
                    hasThrown = true;
                    what      = ( e.what() != nullptr ) ? e.what() : "";
                    thrown    = Utility::Typename( e ) + ( ( what.length() > 0 ) ? ": \"" + what + "\"" : "" );
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
                        ( hasThrown == false ) ? "Doesn't throw anything" : ( ( thrown.length() == 0 ) ? "Throws a different exception" : "Throws " + thrown ),
                        file,
                        line
                    );
                }
            }
            
            template< typename _T_ >
            inline auto Throwing( const std::function< void( void ) > & f, const std::string & exception, const std::string & expression, const std::string & file, size_t line )
                -> typename std::enable_if< !( !std::is_base_of< std::exception, _T_ >::value || !std::is_same< std::exception, _T_ >::value ) >::type
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
                catch( const _T_ & e )
                {
                    ( void )e;

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
                bool        hasThrown( false );
                std::string thrown;
                std::string what;
                
                try
                {
                    if( f != nullptr )
                    {
                        f();
                    }
                }
                catch( const std::exception & e )
                {
                    hasThrown = true;
                    what      = ( e.what() != nullptr ) ? e.what() : "";
                    thrown    = Utility::Typename( e ) + ( ( what.length() > 0 ) ? ": \"" + what + "\"" : "" );
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
                        ( throws ) ? "Doesn't throw anything" : ( ( thrown.length() == 0 ) ? "Throws an exception" : "Throws " + thrown ),
                        file,
                        line
                    );
                }
            }
            
            template< typename _T_ >
            inline auto Compare( _T_ v1, _T_ v2, const std::string & expression1, const std::string & expression2, const std::string & file, size_t line )
                -> typename std::enable_if< std::is_same< _T_, float >::value || std::is_same< _T_, double >::value >::type
            {
                FloatingPoint< _T_ > fp1( v1 );
                FloatingPoint< _T_ > fp2( v2 );
                
                if( fp1 != fp2 )
                {
                    throw Failure
                    (
                        expression1 + " == " + expression2,
                        std::to_string( v1 ) + " == " + std::to_string( v2 ),
                        "True",
                        "False",
                        file,
                        line
                    );
                }
            }
            
            #ifdef _WIN32
            inline void HResult( HRESULT hr, bool expected, const std::string & expression, const std::string & file, size_t line )
            {
                bool result( ( expected == true && SUCCEEDED( hr ) ) || ( expected == false && FAILED( hr ) ) );
                
                Boolean( result, expected, expression, std::to_string( hr ), file, line );
            }
            #endif
        }
    }
}

#endif /* XS_TEST_ASSERT_HPP */
