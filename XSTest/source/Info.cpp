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
 * @file        Info.cpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#include <XS/Test/Info.hpp>
#include <XS/Test/Base.hpp>
#include <XS/Test/Group.hpp>
#include <XS/Test/StopWatch.hpp>
#include <algorithm>
#include <random>
#include <map>

namespace XS
{
    namespace Test
    {
        static std::vector< std::shared_ptr< Info > > * infos = nullptr;
        
        class Info::IMPL
        {
            public:
                
                IMPL( const std::string & testCaseName, const std::string & testName, std::shared_ptr< Base > test );
                IMPL( const IMPL & o );
                ~IMPL( void );
                
                std::string             _testCaseName;
                std::string             _testName;
                std::shared_ptr< Base > _test;
                Status                  _status;
                std::string             _failureReason;
        };
        
        Info & Info::Register( const std::string & testCaseName, const std::string & testName, std::shared_ptr< Base > test )
        {
            Info * i = new Info( testCaseName, testName, test );
            
            if( infos == nullptr )
            {
                infos = new std::vector< std::shared_ptr< Info > >();
            }
            
            infos->push_back( std::shared_ptr< Info >( i ) );
            
            return *( i );
        }
        
        std::vector< Group > Info::All( void )
        {
            std::map< std::string, std::vector< Info > > all;
            std::vector< Group >                         groups;
            
            if( infos == nullptr )
            {
                return {};
            }
            
            for( auto & i: *( infos ) )
            {
                all[ i->GetTestCaseName() ].push_back( *( i ) );
            }
            
            for( const auto & p: all )
            {
                groups.push_back( Group( p.first, p.second ) );
            }
            
            return groups;
        }
        
        Info::Info( const std::string & testCaseName, const std::string & testName, std::shared_ptr< Base > test ):
            impl( std::make_shared< IMPL >( testCaseName, testName, test ) )
        {}
        
        Info::Info( const Info & o ):
            impl( std::make_shared< IMPL >( *( o.impl ) ) )
        {}
        
        Info::~Info( void )
        {}
        
        Info & Info::operator =( Info o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        std::string Info::GetName( void ) const
        {
            return this->GetTestCaseName() + "." + this->GetTestName();
        }
        
        std::string Info::GetTestCaseName( void ) const
        {
            return this->impl->_testCaseName;
        }
        
        std::string Info::GetTestName( void ) const
        {
            return this->impl->_testName;
        }
        
        std::shared_ptr< Base > Info::GetTest( void ) const
        {
            return this->impl->_test;
        }
        
        Info::Status Info::GetStatus( void ) const
        {
            return this->impl->_status;
        }
        
        std::string Info::GetFailureReason( void ) const
        {
            return this->impl->_failureReason;
        }
        
        bool Info::Run( std::ostream & os )
        {
            StopWatch time;
            
            this->impl->_status = Status::Running;
            
            os << "[ RUN      ] " << this->GetName() << std::endl;
            
            time.Start();
            
            try
            {
                this->GetTest()->Test();
                
                this->impl->_status = Status::Success;
            }
            catch( ... )
            {
                this->impl->_status = Status::Failed;
            }
            
            time.Stop();
            
            if( this->impl->_status == Status::Success )
            {
                os << "[       OK ] ";
            }
            else
            {
                os << "[  FAILED  ] ";
            }
            
            os << this->GetName() << " (" << time.GetString() << ")" << std::endl;
            
            return this->impl->_status == Status::Success;
        }
        
        void swap( Info & o1, Info & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        Info::IMPL::IMPL( const std::string & testCaseName, const std::string & testName, std::shared_ptr< Base > test ):
            _testCaseName( testCaseName ),
            _testName( testName ),
            _test( test ),
            _status( Status::Unknown )
        {}
        
        Info::IMPL::IMPL( const IMPL & o ):
            _testCaseName( o._testCaseName ),
            _testName( o._testName ),
            _test( o._test ),
            _status( o._status ),
            _failureReason( o._failureReason )
        {}
        
        Info::IMPL::~IMPL( void )
        {}
    }
}
