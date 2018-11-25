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
#include <sstream>
#include <algorithm>
#include <XSTest/TermColor.hpp>

namespace XS
{
    namespace Test
    {
        class Failure: public std::exception
        {
            public:
                
                Failure( const std::string & expression, const std::string & expected, const std::string & actual, const std::string & file, size_t line ):
                    _expression( expression ),
                    _expected(   expected ),
                    _actual(     actual ),
                    _file(       file ),
                    _line(       line )
                {
                    std::string description;
                    
                    if( expression.length() > 0 )
                    {
                        description += "Expression: " + expression;
                    }
                    
                    if( expected.length() > 0 )
                    {
                        if( description.length() > 0 )
                        {
                            description += " | ";
                        }
                        
                        description += "Expected: " + expected;
                    }
                    
                    if( actual.length() > 0 )
                    {
                        if( description.length() > 0 )
                        {
                            description += " | ";
                        }
                        
                        description += "Actual: " + actual;
                    }
                    
                    this->_description = description;
                }
                
                Failure( const std::string & description, const std::string & file, size_t line ):
                    _description( description ),
                    _file(       file ),
                    _line(       line )
                {}
                
                Failure( const Failure & o ):
                    _expression(  o._expression ),
                    _expected(    o._expected ),
                    _actual(      o._actual ),
                    _description( o._description ),
                    _file(        o._file ),
                    _line(        o._line )
                {}
                
                Failure( Failure && o ) noexcept:
                    _expression(  std::move( o._expression ) ),
                    _expected(    std::move( o._expected ) ),
                    _actual(      std::move( o._actual ) ),
                    _description( std::move( o._description ) ),
                    _file(        std::move( o._file ) ),
                    _line(        std::move( o._line ) )
                {}
                
                ~Failure( void )
                {}
                
                Failure & operator =( Failure o )
                {
                    swap( *( this ), o );
                    
                    return *( this );
                }
                
                std::string GetExpression( void ) const
                {
                    return this->_expression;
                }
                
                std::string GetExpected( void ) const
                {
                    return this->_expected;
                }
                
                std::string GetActual( void ) const
                {
                    return this->_actual;
                }
                
                std::string GetDescription( void ) const
                {
                    return this->_description;
                }
                
                std::string GetFile( void ) const
                {
                    return this->_file;
                }
                
                size_t GetLine( void ) const noexcept
                {
                    return this->_line;
                }
                
                const char * what( void ) const noexcept override
                {
                    return this->_description.c_str();
                }
                
                friend void swap( Failure & o1, Failure & o2 ) noexcept
                {
                    using std::swap;
                    
                    swap( o1._expression,  o2._expression );
                    swap( o1._expected,    o2._expected );
                    swap( o1._actual,      o2._actual );
                    swap( o1._description, o2._description );
                    swap( o1._file,        o2._file );
                    swap( o1._line,        o2._line );
                }
                
            private:
                
                std::string _expression;
                std::string _expected;
                std::string _actual;
                std::string _file;
                std::string _description;
                size_t      _line;
        };
    }
}

#endif
