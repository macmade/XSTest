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
 * @header      FloatingPoint.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_FLOATING_POINT_HPP
#define XS_TEST_FLOATING_POINT_HPP

#include <type_traits>
#include <algorithm>
#include <cmath>

namespace XS
{
    namespace Test
    {
        template< typename _T_, typename = typename std::enable_if< std::is_same< _T_, float >::value || std::is_same< _T_, double >::value >::type >
        class FloatingPoint
        {
            public:
                
                FloatingPoint( _T_ value ):
                    _value( value )
                {}
                
                FloatingPoint( const FloatingPoint< _T_ > & o ):
                    _value( o._value )
                {}
                
                FloatingPoint( FloatingPoint< _T_ > && o ):
                    _value( std::move( o._value ) )
                {}
                
                ~FloatingPoint( void )
                {}
                
                FloatingPoint & operator =( FloatingPoint o )
                {
                    swap( *( this ), o );
                    
                    return *( this );
                }
                
                _T_ Value( void ) const
                {
                    return this->_value;
                }
                
                bool operator ==( _T_ value )
                {
                    return operator ==( FloatingPoint< _T_ >( value ) );
                }
                
                bool operator !=( _T_ value )
                {
                    return !operator ==( value );
                }
                
                bool operator ==( const FloatingPoint< _T_ > & o )
                {
                    return this->DistanceWith( o ) <= 4;
                }
                
                bool operator !=( const FloatingPoint< _T_ > & o )
                {
                    return !operator ==( o );
                }
                
                uint64_t DistanceWith( _T_ value )
                {
                    return this->DistanceWith( FloatingPoint< _T_ >( value ) );
                }
                
                uint64_t DistanceWith( const FloatingPoint< _T_ > & o )
                {
                    return DistanceBetween( this->_value, o._value );
                }
                
                friend void swap( FloatingPoint & o1, FloatingPoint & o2 )
                {
                    using std::swap;
                    
                    swap( o1._value, o2._value );
                } 
                
            private:
                
                _T_ _value;
                
                static uint32_t DistanceBetween( float v1, float v2 )
                {
                    return DistanceBetween( *( reinterpret_cast< int32_t * >( &v1 ) ), *( reinterpret_cast< int32_t * >( &v2 ) ) );
                }
                
                static uint64_t DistanceBetween( double v1, double v2 )
                {
                    return DistanceBetween( *( reinterpret_cast< int64_t * >( &v1 ) ), *( reinterpret_cast< int64_t * >( &v2 ) ) );
                }
                
                template< typename _U_, typename = typename std::enable_if< std::is_integral< _U_ >::value >::type >
                static _U_ DistanceBetween( _U_ v1, _U_ v2 )
                {
                    _U_ signMask( static_cast< _U_ >( 1 ) << ( ( sizeof( _U_ ) * 8 ) - 1 ) );
                    _U_ diff;
                    
                    v1   = ( v1 >= 0 ) ? v1 : signMask - v1;
                    v2   = ( v2 >= 0 ) ? v2 : signMask - v2;
                    diff = v1 - v2;
                    
                    return ( diff >= 0 ) ? diff : -diff;
                }
        };
    }
}

#endif /* XS_TEST_FLOATING_POINT_HPP */
