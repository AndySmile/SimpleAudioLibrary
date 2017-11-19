// Copyright (c) 2013-2017 by Andy Liebke. All rights reserved.

/**
 * Simple Audio Library - Base Message Exception.
 *
 * LICENSE:
 *  
 *  The MIT License (MIT)
 *  
 *  Copyright (c) 2013-2017 by Andy Liebke. All rights reserved.
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */
#include <SimpleAudioLib/BaseMessageException.h>

/**
 * Simple Audio Library Namespace.
 */
namespace SimpleAudioLib
{
    /**
     * Creates new instance of this class.
     *
     * @param message - string including exception message
     */
    BaseMessageException::BaseMessageException(const std::string message) : 
        std::exception(),
        _message(message)
    {
    }
    
    /**
     * Creates new instance by copying another instance of this class.
     *
     * @param src - reference to the other instance of this class
     */
    BaseMessageException::BaseMessageException(const BaseMessageException &src) :
        _message(src._message)
    {
    }

    /**
     * Releases this instance of this class.
     */
    BaseMessageException::~BaseMessageException(void) throw()
    {
    }
    
    /**
     * Assigns data by another instance of this class.
     *
     * @param src - reference to the other instance of this class
     * @return BaseMessageException - reference to this instance of this class
     */
    BaseMessageException& BaseMessageException::operator = (const BaseMessageException &src)
    {
        this->_message = src._message;
        
        return *this;
    }
    
    /**
     * Returns exception message.
     *
     * @return string - exception message
     */
    const char* BaseMessageException::what(void) const throw()
    {
        return this->_message.c_str();
    }
}
