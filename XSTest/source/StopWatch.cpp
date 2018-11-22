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
 * @file        StopWatch.cpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#include <XS/Test/StopWatch.hpp>
#include <chrono>
#include <algorithm>

namespace XS
{
    namespace Test
    {
        class StopWatch::IMPL
        {
            public:
                
                enum class Status
                {
                    Unknown,
                    Started,
                    Stopped
                };
                
                IMPL( void );
                ~IMPL( void );
                
                std::chrono::time_point< std::chrono::system_clock > _start;
                std::chrono::time_point< std::chrono::system_clock > _end;
                Status                                               _status;
        };
        
        StopWatch::StopWatch( void ): impl( std::make_shared< IMPL >() )
        {}
        
        StopWatch::~StopWatch( void )
        {}
        
        void StopWatch::Start( void )
        {
            this->impl->_start  = std::chrono::system_clock::now();
            this->impl->_status = IMPL::Status::Started;
        }
        
        void StopWatch::Stop( void )
        {
            if( this->impl->_status != IMPL::Status::Started )
            {
                return;
            }
            
            this->impl->_end    = std::chrono::system_clock::now();
            this->impl->_status = IMPL::Status::Stopped;
        }
        
        int64_t StopWatch::GetSeconds( void ) const
        {
            std::chrono::duration< double > duration;
            
            if( this->impl->_status != IMPL::Status::Stopped )
            {
                return 0;
            }
            
            duration = { this->impl->_end - this->impl->_start };
            
            return std::chrono::duration_cast< std::chrono::seconds >( duration ).count();
        }
        
        int64_t StopWatch::GetMilliseconds( void ) const
        {
            std::chrono::duration< double > duration;
            
            if( this->impl->_status != IMPL::Status::Stopped )
            {
                return 0;
            }
            
            duration = { this->impl->_end - this->impl->_start };
            
            return std::chrono::duration_cast< std::chrono::milliseconds >( duration ).count();
        }
        
        std::string StopWatch::GetString( void ) const
        {
            return std::to_string( this->GetMilliseconds() ) + " ms";
        }
        
        StopWatch::IMPL::IMPL( void )
        {}
        
        StopWatch::IMPL::~IMPL( void )
        {}
    }
}
