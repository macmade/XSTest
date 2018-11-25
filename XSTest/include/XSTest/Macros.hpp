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

#ifdef XSTEST_GTEST_COMPAT

#define TEST( _case_, _name_ )              XSTest( _case_, _name_ )
#define TEST_F( _case_, _name_ )            XSTestFixture( _case_, _name_ )
#define ASSERT_FALSE( _e_ )                 XSTestAssertFalse( _e_ )
#define ASSERT_TRUE( _e_ )                  XSTestAssertTrue( _e_ )
#define ASSERT_EQ( _v1_, _v2_ )             XSTestAssertEqual( _v1_, _v2_ )
#define ASSERT_NE( _v1_, _v2_ )             XSTestAssertNotEqual( _v1_, _v2_ )
#define ASSERT_LT( _v1_, _v2_ )             XSTestAssertLess( _v1_, _v2_ )
#define ASSERT_LE( _v1_, _v2_ )             XSTestAssertLessOrEqual( _v1_, _v2_ )
#define ASSERT_GT( _v1_, _v2_ )             XSTestAssertGreater( _v1_, _v2_ )
#define ASSERT_GE( _v1_, _v2_ )             XSTestAssertGreaterOrEqual( _v1_, _v2_ )
#define ASSERT_STREQ( _s1_, _s2_ )          XSTestAssertStringEqual( _s1_, _s2_ )
#define ASSERT_STRNE( _s1_, _s2_ )          XSTestAssertStringNotEqual( _s1_, _s2_ )
#define ASSERT_STRCASEEQ( _s1_, _s2_ )      XSTestAssertStringEqualCaseInsensitive( _s1_, _s2_ )
#define ASSERT_STRCASENE( _s1_, _s2_ )      XSTestAssertStringNotEqualCaseInsensitive( _s1_, _s2_ )
#define ASSERT_THROW( _e_, _ex_ )           XSTestAssertThrow( _e_, _ex_ )
#define ASSERT_NO_THROW( _e_ )              XSTestAssertNoThrow( _e_ )
#define ASSERT_ANY_THROW( _e_ )             XSTestAssertAnyThrow( _e_ )
#define ASSERT_FLOAT_EQ( _v1_, _v2_ )       XSTestAssertFloatEqual( _v1_, _v2_ )
#define ASSERT_DOUBLE_EQ( _v1_, _v2_ )      XSTestAssertDoubleEqual( _v1_, _v2_ )
#define ASSERT_LONGDOUBLE_EQ( _v1_, _v2_ )  XSTestAssertLongDoubleEqual( _v1_, _v2_ )
#define ASSERT_HRESULT_SUCCEEDED( _e_ )     XSTestAssertHResultSucceeded( _e_ )
#define ASSERT_HRESULT_FAILED( _e_ )        XSTestAssertHResultFailed( _e_ )
#define ASSERT_NO_FATAL_FAILURE( _e_ )      XSTestAssertNoFatalFailure( _e_ )

#endif

/*******************************************************************************
 * Assertions
 ******************************************************************************/

#define XSTestAssertFalse( _e_ )                                XS::Test::Assert::Boolean( static_cast< bool >( _e_ ), false, XSTest_Internal_XString( _e_ ), __FILE__, __LINE__ )
#define XSTestAssertTrue( _e_ )                                 XS::Test::Assert::Boolean( static_cast< bool >( _e_ ), true,  XSTest_Internal_XString( _e_ ), __FILE__, __LINE__ )
#define XSTestAssertEqual( _v1_, _v2_ )                         XS::Test::Assert::Equality( _v1_, _v2_, true,  std::string( XSTest_Internal_XString( _v1_ ) ) + " == " + std::string( XSTest_Internal_XString( _v2_ ) ), __FILE__, __LINE__ )
#define XSTestAssertNotEqual( _v1_, _v2_ )                      XS::Test::Assert::Equality( _v1_, _v2_, false, std::string( XSTest_Internal_XString( _v1_ ) ) + " != " + std::string( XSTest_Internal_XString( _v2_ ) ), __FILE__, __LINE__ )
#define XSTestAssertLess( _v1_, _v2_ )                          
#define XSTestAssertLessOrEqual( _v1_, _v2_ )                   
#define XSTestAssertGreater( _v1_, _v2_ )                       
#define XSTestAssertGreaterOrEqual( _v1_, _v2_ )                
#define XSTestAssertStringEqual( _s1_, _s2_ )                   
#define XSTestAssertStringNotEqual( _s1_, _s2_ )                
#define XSTestAssertStringEqualCaseInsensitive( _s1_, _s2_ )    
#define XSTestAssertStringNotEqualCaseInsensitive( _s1_, _s2_ ) 
#define XSTestAssertThrow( _e_, _ex_ )                          
#define XSTestAssertNoThrow( _e_ )                              
#define XSTestAssertAnyThrow( _e_ )                              
#define XSTestAssertFloatEqual( _v1_, _v2_ )                    
#define XSTestAssertDoubleEqual( _v1_, _v2_ )                   
#define XSTestAssertLongDoubleEqual( _v1_, _v2_ )               
#define XSTestAssertHResultSucceeded( _e_ )                     
#define XSTestAssertHResultFailed( _e_ )                        
#define XSTestAssertNoFatalFailure( _e_ )                       

/*******************************************************************************
 * Test cases
 ******************************************************************************/
 
#define XSTest( _case_, _name_ )                    XSTest_Internal_TestSetup( _case_, _name_, XSTest_Internal_ClassName( _case_, _name_ ), XS::Test::Case )
#define XSTestFixture( _case_, _name_ )             XSTest_Internal_TestSetup( _case_, _name_, XSTest_Internal_ClassName( _case_, _name_ ), _case_ )
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
        protected:                                                      \
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
        []( void ) { return std::make_shared< _class_ >(); },           \
        __FILE__,                                                       \
        __LINE__                                                        \
    );                                                                  \
                                                                        \
    const XS::Test::Info & _class_::Info( void )                        \
    {                                                                   \
        return _InfoRef;                                                \
    }                                                                   \
                                                                        \
    void _class_::Test( void )                                          \

#endif /* XS_TEST_MACROS_HPP */
