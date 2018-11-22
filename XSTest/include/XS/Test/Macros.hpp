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
 * @header      Macors.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_MACROS_HPP
#define XS_TEST_MACROS_HPP

#define TEST( _case_, _name_ )              XS_TEST( _case_, _name_ )
#define XS_TEST( _case_, _name_ )           XS_TEST_SETUP( _case_, _name_, XS_TEST_CLASSNAME( _case_, _name_ ), XS::Test::Base )
#define XS_TEST_CLASSNAME( _case_, _name_ ) Test_ ## _case_ ## _ ## _name_
#define XS_TEST_XSTR( _s_ )                 XS_TEST_STR( _s_ )
#define XS_TEST_STR( _s_ )                  #_s_

#define XS_TEST_SETUP( _case_, _name_, _class_, _base_ )                \
                                                                        \
    class _class_: public _base_                                        \
    {                                                                   \
        public:                                                         \
                                                                        \
            _class_( void ) = default;                                  \
                                                                        \
            const XS::Test::Info & Info( void ) override;               \
            void                   Test( void ) override;               \
                                                                        \
        private:                                                        \
                                                                        \
            const static XS::Test::Info & _InfoRef;                     \
    };                                                                  \
                                                                        \
    const XS::Test::Info & _class_::_InfoRef = XS::Test::Info::Register \
    (                                                                   \
        XS_TEST_XSTR( _case_ ),                                         \
        XS_TEST_XSTR( _name_ ),                                         \
        std::make_shared< _class_ >()                                   \
    );                                                                  \
                                                                        \
    const XS::Test::Info & _class_::Info( void )                        \
    {                                                                   \
        return _InfoRef;                                                \
    }                                                                   \
                                                                        \
    void _class_::Test( void )                                          \

#endif /* XS_TEST_MACROS_HPP */
