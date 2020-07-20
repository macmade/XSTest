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
 * @header      Flags.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_FLAGS_HPP
#define XS_TEST_FLAGS_HPP

#include <type_traits>
#include <initializer_list>
#include <algorithm>

namespace XS
{
    namespace Test
    {
        template< typename _T_, typename = typename std::enable_if< std::is_enum< _T_ >::value && std::is_unsigned< typename std::underlying_type< _T_ >::type >::value >::type >
        class Flags
        {
            public:
                
                typedef typename std::underlying_type< _T_ >::type Type;
                
                Flags():
                    _value( 0 )
                {}
                
                Flags( Type value ):
                    _value( value )
                {}
                
                Flags( _T_ value ):
                    _value( static_cast< Type >( value ) )
                {}
                
                Flags( std::initializer_list< _T_ > value ):
                    _value( 0 )
                {
                    for( auto f: value )
                    {
                        this->AddFlag( f );
                    }
                }
                
                Flags( const Flags< _T_ > & o ):
                    _value( o._value )
                {}
                
                Flags( Flags< _T_ > && o ) noexcept:
                    _value( std::move( o._value ) )
                {}
                
                Flags< _T_ > & operator =( Flags< _T_ > o )
                {
                    swap( *( this ), o );
                    
                    return *( this );
                }
                
                bool operator ==( const Flags & o ) const
                {
                    return this->_value == o._value;
                }
                
                bool operator !=( const Flags & o ) const
                {
                    return !operator ==( o );
                }
                
                operator Type() const
                {
                    return this->_value;
                }
                
                bool HasFlag( _T_ flag ) const
                {
                    return this->_value & static_cast< Type >( flag );
                }
                
                void AddFlag( _T_ flag )
                {
                    this->_value |= static_cast< Type >( flag );
                }
                
                void RemoveFlag( _T_ flag )
                {
                    this->_value &= ~( static_cast< Type >( flag ) );
                }
                
                void Clear()
                {
                    this->_value = 0;
                }
                
                friend void swap( Flags< _T_ > & o1, Flags< _T_ > & o2 ) noexcept
                {
                    using std::swap;
                    
                    swap( o1._value, o2._value );
                }
                
            private:
                
                Type _value;
        };
    }
}

#endif /* XS_TEST_FLAGS_HPP */
