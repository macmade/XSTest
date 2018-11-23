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
 * @header      StopWatch.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_STOP_WATCH_HPP
#define XS_TEST_STOP_WATCH_HPP

#include <memory>
#include <string>
#include <cstdint>
#include <chrono>
#include <algorithm>

namespace XS
{
    namespace Test
    {
        class StopWatch
        {
            public:
                
                StopWatch( void ): _status( Status::Unknown )
                {}
                
                ~StopWatch( void )
                {}
                
                StopWatch( const StopWatch & o )              = delete;
                StopWatch & operator =( const StopWatch & o ) = delete;
                
                void Start( void )
                {
                    this->_start  = std::chrono::system_clock::now();
                    this->_status = Status::Started;
                }
                
                void Stop( void )
                {
                    if( this->_status != Status::Started )
                    {
                        return;
                    }
                    
                    this->_end    = std::chrono::system_clock::now();
                    this->_status = Status::Stopped;
                }
                
                int64_t GetSeconds( void ) const
                {
                    std::chrono::duration< double > duration;
                    
                    if( this->_status != Status::Stopped )
                    {
                        return 0;
                    }
                    
                    duration = { this->_end - this->_start };
                    
                    return std::chrono::duration_cast< std::chrono::seconds >( duration ).count();
                }
                
                int64_t GetMilliseconds( void ) const
                {
                    std::chrono::duration< double > duration;
                    
                    if( this->_status != Status::Stopped )
                    {
                        return 0;
                    }
                    
                    duration = { this->_end - this->_start };
                    
                    return std::chrono::duration_cast< std::chrono::milliseconds >( duration ).count();
                }
                
                std::string GetString( void ) const
                {
                    return std::to_string( this->GetMilliseconds() ) + " ms";
                }
                
            private:
                
                enum class Status
                {
                    Unknown,
                    Started,
                    Stopped
                };
                
                std::chrono::time_point< std::chrono::system_clock > _start;
                std::chrono::time_point< std::chrono::system_clock > _end;
                Status                                               _status;
        };
    }
}

#endif /* XS_TEST_STOP_WATCH_HPP */
