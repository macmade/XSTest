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
#include <XSTest/Logging.hpp>
#include <XSTest/TermColor.hpp>

#ifdef _WIN32
#include <Windows.h>
#endif

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
                
                ~Runner()
                {}
                
                Runner & operator =( Runner o )
                {
                    swap( *( this ), o );
                    
                    return *( this );
                }
                
                std::vector< Suite > GetSuites() const
                {
                    return this->_suites;
                }
                
                bool Run( Optional< std::reference_wrapper< std::ostream > > os )
                {
                    size_t    suites( 0 );
                    size_t    cases( 0 );
                    StopWatch time;
                    bool      success( true );
                    
                    if( this->_suites.size() == 0 )
                    {
                        Logging::Log( os, "No test to run...", {}, Logging::Style::Failure );
                        
                        return false;
                    }
                    
                    suites += this->_suites.size();
                    
                    for( const auto & suite: this->_suites )
                    {
                        cases += suite.GetInfos().size();
                    }
                    
                    Logging::Log( os, "Running " + Utility::Numbered( "test case", cases ) + " from " + Utility::Numbered( "test suite", suites ) );
                    
                    time.Start();
                    
                    for( auto & suite: this->_suites )
                    {
                        if( suite.Run( os ) == false )
                        {
                            success = false;
                        }
                    }
                    
                    time.Stop();
                    
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
                        
                        Logging::Log( os, Utility::Numbered( "test case", cases ) + " from " + Utility::Numbered( "test suite", suites ) + " ran (" + time.GetString() + " total)", {}, Logging::Style::None, Logging::Options::NewLineBefore );
                        Logging::Log( os, Utility::Numbered( "test", passed.size() ) + " passed:", ( ( passed.size() > 0 ) ? TermColor::Green() : TermColor::Red() ) );
                        
                        std::sort( passed.begin(), passed.end(), []( const Info & o1, const Info & o2 ) { return o1.GetName() < o2.GetName(); } );
                        
                        for( const auto & info: passed )
                        {
                            #ifdef _WIN32
                            Logging::Log( os, info.GetSuiteName(), info.GetCaseName(), "  - " );
                            #else
                            Logging::Log( os, info.GetSuiteName(), info.GetCaseName(), "  - ✅ " );
                            #endif
                        }
                        
                        if( failed.size() > 0 )
                        {
                            std::sort( failed.begin(), failed.end(), []( const Info & o1, const Info & o2 ) { return o1.GetName() < o2.GetName(); } );
                            
                            Logging::Log( os, Utility::Numbered( "test", failed.size() ) + " failed:", TermColor::Red() );
                            
                            for( const auto & info: failed )
                            {
                                #ifdef _WIN32
                                Logging::Log( os, info.GetSuiteName(), info.GetCaseName(), "  - " );
                                #else
                                Logging::Log( os, info.GetSuiteName(), info.GetCaseName(), "  - ❌ " );
                                #endif
                            }
                            
                            Logging::Log( os, "TESTING FAILED", TermColor::Red(), Logging::Style::None, Logging::Options::NewLineBefore );
                        }
                        else
                        {
                            Logging::Log( os, "TESTING PASSED", TermColor::Green(), Logging::Style::None, Logging::Options::NewLineBefore );
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
                
                std::vector< Suite > _suites;
        };
    }
}

#endif /* XS_TEST_RUNNER_HPP */
