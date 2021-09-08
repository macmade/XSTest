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
 * @header      Optional.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 * @discussion  On macOS, std::optional is only available starting with
 *              macOS 10.14.
 */

#ifndef XS_TEST_OPTIONAL_HPP
#define XS_TEST_OPTIONAL_HPP

#include <algorithm>
#include <stdexcept>
#include <memory>

namespace XS
{
    namespace Test
    {
        template< typename _T_ >
        class Optional
        {
            public:
                
                class BadAccessException: public std::exception
                {};
                
                Optional()
                {}
                
                Optional( const _T_ & value ):
                    _hasValue( true )
                {
                    new ( this->_data )_T_( value );
                }
                
                Optional( const Optional< _T_ > & o ):
                    _hasValue( o._hasValue )
                {
                    if( o._hasValue )
                    {
                        new ( this->_data )_T_( reinterpret_cast< const _T_ & >( o._data ) );
                    }
                }
                
                ~Optional()
                {
                    if( this->_hasValue )
                    {
                        ( reinterpret_cast< _T_ * >( this->_data ) )->~_T_();
                    }
                }
                
                Optional< _T_ > & operator =( Optional< _T_ > o )
                {
                    swap( *( this ), o );
                    
                    return *( this );
                }
                
                Optional< _T_ > & operator =( const _T_ & value )
                {
                    Optional< _T_ > o( value );
                    
                    swap( *( this ), o );
                    
                    return *( this );
                }
                
                operator bool() const
                {
                    return this->HasValue();
                }
                
                const _T_ * operator ->() const
                {
                    if( this->_hasValue == false )
                    {
                        throw BadAccessException();
                    }
                    
                    return reinterpret_cast< const _T_ * >( this->_data );
                }
                
                _T_ * operator ->()
                {
                    if( this->_hasValue == false )
                    {
                        throw BadAccessException();
                    }
                    
                    return reinterpret_cast< _T_ * >( this->_data );
                }
                
                const _T_ & operator *() const &
                {
                    return this->Value();
                }
                
                _T_ & operator *() &
                {
                    return this->Value();
                }
                
                bool HasValue() const
                {
                    return this->_hasValue;
                }
                
                _T_ & Value() &
                {
                    return *( this->operator->() );
                }
                
                const _T_ & Value() const &
                {
                    return *( this->operator->() );
                }
                
                _T_ ValueOr( _T_ && defaultValue ) const &
                {
                    return ( this->HasValue() ) ? this->Value() : defaultValue;
                }
                
                _T_ ValueOr( _T_ && defaultValue ) &&
                {
                    return ( this->HasValue() ) ? this->Value() : defaultValue;
                }
                
                void Reset()
                {
                    Optional< _T_ > o;
                    
                    swap( *( this ), o );
                }
                
                friend void swap( Optional< _T_ > & o1, Optional< _T_ > & o2 )
                {
                    using std::swap;
                    
                    swap( o1._data,     o2._data );
                    swap( o1._hasValue, o2._hasValue );
                }
                
            private:
                
                alignas( alignof( _T_ ) ) uint8_t _data[ sizeof( _T_ ) ] = {};
                bool                              _hasValue              = false;
        };
        
        template< class _T_, class _U_ > 
        bool operator ==( const Optional< _T_ > & o1, const Optional< _U_ > & o2 )
        {
            if( o1.hasValue() && o2.hasValue() )
            {
                return o1.value() == o2.value();
            }
            
            return false;
        }
        
        template< class _T_, class _U_ > 
        bool operator !=( const Optional< _T_ > & o1, const Optional< _U_ >& o2 )
        {
            return !operator ==( o1, o2 );
        }
        
        template< class _T_, class _U_ > 
        bool operator ==( const Optional< _T_ > & o, const _U_ & value )
        {
            return operator ==( o, Optional< _T_ >( value ) );
        }
        
        template< class _T_, class _U_ > 
        bool operator !=( const Optional< _T_ > & o, const _U_ & value )
        {
            return !operator ==( o, value );
        }
        
        template< class _T_, class _U_ > 
        bool operator ==( const _T_ & value, const Optional< _U_ > & o )
        {
            return operator ==( Optional< _T_ >( value ), o );
        }
        
        template< class _T_, class _U_ > 
        bool operator !=( const _T_ & value, const Optional< _U_ > & o )
        {
            return !operator ==( value, o );
        }
    }
}

#endif /* XS_TEST_OPTIONAL_HPP */
