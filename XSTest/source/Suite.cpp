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
 * @file        Suite.cpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#include <XS/Test/Suite.hpp>
#include <XS/Test/StopWatch.hpp>
#include <XS/Test/Utility.hpp>
#include <XS/Test/Info.hpp>
#include <algorithm>

namespace XS
{
    namespace Test
    {
        class Suite::IMPL
        {
            public:
                
                IMPL( const std::string & name, std::vector< Info > infos );
                IMPL( const IMPL & o );
                ~IMPL( void );
                
                std::string         _name;
                std::vector< Info > _infos;
        };
        
        Suite::Suite( const std::string & name, std::vector< Info > infos ):
            impl( std::make_shared< IMPL >( name, infos ) )
        {}
        
        Suite::Suite( const Suite & o ):
            impl( std::make_shared< IMPL >( *( o.impl ) ) )
        {}
        
        Suite::~Suite( void )
        {}
        
        Suite & Suite::operator =( Suite o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        std::string Suite::GetName( void ) const
        {
            return this->impl->_name;
        }
        
        std::vector< Info > Suite::GetInfos( void ) const
        {
            return this->impl->_infos;
        }
        
        bool Suite::Run( std::ostream & os )
        {
            StopWatch time;
            bool      success( true );
            
            if( this->impl->_infos.size() == 0 )
            {
                return false;
            }
            
            os << "[----------] "
               << Utility::Numbered( "test", this->impl->_infos.size() )
               << " from "
               << this->impl->_name
               << std::endl;
            
            time.Start();
            
            for( auto & i: this->impl->_infos )
            {
                if( i.Run( std::cout ) == false )
                {
                    success = false;
                }
            }
            
            time.Stop();
            
            os << "[----------] "
               << Utility::Numbered( "test", this->impl->_infos.size() )
               << " from "
               << this->impl->_name
               << " ("
               << time.GetString()
               << " total)"
               << std::endl
               << std::endl;
               
            return success;
        }
        
        void swap( Suite & o1, Suite & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        Suite::IMPL::IMPL( const std::string & name, std::vector< Info > infos ):
            _name( name ),
            _infos( infos )
        {
            Utility::Shuffle( this->_infos );
        }
        
        Suite::IMPL::IMPL( const IMPL & o ):
            _name( o._name ),
            _infos( o._infos )
        {
            Utility::Shuffle( this->_infos );
        }
        
        Suite::IMPL::~IMPL( void )
        {}
    }
}
