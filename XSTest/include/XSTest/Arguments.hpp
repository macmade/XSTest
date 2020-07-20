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
 * @header      Arguments.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_ARGUMENTS_HPP
#define XS_TEST_ARGUMENTS_HPP

#include <vector>
#include <string>
#include <algorithm>

namespace XS
{
    namespace Test
    {
        class Arguments
        {
            public:
                
                Arguments( int argc, char * argv[] )
                {
                    std::string arg;
                    
                    for( int i = 1; i < argc; i++ )
                    {
                        arg = argv[ i ];
                        
                        this->_tests.push_back( arg );
                    }
                }
                
                Arguments( const Arguments & o ):
                    _tests( o._tests )
                {}
                
                Arguments( Arguments && o ) noexcept:
                    _tests( std::move( o._tests ) )
                {}
                
                ~Arguments()
                {}
                
                Arguments & operator =( Arguments o )
                {
                    swap( *( this ), o );
                    
                    return *( this );
                }
                
                bool ShouldRun( const std::string & testSuite, const std::string & testCase ) const
                {
                    if( this->_tests.size() == 0 )
                    {
                        return true;
                    }
                    
                    if( std::find( std::begin( this->_tests ), std::end( this->_tests ), testSuite ) != std::end( this->_tests ) )
                    {
                        return true;
                    }
                    
                    if( std::find( std::begin( this->_tests ), std::end( this->_tests ), testSuite + "." + testCase ) != std::end( this->_tests ) )
                    {
                        return true;
                    }
                    
                    return false;
                }
                
                friend void swap( Arguments & o1, Arguments & o2 ) noexcept
                {
                    using std::swap;
                    
                    swap( o1._tests, o2._tests );
                }
                
            private:
                
                std::vector< std::string > _tests;
        };
    }
}

#endif /* XS_TEST_ARGUMENTS_HPP */
