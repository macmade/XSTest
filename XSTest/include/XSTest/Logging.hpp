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
 * @header      Logging.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_LOG_HPP
#define XS_TEST_LOG_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <XSTest/Flags.hpp>
#include <XSTest/Optional.hpp>
#include <XSTest/TermColor.hpp>
#include <XSTest/Failure.hpp>

namespace XS
{
    namespace Test
    {
        namespace Logging
        {
            enum class Style
            {
                None,
                Success,
                Failure
            };
            
            enum class Options: unsigned int
            {
                NewLineBefore = 0x01,
                NewLineAfter  = 0x02
            };
            
            inline void SuccessPrompt( Optional< std::reference_wrapper< std::ostream > > os )
            {
                if( os.HasValue() == false )
                {
                    return;
                }
                
                os->get() << "[ " << TermColor::Green() << "PASSED" << TermColor::None() << " ]> ";
            }
            
            inline void FailedPrompt( Optional< std::reference_wrapper< std::ostream > > os )
            {
                if( os.HasValue() == false )
                {
                    return;
                }
                
                os->get() << "[ " << TermColor::Red() << "FAILED" << TermColor::None() << " ]> ";
            }
            
            inline void Prompt( Optional< std::reference_wrapper< std::ostream > > os )
            {
                if( os.HasValue() == false )
                {
                    return;
                }
                
                os->get() << "> ";
            }
            
            inline void Log
            (
                Optional< std::reference_wrapper< std::ostream > > os,
                const std::string & message,
                Optional< TermColor > color = {},
                Style style = Style::None,
                Flags< Options > options = {}
            )
            {
                if( os.HasValue() == false )
                {
                    return;
                }
                
                if( options.HasFlag( Options::NewLineBefore ) )
                {
                    os->get() << std::endl;
                }
                
                if( style == Style::Success )
                {
                    SuccessPrompt( os );
                }
                else if( style == Style::Failure )
                {
                    FailedPrompt( os );
                }
                else
                {
                    Prompt( os );
                }
                
                if( color.HasValue() )
                {
                    os->get() << *( color );
                }
                
                os->get() << message << TermColor::None() << std::endl;
                
                if( options.HasFlag( Options::NewLineAfter ) )
                {
                    os->get() << std::endl;
                }
            }
            
            inline void Log
            (
                Optional< std::reference_wrapper< std::ostream > > os,
                const std::string & testSuite,
                const std::string & testCase,
                const std::string & prefix
            )
            {
                if( os.HasValue() == false )
                {
                    return;
                }
                
                os->get() << prefix
                          << TermColor::Blue()
                          << testSuite
                          << TermColor::None()
                          << "."
                          << TermColor::Magenta()
                          << testCase
                          << TermColor::None()
                          << std::endl;
            }
            
            inline void Log
            (
                Optional< std::reference_wrapper< std::ostream > > os,
                const std::string & testSuite,
                const std::string & testCase,
                Optional< Failure > failure,
                const StopWatch & time
            )
            {
                if( os.HasValue() == false )
                {
                    return;
                }
                
                if( failure.HasValue() )
                {
                    Logging::FailedPrompt( os );
                    
                    os->get() << TermColor::Blue()
                              << testSuite
                              << TermColor::None()
                              << "."
                              << TermColor::Magenta()
                              << testCase
                              << TermColor::None()
                              << " - "
                              << time.GetString()
                              << std::endl;
                
                    {
                        std::string file( ( failure->GetFile().length() > 0 ) ? failure->GetFile() : "<unknown>" );
                        std::string expression( failure->GetExpression() );
                        std::string evaluated( failure->GetEvaluated() );
                        std::string expected( failure->GetExpected() );
                        std::string actual( failure->GetActual() );
                            
                        os->get() << "            - File:       "
                                  << TermColor::Yellow()
                                  << file
                                  << ":"
                                  << std::to_string( failure->GetLine() )
                                  << TermColor::None();
                                  
                        if( expression.length() > 0 )
                        {
                            os->get() << std::endl
                                      << "            - Expression: "
                                      << TermColor::Cyan()
                                      << expression
                                      << TermColor::None();
                            
                            if( evaluated.length() > 0 && evaluated != expression )
                            {
                                os->get() << std::endl
                                          << "            - Evaluated:  "
                                          << TermColor::Magenta()
                                          << evaluated
                                          << TermColor::None();
                            }
                            
                            if( expected.length() > 0 )
                            {
                                os->get() << std::endl
                                          << "            - Expected:   "
                                          << TermColor::Green()
                                          << expected
                                          << TermColor::None();
                            }
                            
                            if( actual.length() > 0 )
                            {
                                os->get() << std::endl
                                          << "            - Actual:     "
                                          << TermColor::Red()
                                          << actual
                                          << TermColor::None();
                            }
                        }
                        else
                        {
                            os->get() << std::endl
                                      << "            - Reason:     "
                                      << TermColor::Red()
                                      << failure->GetDescription()
                                      << TermColor::None();
                        }
                    }
                    
                    os->get() << std::endl;
                }
                else
                {
                    Logging::SuccessPrompt( os );
                    
                    os->get() << TermColor::Blue()
                              << testSuite
                              << TermColor::None()
                              << "."
                              << TermColor::Magenta()
                              << testCase
                              << TermColor::None()
                              << " - "
                              << time.GetString()
                              << TermColor::None()
                              << std::endl;
                }
            }
        }
    }
}

#endif /* XS_TEST_LOG_HPP */
