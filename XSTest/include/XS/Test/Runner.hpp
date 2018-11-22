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
 * @header      Runner.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_RUNNER_HPP
#define XS_TEST_RUNNER_HPP

#include <iostream>
#include <memory>
#include <XS/Test/Optional.hpp>

namespace XS
{
    namespace Test
    {
        class Suite;
        
        class Runner
        {
            public:
                
                Runner( const std::vector< Suite > & suites );
                Runner( const Runner & o );
                virtual ~Runner( void );
                
                Runner & operator =( Runner o );
                
                std::vector< Suite > GetSuites( void ) const;
                
                bool Run( Optional< std::reference_wrapper< std::ostream > > os );
                
                friend void swap( Runner & o1, Runner & o2 );
                
            private:
                
                class IMPL;
                
                std::shared_ptr< IMPL > impl;
        };
    }
}

#endif /* XS_TEST_RUNNER_HPP */
