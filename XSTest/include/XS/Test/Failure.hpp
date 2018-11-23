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
 * @header      Failure.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_FAILURE_HPP
#define XS_TEST_FAILURE_HPP

#include <stdexcept>
#include <memory>
#include <string>
#include <algorithm>

namespace XS
{
    namespace Test
    {
        class Failure: public std::exception
        {
            public:
                
                Failure( const std::string & reason, const std::string & file, int line ):
                    _reason( reason ),
                    _file(   file ),
                    _line(   line )
                {}
                
                Failure( const Failure & o ):
                    Failure( o._reason, o._file, o._line )
                {}
                
                Failure( Failure && o ) noexcept:
                    _reason( std::move( o._reason ) ),
                    _file(   std::move( o._file ) ),
                    _line(   std::move( o._line ) )
                {}
                
                ~Failure( void )
                {}
                
                Failure & operator =( Failure o )
                {
                    swap( *( this ), o );
                    
                    return *( this );
                }
                
                std::string GetReason( void ) const
                {
                    return this->_reason;
                }
                
                std::string GetFile( void ) const
                {
                    return this->_file;
                }
                
                int GetLine( void ) const noexcept
                {
                    return this->_line;
                }
                
                const char * what( void ) const noexcept override
                {
                    return this->_reason.c_str();
                }
                
                friend void swap( Failure & o1, Failure & o2 ) noexcept
                {
                    using std::swap;
                    
                    swap( o1._reason, o2._reason );
                    swap( o1._file,   o2._file );
                    swap( o1._line,   o2._line );
                }
                
            private:
                
                std::string _reason;
                std::string _file;
                int         _line;
        };
    }
}

#endif
