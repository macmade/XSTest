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
 * @header      Suite.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_SUITE_HPP
#define XS_TEST_SUITE_HPP

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <XSTest/Optional.hpp>
#include <XSTest/StopWatch.hpp>
#include <XSTest/Utility.hpp>
#include <XSTest/Info.hpp>

namespace XS
{
    namespace Test
    {
        class Info;
        
        class Suite
        {
            public:
                
                static std::vector< Suite > All( void )
                {
                    std::map< std::string, std::vector< Info > > all;
                    std::vector< Suite >                         suites;
                    
                    for( auto & i: Info::All() )
                    {
                        all[ i.GetSuiteName() ].push_back( i );
                    }
                    
                    for( const auto & p: all )
                    {
                        suites.push_back( Suite( p.first, p.second ) );
                    }
                    
                    return suites;
                }
                
                Suite( const std::string & name, std::vector< Info > infos ):
                    _name(  name ),
                    _infos( infos )
                {
                    Utility::Shuffle( this->_infos );
                }
                
                Suite( const Suite & o ):
                    Suite( o._name, o._infos )
                {}
                
                Suite( Suite && o ) noexcept:
                    _name(  std::move( o._name ) ),
                    _infos( std::move( o._infos ) )
                {}
                
                ~Suite( void )
                {}
                
                Suite & operator =( Suite o )
                {
                    swap( *( this ), o );
                    
                    return *( this );
                }
                
                std::string GetName( void )  const
                {
                    return this->_name;
                }
                
                std::vector< Info > GetInfos( void ) const
                {
                    return this->_infos;
                }
                
                bool Run( Optional< std::reference_wrapper< std::ostream > > os )
                {
                    StopWatch time;
                    bool      success( true );
                    
                    if( this->_infos.size() == 0 )
                    {
                        return false;
                    }
                    
                    if( os )
                    {
                        os.value().get() << "[----------] "
                                         << Utility::Numbered( "test", this->_infos.size() )
                                         << " from "
                                         << this->_name
                                         << std::endl;
                    }
                    
                    time.Start();
                    
                    for( auto & i: this->_infos )
                    {
                        if( i.Run( os ) == false )
                        {
                            success = false;
                        }
                    }
                    
                    time.Stop();
                    
                    if( os )
                    {
                        os.value().get() << "[----------] "
                                         << Utility::Numbered( "test", this->_infos.size() )
                                         << " from "
                                         << this->_name
                                         << " ("
                                         << time.GetString()
                                         << " total)"
                                         << std::endl
                                         << std::endl;
                    }
                    
                    return success;
                }
                
                friend void swap( Suite & o1, Suite & o2 ) noexcept
                {
                    using std::swap;
                    
                    swap( o1._name,  o2._name );
                    swap( o1._infos, o2._infos );
                }
                
            private:
                
                std::string         _name;
                std::vector< Info > _infos;
        };
    }
}

#endif /* XS_TEST_SUITE_HPP */
