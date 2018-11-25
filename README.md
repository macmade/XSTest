XSTest
======

[![Build Status](https://img.shields.io/travis/macmade/XSTest.svg?branch=master&style=flat)](https://travis-ci.org/macmade/XSTest)
[![Coverage Status](https://img.shields.io/coveralls/macmade/XSTest.svg?branch=master&style=flat)](https://coveralls.io/r/macmade/XSTest?branch=master)
[![Issues](http://img.shields.io/github/issues/macmade/XSTest.svg?style=flat)](https://github.com/macmade/XSTest/issues)
![Status](https://img.shields.io/badge/status-active-brightgreen.svg?style=flat)
![License](https://img.shields.io/badge/license-mit-brightgreen.svg?style=flat)
[![Contact](https://img.shields.io/badge/contact-@macmade-blue.svg?style=flat)](https://twitter.com/macmade)  
[![Donate-Patreon](https://img.shields.io/badge/donate-patreon-yellow.svg?style=flat)](https://patreon.com/macmade)
[![Donate-Gratipay](https://img.shields.io/badge/donate-gratipay-yellow.svg?style=flat)](https://www.gratipay.com/macmade)
[![Donate-Paypal](https://img.shields.io/badge/donate-paypal-yellow.svg?style=flat)](https://paypal.me/xslabs)

About
-----

**XSTest is a cross-platform C++ unit testing library.**

### Features

 - Cross-platform (macOS, Windows, Linux, Unix)
 - C++11 and greater
 - Header-only library
 - Integration with IDEs such as Xcode and VisualStudio
 - Compatible with GoogleTest

### Primer

XSTest is a header only library, meaning you simply need to include `XSTest/XSTest.hpp` in order to use-it.

Test cases are defined using the `XTest` macro.  
Parameters are the test suite name and the test case name:

```cpp
#include <XSTest/XSTest.hpp>

XSTest( MyTestSuite, MyTestCase )
{
    /* Test case body */
}
```

Note that tests cases and test suites are run in random order for each invocation.

#### Assertions

Test case body is user-defined code, but the test case result is controlled using assertions macros:

```cpp
#include <XSTest/XSTest.hpp>

XSTest( MyTestSuite, MyTestCase )
{
    XSTestAssertTrue( true );         /* Will succeed */
    XSTestAssertEqual( true, false ); /* Will fail */
}
```

#### Main function

Usually, the unit tests are packaged into an executable.  
You can define a `main` function that will run all registered tests using:

```cpp
#include <XSTest/XSTest.hpp>

int main( int argc, char * argv[] )
{
    return XS::Test::RunAll();
}
```

As an alternative, you can define the `XS_TEST_MAIN` macro.  
This will automatically generate a `main` function for you.
```cpp
#define XS_TEST_MAIN
#include <XSTest/XSTest.hpp>
```

#### Fixtures

XSTest supports _fixtures_, that is test cases that will run from a user defined class representing the test suite.  
This allows custom setup to be performed prior to running a test case.

Fixtures requires a user-defined class, inheriting from `XS::Test::Case`, and are defined with the `XSTestFixture` macro:

```cpp
#include <XSTest/XSTest.hpp>

class MyFixture: XS::Test::Case
{
    protected:
        
        void SetUp( void ) override
        {
            this->_x = 42;
        }
        
        void TearDown( void ) override
        {}
        
        int _x = 0;
};

XSTestFixture( MyFixture, MyTestCase )
{
    XSTestAssertEqual( this->_x, 42 ); /* Will succeed */
}
```

For each test case, a new instance of the fixture class will be created.  
`SetUp` and `TearDown` will be automatically called, allowing you to add custom behaviours to your test suite.

### IDE Integration

...

### GoogleTest Compatibility

XSTest aims to be compatible with GoogleTest, making it easy to migrate.

Most assertions from GoogleTest can be used seamlessly with XSTest, by defining the `XSTEST_GTEST_COMPAT` macro:

```cpp
#define XSTEST_GTEST_COMPAT
#include <XSTest/XSTest.hpp>

TEST( MyTestSuite, MyTestCase )
{
    ASSERT_TRUE( true );
}
```

Supported macros are:

 - `TEST`
 - `TEST_F`
 - `ASSERT_FALSE`
 - `ASSERT_TRUE`
 - `ASSERT_EQ`
 - `ASSERT_NE`
 - `ASSERT_LT`
 - `ASSERT_LE`
 - `ASSERT_GT`
 - `ASSERT_GE`
 - `ASSERT_STREQ`
 - `ASSERT_STRNE`
 - `ASSERT_STRCASEEQ`
 - `ASSERT_STRCASENE`
 - `ASSERT_THROW`
 - `ASSERT_NO_THROW`
 - `ASSERT_ANY_THROW`
 - `ASSERT_FLOAT_EQ`
 - `ASSERT_DOUBLE_EQ`
 - `ASSERT_LONGDOUBLE_EQ`
 - `ASSERT_HRESULT_SUCCEEDED`
 - `ASSERT_HRESULT_FAILED`
 - `ASSERT_NO_FATAL_FAILURE`


### Documentation

...

License
-------

XSTest is released under the terms of the MIT license.

Repository Infos
----------------

    Owner:          Jean-David Gadina - XS-Labs
    Web:            www.xs-labs.com
    Blog:           www.noxeos.com
    Twitter:        @macmade
    GitHub:         github.com/macmade
    LinkedIn:       ch.linkedin.com/in/macmade/
    StackOverflow:  stackoverflow.com/users/182676/macmade
