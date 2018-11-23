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
#include <XS/Test/Suite.hpp>
#include <XS/Test/StopWatch.hpp>
#include <algorithm>

namespace XS
{
    namespace Test
    {
        class Runner::IMPL
        {
            public:
                
                IMPL( const std::vector< Suite > & suites );
                IMPL( IMPL & o );
                ~IMPL( void );
                
                void setup( Optional< std::reference_wrapper< std::ostream > > os );
                void tearDown( Optional< std::reference_wrapper< std::ostream > > os );
                
                std::vector< Suite > _suites;
        };
        
        Runner::Runner( const std::vector< Suite > & suites ):
            impl( new IMPL( suites ) )
        {}
        
        Runner::Runner( const Runner & o ):
            impl( new IMPL( *( o.impl ) ) )
        {}
        
        Runner::~Runner( void )
        {}
        
        Runner & Runner::operator =( Runner o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        std::vector< Suite > Runner::GetSuites( void ) const
        {
            return this->impl->_suites;
        }
        
        bool Runner::Run( Optional< std::reference_wrapper< std::ostream > > os )
        {
            size_t    cases( 0 );
            size_t    tests( 0 );
            StopWatch time;
            bool      success( true );
            
            if( this->impl->_suites.size() == 0 )
            {
                return false;
            }
            
            cases += this->impl->_suites.size();
            
            for( const auto & suite: this->impl->_suites )
            {
                tests += suite.GetInfos().size();
            }
            
            if( os )
            {
                os.value().get() << "[==========] Running "
                                 << Utility::Numbered( "test", tests )
                                 << " from "
                                 << Utility::Numbered( "case", cases )
                                 << "."
                                 << std::endl;
            }
            
            this->impl->setup( os );
            
            time.Start();
            
            if( os )
            {
                os.value().get() << std::endl;
            }
            
            for( auto & suite: this->impl->_suites )
            {
                if( suite.Run( os ) == false )
                {
                    success = false;
                }
            }
            
            time.Stop();
            
            this->impl->tearDown( os );
            
            if( os )
            {
                os.value().get() << "[==========] "
                                 << Utility::Numbered( "test", tests )
                                 << " from "
                                 << Utility::Numbered( "case", cases )
                                 << " ran. ("
                                 << time.GetString()
                                 << " total)"
                                 << std::endl;
            }
            
            {
                std::vector< Info > passed;
                std::vector< Info > failed;
                
                for( auto & suite: this->impl->_suites )
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
                
                if( os )
                {
                    os.value().get() << "[  PASSED  ] "
                                     << Utility::Numbered( "test", passed.size() )
                                     << "."
                                     << std::endl;
                    
                    if( failed.size() > 0 )
                    {
                        os.value().get() << "[  FAILED  ] "
                                         << Utility::Numbered( "test", failed.size() )
                                         << ", listed below:"
                                         << std::endl;
                        
                        for( const auto & info: failed )
                        {
                            os.value().get() << "[  FAILED  ] "
                                             << info.GetName()
                                             << std::endl;
                        }
                        
                        os.value().get() << std::endl
                                         << Utility::Numbered( "FAILED TEST", failed.size(), "FAILED TESTS" )
                                         << std::endl;
                    }
                }
            }
            
            return success;
        }
        
        void swap( Runner & o1, Runner & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        Runner::IMPL::IMPL( const std::vector< Suite > & suites ):
            _suites( suites )
        {
            Utility::Shuffle( this->_suites );
        }
        
        Runner::IMPL::IMPL( IMPL & o ):
            _suites( o._suites )
        {
            Utility::Shuffle( this->_suites );
        }
        
        Runner::IMPL::~IMPL( void )
        {}
        
        void Runner::IMPL::setup( Optional< std::reference_wrapper< std::ostream > > os )
        {
            if( os )
            {
                os.value().get() << "[----------] Global test environment set-up." << std::endl;
            }
        }
        
        void Runner::IMPL::tearDown( Optional< std::reference_wrapper< std::ostream > > os )
        {
            if( os )
            {
                os.value().get() << "[----------] Global test environment tear-down." << std::endl;
            }
        }
    }
}
