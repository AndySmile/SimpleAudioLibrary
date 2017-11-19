/**
 * Simple Audio Library - No Context Exception.
 *
 * LICENSE:
 *	
 *	The MIT License (MIT)
 *
 *	Copyright (c) 2013-2017 by Andy Liebke. All rights reserved.
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 * 	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in
 *	all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *	THE SOFTWARE.
 *
 * @author		Andy Liebke<coding@andysmiles4games.com>
 * @file		Header/SimpleAudioLib/NoContextException.h
 * @version 	1.0.1 01-Jan-16
 * @copyright	Copyright (c) 2013-2017 by Andy Liebke. All rights reserved. (http://andysmiles4games.com)
 */
#ifndef __NO_CONTEXT_EXCEPTION_H__
#define __NO_CONTEXT_EXCEPTION_H__

#include <SimpleAudioLib/BaseMessageException.h>

/**
 * Simple Audio Library Namespace.
 */
namespace SimpleAudioLib
{
    /**
     * No Device Exception Class.
     */
    class NoContextException : public BaseMessageException
    {
        public:
            
            /**
             * Creates new instance of this class.
             *
             * @param message - string including exception message
             */
            NoContextException(const std::string message) : BaseMessageException(message)
            {
            }
            
            /**
             * Creates new instance by copying another instance of this class.
             *
             * @param src - reference to the other instance of this class
             */
            NoContextException(const NoContextException &src) : BaseMessageException(src)
            {
            }
            
            /**
             * Releases this instance of this class.
             */
            virtual ~NoContextException(void) throw()
            {
            }
    };
}

#endif
