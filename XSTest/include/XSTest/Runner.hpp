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
 * @header      Runner.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_RUNNER_HPP
#define XS_TEST_RUNNER_HPP

#include <iostream>
#include <memory>
#include <algorithm>
#include <XSTest/Optional.hpp>
#include <XSTest/Utility.hpp>
#include <XSTest/Info.hpp>
#include <XSTest/Suite.hpp>
#include <XSTest/StopWatch.hpp>
#include <XSTest/Log.hpp>

namespace XS
{
    namespace Test
    {
        class Suite;
        
        class Runner
        {
            public:
                
                Runner( const std::vector< Suite > & suites ):
                    _suites( suites )
                {
                    Utility::Shuffle( this->_suites );
                }
                
                Runner( const Runner & o ):
                    Runner( o._suites )
                {}
                
                Runner( Runner && o ) noexcept:
                    _suites( std::move( o._suites ) )
                {}
                
                ~Runner( void )
                {}
                
                Runner & operator =( Runner o )
                {
                    swap( *( this ), o );
                    
                    return *( this );
                }
                
                std::vector< Suite > GetSuites( void ) const
                {
                    return this->_suites;
                }
                
                bool Run( Optional< std::reference_wrapper< std::ostream > > os )
                {
                    size_t    cases( 0 );
                    size_t    tests( 0 );
                    StopWatch time;
                    bool      success( true );
                    
                    if( this->_suites.size() == 0 )
                    {
                        return false;
                    }
                    
                    cases += this->_suites.size();
                    
                    for( const auto & suite: this->_suites )
                    {
                        tests += suite.GetInfos().size();
                    }
                    
                    Log( os, {}, "Running " + Utility::Numbered( "test", tests ) + " from " + Utility::Numbered( "case", cases ) );
                    
                    this->setup( os );
                    
                    time.Start();
                    
                    for( auto & suite: this->_suites )
                    {
                        if( suite.Run( os ) == false )
                        {
                            success = false;
                        }
                    }
                    
                    time.Stop();
                    
                    this->tearDown( os );
                    
                    Log( os, {}, Utility::Numbered( "test", tests ) + " from " + Utility::Numbered( "case", cases ) + " ran (" + time.GetString() + " total)" );
                    
                    {
                        std::vector< Info > passed;
                        std::vector< Info > failed;
                        
                        for( auto & suite: this->_suites )
                        {
                            for( auto & info: suite.GetInfos() )
                            {
                                if( info.GetStatus() == Info::Status::Failed )
                                {
                                    failed.push_back( info );
                                }
                                else if( info.GetStatus() == Info::Status::Success )
                                {
                                    passed.push_back( info );
                                }
                            }
                        }
                        
                        Log( os, {}, Utility::Numbered( "test", passed.size() ) + " passed" );
                        
                        if( failed.size() > 0 )
                        {
                            Log( os, {}, Utility::Numbered( "test", passed.size() ) + " failed, listed below:" );
                            
                            for( const auto & info: failed )
                            {
                                Log( os, { "FAILED" }, info.GetName() );
                            }
                            
                            Log( os, {}, Utility::Numbered( "FAILED TEST", failed.size(), "FAILED TESTS" ) );
                        }
                    }
                    
                    return success;
                }
                
                friend void swap( Runner & o1, Runner & o2 ) noexcept
                {
                    using std::swap;
                    
                    swap( o1._suites, o2._suites );
                }
                
            private:
                
                void setup( Optional< std::reference_wrapper< std::ostream > > os )
                {
                    Log( os, {}, "Global test environment set-up" );
                }
                
                void tearDown( Optional< std::reference_wrapper< std::ostream > > os )
                {
                    Log( os, {}, "Global test environment tear-down" );
                }
                
                std::vector< Suite > _suites;
        };
    }
}

#endif /* XS_TEST_RUNNER_HPP */
