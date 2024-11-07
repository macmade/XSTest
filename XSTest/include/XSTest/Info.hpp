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
 * @header      Info.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_INFO_HPP
#define XS_TEST_INFO_HPP

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <random>
#include <map>
#include <XSTest/Optional.hpp>
#include <XSTest/Failure.hpp>
#include <XSTest/Case.hpp>
#include <XSTest/StopWatch.hpp>
#include <XSTest/Logging.hpp>
#include <XSTest/TermColor.hpp>

#define XS_TEST_GET_ALL_INFOS_DECLARATION                                   \
    std::vector< std::shared_ptr< Info > > & GetAllInfos();

#define XS_TEST_GET_ALL_INFOS_DEFINITION                                    \
    std::vector< std::shared_ptr< Info > > & GetAllInfos()                  \
    {                                                                       \
        static auto infos = new std::vector< std::shared_ptr< Info > >();   \
                                                                            \
        return *( infos );                                                  \
    }

namespace XS
{
    namespace Test
    {
        class Suite;
        class Case;
        
        #if defined( XSTEST_MAIN ) || defined( XSTEST_MAIN_RUN )
        
        inline XS_TEST_GET_ALL_INFOS_DEFINITION
        
        #else
        
        extern XS_TEST_GET_ALL_INFOS_DECLARATION
        
        #endif

        class Info
        {
            public:
                
                enum class Status
                {
                    Unknown,
                    Running,
                    Success,
                    Failed
                };
                
                static Info & Register( const std::string & testCaseName, const std::string & testName, const std::function< std::shared_ptr< Case >() > createTest, const std::string & file, size_t line )
                {
                    Info * i = new Info( testCaseName, testName, createTest, file, line );
                                        
                    GetInfos().push_back( std::shared_ptr< Info >( i ) );
                    
                    return *( i );
                }
                
                static std::vector< Info > All()
                {
                    std::vector< Info > all;
                    
                    for( auto & i: GetInfos() )
                    {
                        all.push_back( *( i ) );
                    }
                    
                    return all;
                }
                
                Info( const Info & o ):
                    _suiteName(  o._suiteName ),
                    _caseName(   o._caseName ),
                    _createTest( o._createTest ),
                    _status(     o._status ),
                    _file(       o._file ),
                    _line(       o._line ),
                    _failure(    o._failure )
                {}
                
                Info( Info && o ) noexcept:
                    _suiteName(  std::move( o._suiteName ) ),
                    _caseName(   std::move( o._caseName ) ),
                    _createTest( std::move( o._createTest ) ),
                    _status(     std::move( o._status ) ),
                    _file(       std::move( o._file ) ),
                    _line(       std::move( o._line ) ),
                    _failure(    std::move( o._failure ) )
                {}
                
                ~Info()
                {}
                
                Info & operator =( Info o )
                {
                    swap( *( this ), o );
                    
                    return *( this );
                }
                
                std::string GetName() const
                {
                    return this->_suiteName + "." + this->_caseName;
                }
                
                std::string GetSuiteName() const
                {
                    return this->_suiteName;
                }
                
                std::string GetCaseName() const
                {
                    return this->_caseName;
                }
                
                Status GetStatus() const noexcept
                {
                    return this->_status;
                }
                
                std::string GetFile() const
                {
                    return this->_file;
                }
                
                size_t GetLine() const noexcept
                {
                    return this->_line;
                }
                
                Optional< Failure > GetFailure() const
                {
                    return this->_failure;
                }
                
                bool Run( Optional< std::reference_wrapper< std::ostream > > os )
                {
                    StopWatch               time;
                    std::shared_ptr< Case > test( this->_createTest() );
                    
                    this->_failure.Reset();
                    
                    this->_status = Status::Running;
                    
                    test->SetUp();
                    time.Start();
                    
                    try
                    {
                        test->Test();
                        
                        this->_status = Status::Success;
                    }
                    catch( const Failure & e )
                    {
                        this->_failure = e;
                        this->_status  = Status::Failed;
                    }
                    catch( const std::exception & e )
                    {
                        this->_failure = Failure( std::string( "Caught unexpected exception: " ) + e.what(), this->_file, this->_line );
                        this->_status  = Status::Failed;
                    }
                    catch( ... )
                    {
                        this->_failure = Failure( "Caught unexpected exception", this->_file, this->_line );
                        this->_status  = Status::Failed;
                    }
                    
                    time.Stop();
                    test->TearDown();
                    Logging::Log( os, this->_suiteName, this->_caseName, this->_failure, time );
                    
                    return this->_status == Status::Success;
                }
                
                friend void swap( Info & o1, Info & o2 ) noexcept
                {
                    using std::swap;
                    
                    swap( o1._suiteName,  o2._suiteName );
                    swap( o1._caseName,   o2._caseName );
                    swap( o1._createTest, o2._createTest );
                    swap( o1._status,     o2._status );
                    swap( o1._file,       o2._file );
                    swap( o1._line,       o2._line );
                    swap( o1._failure,    o2._failure );
                }
                
            private:
                
                static std::vector< std::shared_ptr< Info > > & GetInfos()
                {
                    return GetAllInfos();
                }
                
                Info( const std::string & suiteName, const std::string & caseName, const std::function< std::shared_ptr< Case >() > createTest, const std::string & file, size_t line ):
                    _suiteName( suiteName ),
                    _caseName( caseName ),
                    _createTest( createTest ),
                    _status( Status::Unknown ),
                    _file( file ),
                    _line( line )
                {}
                
                std::string                                _suiteName;
                std::string                                _caseName;
                std::function< std::shared_ptr< Case >() > _createTest;
                Status                                     _status;
                std::string                                _file;
                size_t                                     _line;
                Optional< Failure >                        _failure;
        };
    }
}

#endif /* XS_TEST_INFO_HPP */
