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
 * @file        Failure.cpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#include <XS/Test/Failure.hpp>
#include <algorithm>

namespace XS
{
    namespace Test
    {
        class Failure::IMPL
        {
            public:
                
                IMPL( const std::string & reason, const std::string & file, int line );
                IMPL( const IMPL & o );
                ~IMPL( void );
                
                std::string _reason;
                std::string _file;
                int         _line;
        };
        
        Failure::Failure( const std::string & reason, const std::string & file, int line ):
            std::runtime_error( reason ),
            impl( new IMPL( reason, file, line ) )
        {}
        
        Failure::Failure( const Failure & o ):
            std::runtime_error( o.impl->_reason ),
            impl( new IMPL( *( o.impl ) ) )
        {}
        
        Failure::~Failure( void )
        {}
        
        Failure & Failure::operator =( Failure o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        std::string Failure::GetReason( void ) const
        {
            return this->impl->_reason;
        }
        
        std::string Failure::GetFile( void ) const
        {
            return this->impl->_file;
        }
        
        int Failure::GetLine( void ) const
        {
            return this->impl->_line;
        }
        
        void swap( Failure & o1, Failure & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        Failure::IMPL::IMPL( const std::string & reason, const std::string & file, int line ):
            _reason( reason ),
            _file( file ),
            _line( line )
        {}
        
        Failure::IMPL::IMPL( const IMPL & o ):
            _reason( o._reason ),
            _file( o._file ),
            _line( o._line )
        {}
        
        Failure::IMPL::~IMPL( void )
        {}
    }
}
