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
 * @header      Macros.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_MACROS_HPP
#define XS_TEST_MACROS_HPP

/*******************************************************************************
 * Compatibility
 ******************************************************************************/

#define TEST( _case_, _name_ )              XSTest( _case_, _name_ )
#define ASSERT_FALSE( _e_ )                 XSAssertFalse( _e_ )
#define ASSERT_TRUE( _e_ )                  XSAssertTrue( _e_ )
#define ASSERT_EQ( _v1_, _v2_ )             XSAssertEqual( _v1_, _v2_ )
#define ASSERT_NE( _v1_, _v2_ )             XSAssertNotEqual( _v1_, _v2_ )
#define ASSERT_LT( _v1_, _v2_ )             XSAssertLess( _v1_, _v2_ )
#define ASSERT_LE( _v1_, _v2_ )             XSAssertLessOrEqual( _v1_, _v2_ )
#define ASSERT_GT( _v1_, _v2_ )             XSAssertGreater( _v1_, _v2_ )
#define ASSERT_GE( _v1_, _v2_ )             XSAssertGreaterOrEqual( _v1_, _v2_ )
#define ASSERT_STREQ( _s1_, _s2_ )          XSAssertStringEqual( _s1_, _s2_ )
#define ASSERT_STRNE( _s1_, _s2_ )          XSAssertStringNotEqual( _s1_, _s2_ )
#define ASSERT_STRCASEEQ( _s1_, _s2_ )      XSAssertStringEqualCaseInsensitive( _s1_, _s2_ )
#define ASSERT_STRCASENE( _s1_, _s2_ )      XSAssertStringNotEqualCaseInsensitive( _s1_, _s2_ )
#define ASSERT_THROW( _e_, _ex_ )           XSAssertThrow( _e_, _ex_ )
#define ASSERT_NO_THROW( _e_ )              XSAssertNoThrow( _e_ )
#define ASSERT_ANY_THROW( _e_ )             XSAssertAnyThrow( _e_ )
#define ASSERT_FLOAT_EQ( _v1_, _v2_ )       XSAssertFloatEqual( _v1_, _v2_ )
#define ASSERT_DOUBLE_EQ( _v1_, _v2_ )      XSAssertDoubleEqual( _v1_, _v2_ )
#define ASSERT_LONGDOUBLE_EQ( _v1_, _v2_ )  XSAssertLongDoubleEqual( _v1_, _v2_ )
#define ASSERT_HRESULT_SUCCEEDED( _e_ )     XSAssertHResultSucceeded( _e_ )
#define ASSERT_HRESULT_FAILED( _e_ )        XSAssertHResultFailed( _e_ )
#define ASSERT_NO_FATAL_FAILURE( _e_ )      XSAssertNoFatalFailure( _e_ )

/*******************************************************************************
 * Assertions
 ******************************************************************************/

#define XSAssertFalse( _e_ )                                
#define XSAssertTrue( _e_ )                                 
#define XSAssertEqual( _v1_, _v2_ )                         
#define XSAssertNotEqual( _v1_, _v2_ )                      
#define XSAssertLess( _v1_, _v2_ )                          
#define XSAssertLessOrEqual( _v1_, _v2_ )                   
#define XSAssertGreater( _v1_, _v2_ )                       
#define XSAssertGreaterOrEqual( _v1_, _v2_ )                
#define XSAssertStringEqual( _s1_, _s2_ )                   
#define XSAssertStringNotEqual( _s1_, _s2_ )                
#define XSAssertStringEqualCaseInsensitive( _s1_, _s2_ )    
#define XSAssertStringNotEqualCaseInsensitive( _s1_, _s2_ ) 
#define XSAssertThrow( _e_, _ex_ )                          
#define XSAssertNoThrow( _e_ )                              
#define XSAssertAnyThrow( _e_ )                              
#define XSAssertFloatEqual( _v1_, _v2_ )                    
#define XSAssertDoubleEqual( _v1_, _v2_ )                   
#define XSAssertLongDoubleEqual( _v1_, _v2_ )               
#define XSAssertHResultSucceeded( _e_ )                     
#define XSAssertHResultFailed( _e_ )                        
#define XSAssertNoFatalFailure( _e_ )                       

/*******************************************************************************
 * Test cases
 ******************************************************************************/
 
#define XSTest( _case_, _name_ )                    XSTest_Internal_TestSetup( _case_, _name_, XSTest_Internal_ClassName( _case_, _name_ ), XS::Test::Case )
#define XSTest_Internal_ClassName( _case_, _name_ ) Test_ ## _case_ ## _ ## _name_
#define XSTest_Internal_XString( _s_ )              XSTest_Internal_String( _s_ )
#define XSTest_Internal_String( _s_ )               #_s_

#define XSTest_Internal_TestSetup( _case_, _name_, _class_, _base_ )    \
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
        XSTest_Internal_XString( _case_ ),                              \
        XSTest_Internal_XString( _name_ ),                              \
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
