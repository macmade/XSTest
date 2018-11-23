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
#include <XS/Test/Case.hpp>
#include <XS/Test/Suite.hpp>
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
                
                IMPL( const std::string & suiteName, const std::string & caseName, const std::function< std::shared_ptr< Case >( void ) > createTest, const std::string & file, int line );
                IMPL( const IMPL & o );
                ~IMPL( void );
                
                std::string                                      _suiteName;
                std::string                                      _caseName;
                std::function< std::shared_ptr< Case >( void ) > _createTest;
                Status                                           _status;
                std::string                                      _file;
                int                                              _line;
                Optional< Failure >                              _failure;
        };
        
        Info & Info::Register( const std::string & testCaseName, const std::string & testName, const std::function< std::shared_ptr< Case >( void ) > createTest, const std::string & file, int line )
        {
            Info * i = new Info( testCaseName, testName, createTest, file, line );
            
            if( infos == nullptr )
            {
                infos = new std::vector< std::shared_ptr< Info > >();
            }
            
            infos->push_back( std::shared_ptr< Info >( i ) );
            
            return *( i );
        }
        
        std::vector< Suite > Info::All( void )
        {
            std::map< std::string, std::vector< Info > > all;
            std::vector< Suite >                         suites;
            
            if( infos == nullptr )
            {
                return {};
            }
            
            for( auto & i: *( infos ) )
            {
                all[ i->GetSuiteName() ].push_back( *( i ) );
            }
            
            for( const auto & p: all )
            {
                suites.push_back( Suite( p.first, p.second ) );
            }
            
            return suites;
        }
        
        Info::Info( const std::string & suiteName, const std::string & caseName, const std::function< std::shared_ptr< Case >( void ) > createTest, const std::string & file, int line ):
            impl( new IMPL( suiteName, caseName, createTest, file, line ) )
        {}
        
        Info::Info( const Info & o ):
            impl( new IMPL( *( o.impl ) ) )
        {}
        
        Info::Info( Info && o ) noexcept:
            impl( std::move( o.impl ) )
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
            return this->GetSuiteName() + "." + this->GetCaseName();
        }
        
        std::string Info::GetSuiteName( void ) const
        {
            return this->impl->_suiteName;
        }
        
        std::string Info::GetCaseName( void ) const
        {
            return this->impl->_caseName;
        }
        
        Info::Status Info::GetStatus( void ) const noexcept
        {
            return this->impl->_status;
        }
        
        std::string Info::GetFile( void ) const
        {
            return this->impl->_file;
        }
        
        int Info::GetLine( void ) const noexcept
        {
            return this->impl->_line;
        }
        
        Optional< Failure > Info::GetFailure( void ) const
        {
            return this->impl->_failure;
        }
        
        bool Info::Run( Optional< std::reference_wrapper< std::ostream > > os )
        {
            StopWatch               time;
            std::shared_ptr< Case > test( this->impl->_createTest() );
            
            this->impl->_failure.reset();
            
            this->impl->_status = Status::Running;
            
            if( os )
            {
                os.value().get() << "[ RUN      ] " << this->GetName() << std::endl;
            }
            
            test->SetUp();
            time.Start();
            
            try
            {
                test->Test();
                
                this->impl->_status = Status::Success;
            }
            catch( const Failure & e )
            {
                this->impl->_failure = e;
                this->impl->_status  = Status::Failed;
            }
            catch( const std::exception & e )
            {
                this->impl->_failure = Failure( std::string( "Caught unexpected exception: " ) + e.what(), this->impl->_file, this->impl->_line );
                this->impl->_status  = Status::Failed;
            }
            catch( ... )
            {
                this->impl->_failure = Failure( "Caught unexpected exception", this->impl->_file, this->impl->_line );
                this->impl->_status  = Status::Failed;
            }
            
            time.Stop();
            test->TearDown();
            
            if( os )
            {
                if( this->impl->_status == Status::Success )
                {
                    os.value().get() << "[       OK ] ";
                }
                else
                {
                    os.value().get() << this->impl->_failure->GetFile()
                                     << ":"
                                     << std::to_string( this->impl->_failure->GetLine() )
                                     << ": Failure"
                                     << std::endl
                                     << this->impl->_failure->GetReason()
                                     << std::endl;
                    
                    os.value().get() << "[  FAILED  ] ";
                }
                
                os.value().get() << this->GetName() << " (" << time.GetString() << ")" << std::endl;
            }
            
            return this->impl->_status == Status::Success;
        }
        
        void swap( Info & o1, Info & o2 ) noexcept
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        Info::IMPL::IMPL( const std::string & suiteName, const std::string & caseName, const std::function< std::shared_ptr< Case >( void ) > createTest, const std::string & file, int line ):
            _suiteName( suiteName ),
            _caseName( caseName ),
            _createTest( createTest ),
            _file( file ),
            _line( line ),
            _status( Status::Unknown )
        {}
        
        Info::IMPL::IMPL( const IMPL & o ):
            _suiteName( o._suiteName ),
            _caseName( o._caseName ),
            _createTest( o._createTest ),
            _status( o._status ),
            _file( o._file ),
            _line( o._line ),
            _failure( o._failure )
        {}
        
        Info::IMPL::~IMPL( void )
        {}
    }
}
