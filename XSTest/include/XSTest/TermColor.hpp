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
 * @header      TermColor.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_TERM_COLOR_HPP
#define XS_TEST_TERM_COLOR_HPP

#include <functional>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#ifndef _WIN32
#include <unistd.h>
#endif

namespace XS
{
    namespace Test
    {
        class TermColor
        {
            public:
                
                static TermColor None( void )
                {
                    #ifdef _WIN32
                    return { nullptr };
                    #else
                    return { []( std::ostream & os ) { os << "\033[00m"; } };
                    #endif
                }
                
                static TermColor Gray( void )
                {
                    #ifdef _WIN32
                    return { nullptr };
                    #else
                    return { []( std::ostream & os ) { os << "\033[30m"; } };
                    #endif
                }
                
                static TermColor Red( void )
                {
                    #ifdef _WIN32
                    return { nullptr };
                    #else
                    return { []( std::ostream & os ) { os << "\033[31m"; } };
                    #endif
                }
                
                static TermColor Green( void )
                {
                    #ifdef _WIN32
                    return { nullptr };
                    #else
                    return { []( std::ostream & os ) { os << "\033[32m"; } };
                    #endif
                }
                
                static TermColor Yellow( void )
                {
                    #ifdef _WIN32
                    return { nullptr };
                    #else
                    return { []( std::ostream & os ) { os << "\033[33m"; } };
                    #endif
                }
                
                static TermColor Blue( void )
                {
                    #ifdef _WIN32
                    return { nullptr };
                    #else
                    return { []( std::ostream & os ) { os << "\033[34m"; } };
                    #endif
                }
                
                static TermColor Magenta( void )
                {
                    #ifdef _WIN32
                    return { nullptr };
                    #else
                    return { []( std::ostream & os ) { os << "\033[35m"; } };
                    #endif
                }
                
                static TermColor Cyan( void )
                {
                    #ifdef _WIN32
                    return { nullptr };
                    #else
                    return { []( std::ostream & os ) { os << "\033[36m"; } };
                    #endif
                }
                
                static TermColor White( void )
                {
                    #ifdef _WIN32
                    return { nullptr };
                    #else
                    return { []( std::ostream & os ) { os << "\033[37m"; } };
                    #endif
                }
                
                TermColor( const TermColor & o ):
                    _f( o._f )
                {}
                
                TermColor( TermColor && o ) noexcept:
                    _f( std::move( o._f ) )
                {}
                
                ~TermColor( void )
                {}
                
                TermColor & operator =( TermColor o )
                {
                    swap( *( this ), o );
                    
                    return *( this );
                }
                
                friend void swap( TermColor & o1, TermColor & o2 ) noexcept
                {
                    using std::swap;
                    
                    swap( o1._f, o2._f );
                }
                
                friend std::ostream & operator <<( std::ostream & os, const TermColor & color )
                {
                    if( IsTerm( os ) && color._f != nullptr )
                    {
                        color._f( os );
                    }
                    
                    return os;
                }
                
            private:
                
                static bool IsTerm( std::ostream & os )
                {
                    #ifdef _WIN32
                    
                    return false;
                    
                    #else
                    
                    if( getenv( "TERM" ) == nullptr )
                    {
                        return false;
                    }
                    
                    if( std::addressof( os ) == std::addressof( std::cout ) )
                    {
                        return isatty( fileno( stdout ) );
                    }
                    else if( std::addressof( os ) == std::addressof( std::cerr ) )
                    {
                        return isatty( fileno( stderr ) );
                    }
                    
                    return false;
                    
                    #endif
                }
                
                TermColor( const std::function< void( std::ostream & ) > & f ):
                    _f( f )
                {}
                
                std::function< void( std::ostream & ) > _f;
        };
    }
}

#endif /* XS_TEST_TERM_COLOR_HPP */
