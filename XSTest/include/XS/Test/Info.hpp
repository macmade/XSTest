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
 * @header      Info.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_INFO_HPP
#define XS_TEST_INFO_HPP

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <XS/Test/Optional.hpp>
#include <XS/Test/Failure.hpp>

namespace XS
{
    namespace Test
    {
        class Suite;
        class Case;
        
        class Info
        {
            public:
                
                enum class Status
                {
                    Unknown,
                    Running,
                    Success,
                    Failed
                };
                
                static Info &               Register( const std::string & testCaseName, const std::string & testName, const std::function< std::shared_ptr< Case >( void ) > createTest, const std::string & file, int line );
                static std::vector< Suite > All( void );
                
                Info( const Info & o );
                Info( Info && o ) noexcept;
                ~Info( void );
                
                Info & operator =( Info o );
                
                std::string         GetName( void )      const;
                std::string         GetSuiteName( void ) const;
                std::string         GetCaseName( void )  const;
                Status              GetStatus( void )    const noexcept;
                std::string         GetFile( void )      const;
                int                 GetLine( void )      const noexcept;
                Optional< Failure > GetFailure( void )   const;
                
                bool Run( Optional< std::reference_wrapper< std::ostream > > os );
                
                friend void swap( Info & o1, Info & o2 ) noexcept;
                
            private:
                
                Info( const std::string & testCase, const std::string & testName, const std::function< std::shared_ptr< Case >( void ) > createTest, const std::string & file, int line );
                
                class IMPL;
                
                std::unique_ptr< IMPL > impl;
        };
    }
}

#endif /* XS_TEST_INFO_HPP */
