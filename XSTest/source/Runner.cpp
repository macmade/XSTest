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
 * @file        Runner.cpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#include <XS/Test/Runner.hpp>
#include <XS/Test/Utility.hpp>
#include <XS/Test/Info.hpp>
#include <XS/Test/Group.hpp>
#include <XS/Test/StopWatch.hpp>
#include <algorithm>

namespace XS
{
    namespace Test
    {
        class Runner::IMPL
        {
            public:
                
                IMPL( const std::vector< Group > & groups );
                IMPL( IMPL & o );
                ~IMPL( void );
                
                void setup( std::ostream & os );
                void tearDown( std::ostream & os );
                
                std::vector< Group > _groups;
        };
        
        Runner::Runner( const std::vector< Group > & groups ):
            impl( std::make_shared< IMPL >( groups ) )
        {}
        
        Runner::Runner( const Runner & o ):
            impl( std::make_shared< IMPL >( *( o.impl ) ) )
        {}
        
        Runner::~Runner( void )
        {}
        
        Runner & Runner::operator =( Runner o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        std::vector< Group > Runner::GetGroups( void ) const
        {
            return this->impl->_groups;
        }
        
        bool Runner::Run( std::ostream & os )
        {
            size_t    cases( 0 );
            size_t    tests( 0 );
            StopWatch time;
            bool      success( true );
            
            if( this->impl->_groups.size() == 0 )
            {
                return false;
            }
            
            cases += this->impl->_groups.size();
            
            for( const auto & group: this->impl->_groups )
            {
                tests += group.GetInfos().size();
            }
            
            os << "[==========] Running "
               << Utility::Numbered( "test", tests )
               << " from "
               << Utility::Numbered( "case", cases )
               << "."
               << std::endl;
            
            this->impl->setup( os );
            
            time.Start();
            
            os << std::endl;
            
            for( auto & group: this->impl->_groups )
            {
                if( group.Run( os ) == false )
                {
                    success = false;
                }
            }
            
            time.Stop();
            
            this->impl->tearDown( os );
            
            os << "[==========] "
               << Utility::Numbered( "test", tests )
               << " from "
               << Utility::Numbered( "case", cases )
               << " ran. ("
               << time.GetString()
               << " total)"
               << std::endl;
            
            {
                std::vector< Info > passed;
                std::vector< Info > failed;
                
                for( auto & group: this->impl->_groups )
                {
                    for( auto & info: group.GetInfos() )
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
                
                os << "[  PASSED  ] "
                   << Utility::Numbered( "test", passed.size() )
                   << "."
                   << std::endl;
                   
                if( failed.size() > 0 )
                {
                    os << "[  FAILED  ] "
                       << Utility::Numbered( "test", failed.size() )
                       << ", listed below:"
                       << std::endl;
                    
                    for( const auto & info: failed )
                    {
                        os << "[  FAILED  ] "
                           << info.GetName()
                           << std::endl;
                    }
                    
                    os << std::endl
                       << Utility::Numbered( "FAILED TEST", failed.size(), "FAILED TESTS" )
                       << std::endl;
                }
            }
            
            return success;
        }
        
        void swap( Runner & o1, Runner & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        Runner::IMPL::IMPL( const std::vector< Group > & groups ):
            _groups( groups )
        {
            Utility::Shuffle( this->_groups );
        }
        
        Runner::IMPL::IMPL( IMPL & o ):
            _groups( o._groups )
        {
            Utility::Shuffle( this->_groups );
        }
        
        Runner::IMPL::~IMPL( void )
        {}
        
        void Runner::IMPL::setup( std::ostream & os )
        {
            os << "[----------] Global test environment set-up."
               << std::endl;
        }
        
        void Runner::IMPL::tearDown( std::ostream & os )
        {
            os << "[----------] Global test environment tear-down."
            << std::endl;
        }
    }
}
