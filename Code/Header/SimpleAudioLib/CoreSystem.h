/**
 * Simple Audio Library - Core System Model.
 *
 * This is the core class of this library. It is implemented as a singleton class.
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
 * @file		Header/SimpleAudioLib/CoreSystem.h
 * @version		1.2.2 03-Jan-16
 * @copyright	Copyright (c) 2013-2017 by Andy Liebke. All rights reserved. (http://andysmiles4games.com)
 */
#ifndef __SIMPLE_AUDIO_SYSTEM_H__
#define __SIMPLE_AUDIO_SYSTEM_H__

#include <SimpleAudioLib/NoDeviceException.h>
#include <SimpleAudioLib/NoContextException.h>
#include <SimpleAudioLib/CorruptedFileException.h>
#include <SimpleAudioLib/InvalidPathException.h>
#include <SimpleAudioLib/AudioEntity.h>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#define SIMPLE_AUDIO_LIB_VERSION "0.2.0"
#define SIMPLE_AUDIO_LIB_VERSION_0_2_0 1

/**
 * Simple Audio Library Namespace.
 */
namespace SimpleAudioLib
{
    /**
     * Simple Audio System Class.
     *
     * @note This class is implemented as singleton.
     */
    class CoreSystem
    {
        public:
            /**
             * Returns only existing instance of this class.
             *
             * In case that the instance doesn't exist yet, 
             * this method will create one.
             *
             * @note This is part of the Singleton-Pattern.
             * @return reference to the only existing instance of this class.
             */
            static CoreSystem& getInstance(void);
            
            /**
             * Releases memory of this instance.
             *
             * @note This is part of the Singleton-Pattern.
             */
            static void release(void);
            
            /**
             * Initilizes this system with the default audio device.
             *
             * @throws NoDeviceException - in case that no device is available
             */
            void initWithDefaultDevice(void) throw(NoDeviceException, NoContextException);
            
            /**
             * Creates a new audio entity including audio data from an audio file.
             *
             * @param path - string including path to the audio file
             * @return object of the audio entity class in case that the file was successfuly loaded otherwise NULL
             * @throws InvalidPathException 	- in case that given path parameter is empty
             * @throws CorruptedFileException	- in case that the audio file couldn't be opened
             */
            AudioEntity* createAudioEntityFromFile(const std::string path) const  throw(InvalidPathException, CorruptedFileException);
            
            /**
             * Assigns position to listener.
             *
             * @param x - value on the x-axis of listener position
             * @param y - value on the y-axis of listener position
             * @param z - value on the z-axis of listener position
             */
            void setListenerPosition(const float x, const float y, const float z);
            
            /**
             * Assigns orientation to listener.
             *
             * @param atX - value on the x-axis of listener points at
             * @param atY - value on the y-axis of listener points at
             * @param atZ - value on the z-axis of listener points at
             * @param upX - value on the x-axis of listener up vector
             * @param upY - value on the y-axis of listener up vector
             * @param upZ - value on the z-axis of listener up vector
             */
            void setListenerOrientation(const float atX, const float atY, const float atZ, const float upX, const float upY, const float upZ);
            
            /**
             * Assigns velocity to listener.
             *
             * @param x - value on the x-axis of listener velocity
             * @param y - value on the y-axis of listener velocity
             * @param z - value on the z-axis of listener velocity
             */
            void setListenerVelocity(const float x, const float y, const float z);
            
        private:
            /**
             * Creates new instance of this class.
             */
            CoreSystem(void);
            
            /**
             * Creates new instance by copying another instance of this class.
             *
             * @param src - reference to the other instance of this class
             */
            CoreSystem(const CoreSystem &src);
            
            /**
             * Releases this instance of this class.
             */
            ~CoreSystem(void);
            
            /**
             * Assigns data by another instance of this class.
             *
             * @param src - reference to the other instance of this class
             * @return reference to this instance of this class
             */
            CoreSystem& operator = (const CoreSystem &src);	
            
            /**
             * Releases reserved memory of this module.
             */
            void _release(void);
            
            /**
             * Creates a new audio entity including audio data from an audio file.
             *
             * @param path - string including path to the audio file
             * @return object of the audio entity class in case that the file was successfuly loaded otherwise NULL
             * @throws InvalidPathException 	- in case that given path parameter is empty
             * @throws CorruptedFileException	- in case that the audio file couldn't be opened
             */
            AudioEntity* _loadWaveFile(const std::string path) const throw(InvalidPathException, CorruptedFileException);
            
        private:
            /**
             * Stores the only instance of this class.
             *
             * @note This is part of the Singleton-Pattern.
             */
            static CoreSystem* _instance;
            
            /**
             * Stores selected audio device of this system.
             */
            ALCdevice* _device;
            
            /**
             * Stores active context of this system 
             */
            ALCcontext* _context;
    };
}

#endif
