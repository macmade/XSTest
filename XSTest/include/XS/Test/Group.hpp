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
 * @header      Group.hpp
 * @author      Jean-David Gadina - www.xs-labs.com
 * @copyright   (c) 2018, Jean-David Gadina - www.xs-labs.com
 */

#ifndef XS_TEST_GROUP_HPP
#define XS_TEST_GROUP_HPP

#include <memory>
#include <string>
#include <iostream>
#include <vector>

namespace XS
{
    namespace Test
    {
        class Info;
        
        class Group
        {
            public:
                
                Group( const std::string & name, std::vector< Info > infos );
                Group( const Group & o );
                virtual ~Group( void );
                
                Group & operator =( Group o );
                
                std::string         GetName( void )  const;
                std::vector< Info > GetInfos( void ) const;
                
                bool Run( std::ostream & os );
                
                friend void swap( Group & o1, Group & o2 );
                
            private:
                
                class IMPL;
                
                std::shared_ptr< IMPL > impl;
        };
    }
}

#endif /* XS_TEST_GROUP_HPP */
