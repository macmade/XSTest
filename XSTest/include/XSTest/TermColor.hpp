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
#include <XSTest/Optional.hpp>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

namespace XS
{
    namespace Test
    {
        class TermColor
        {
            public:
                
                enum class Foreground
                {
                    None,
                    Gray,
                    Red,
                    Green,
                    Yellow,
                    Blue,
                    Magenta,
                    Cyan,
                    White
                };

                static TermColor None()
                {
                    return Foreground::None;
                }
                
                static TermColor Gray()
                {
                    return Foreground::Gray;
                }
                
                static TermColor Red()
                {
                    return Foreground::Red;
                }
                
                static TermColor Green()
                {
                    return Foreground::Green;
                }
                
                static TermColor Yellow()
                {
                    return Foreground::Yellow;
                }
                
                static TermColor Blue()
                {
                    return Foreground::Blue;
                }
                
                static TermColor Magenta()
                {
                    return Foreground::Magenta;
                }
                
                static TermColor Cyan()
                {
                    return Foreground::Cyan;
                }
                
                static TermColor White()
                {
                    return Foreground::White;
                }

                TermColor( Foreground foreground ):
                    _foreground( foreground )
                {}
                
                TermColor( const TermColor & o ):
                    _foreground( o._foreground )
                {}
                
                TermColor( TermColor && o ) noexcept:
                    _foreground( std::move( o._foreground ) )
                {}
                
                ~TermColor()
                {}
                
                TermColor & operator =( TermColor o )
                {
                    swap( *( this ), o );
                    
                    return *( this );
                }
                
                friend void swap( TermColor & o1, TermColor & o2 ) noexcept
                {
                    using std::swap;
                    
                    swap( o1._foreground, o2._foreground );
                }

                friend std::ostream & operator <<( std::ostream & os, Foreground foreground )
                {
                    return os << TermColor( foreground );
                }

                friend std::ostream & operator <<( std::ostream & os, const TermColor & color )
                {
                    if( SupportsANSISequences( os ) )
                    {
                        os << ANSISequence( color._foreground );
                    }

                    #ifdef _WIN32

                    else if( SupportsWindowsConsoleAttributes( os ) )
                    {
                        SetWindowsConsoleAttributes( os, color._foreground );
                    }

                    #endif

                    return os;
                }
                
            private:
                
                #ifdef _WIN32

                static Optional< WORD > DefaultConsoleAttributes( std::ostream & os )
                {
                    static CONSOLE_SCREEN_BUFFER_INFO * infos[ 2 ] = { nullptr, nullptr };
                    size_t                              index;

                    if( std::addressof( os ) == std::addressof( std::cout ) )
                    {
                        index = 0;
                    }
                    else if( std::addressof( os ) == std::addressof( std::cout ) )
                    {
                        index = 1;
                    }
                    else
                    {
                        return {};
                    }

                    if( infos[ index ] == nullptr )
                    {
                        Optional< CONSOLE_SCREEN_BUFFER_INFO > info( CurrentConsoleInfo( os ) );

                        if( info.HasValue() == false )
                        {
                            return {};
                        }

                        infos[ index ] = new CONSOLE_SCREEN_BUFFER_INFO( *( info ) );
                    }

                    return infos[ index ]->wAttributes;
                }
                
                static HANDLE GetWindowsConsoleHandle( std::ostream & os )
                {
                    if( std::addressof( os ) == std::addressof( std::cout ) )
                    {
                        return GetStdHandle( STD_OUTPUT_HANDLE );
                    }
                    else if( std::addressof( os ) == std::addressof( std::cerr ) )
                    {
                        return GetStdHandle( STD_ERROR_HANDLE );
                    }

                    return nullptr;
                }

                static Optional< CONSOLE_SCREEN_BUFFER_INFO > CurrentConsoleInfo( std::ostream & os )
                {
                    HANDLE h( GetWindowsConsoleHandle( os ) );

                    if( h == nullptr )
                    {
                        return {};
                    }

                    {
                        CONSOLE_SCREEN_BUFFER_INFO info;

                        if( GetConsoleScreenBufferInfo( h, &info ) )
                        {
                            return info;
                        }
                    }

                    return {};
                }
                
                static bool SupportsWindowsConsoleAttributes( std::ostream & os )
                {
                    if
                    (
                           std::addressof( os ) != std::addressof( std::cout )
                        && std::addressof( os ) != std::addressof( std::cerr )
                    )
                    {
                        return false;
                    }

                    return GetConsoleWindow() != nullptr;
                }

                static void SetWindowsConsoleAttributes( std::ostream & os, Foreground foreground )
                {
                    HANDLE           h( GetWindowsConsoleHandle( os ) );
                    Optional< WORD > attributes;

                    switch( foreground )
                    {
                        case Foreground::None:    attributes = DefaultConsoleAttributes( os ); break;
                        case Foreground::Gray:    attributes =  8; break;
                        case Foreground::Red:     attributes = 12; break;
                        case Foreground::Green:   attributes = 10; break;
                        case Foreground::Yellow:  attributes = 14; break;
                        case Foreground::Blue:    attributes =  9; break;
                        case Foreground::Magenta: attributes = 13; break;
                        case Foreground::Cyan:    attributes = 11; break;
                        case Foreground::White:   attributes = 15; break;
                    }

                    if( attributes.HasValue() && h != nullptr )
                    {
                        SetConsoleTextAttribute( h, *( attributes ) );
                    }
                }

                #endif

                static bool SupportsANSISequences( std::ostream & os )
                {
                    #ifdef _WIN32
                    
                    char      * cp( nullptr );
                    size_t      s( 0 );
                    std::string term;

                    if( _dupenv_s( &cp, &s, "TERM" ) == 0 && cp != nullptr )
                    {
                        term = cp;

                        free( cp );
                    }

                    if
                    (
                           std::addressof( os ) == std::addressof( std::cout )
                        || std::addressof( os ) == std::addressof( std::cerr )
                    )
                    {
                        return term == "xterm";
                    }
                    
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

                static std::string ANSISequence( Foreground foreground )
                {
                    switch( foreground )
                    {
                        case Foreground::None:    return "\033[00m";
                        case Foreground::Gray:    return "\033[30m";
                        case Foreground::Red:     return "\033[31m";
                        case Foreground::Green:   return "\033[32m";
                        case Foreground::Yellow:  return "\033[33m";
                        case Foreground::Blue:    return "\033[34m";
                        case Foreground::Magenta: return "\033[35m";
                        case Foreground::Cyan:    return "\033[36m";
                        case Foreground::White:   return "\033[37m";
                    }

                    #ifndef __clang__
                    return "";
                    #endif
                }

                Foreground _foreground;
        };
    }
}

#endif /* XS_TEST_TERM_COLOR_HPP */
