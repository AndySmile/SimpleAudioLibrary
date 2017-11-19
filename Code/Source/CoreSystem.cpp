// Copyright (c) 2013-2017 by Andy Liebke. All rights reserved.

/**
 * Simple Audio Library - Core System Model.
 *
 * This is the core class of this library. It is implemented as a singleton class.
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
#include <SimpleAudioLib/CoreSystem.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

/**
 * Simple Audio Library Namespace.
 */
namespace SimpleAudioLib
{
    /**
     * Stores the only instance of this class.
     *
     * @note This is part of the Singleton-Pattern.
     */
    CoreSystem* CoreSystem::_instance = NULL;
    
    /**
     * Creates new instance of this class.
     */
    CoreSystem::CoreSystem(void) :
        _device(NULL),
        _context(NULL)
    {
    }
    
    /**
     * Creates new instance by copying another instance of this class.
     *
     * @param src - reference to the other instance of this class
     */
    CoreSystem::CoreSystem(const CoreSystem &src) :
        _device(NULL),
        _context(NULL)
    {
    }

    /**
     * Releases this instance of this class.
     */
    CoreSystem::~CoreSystem(void)
    {
    }
    
    /**
     * Assigns data by another instance of this class.
     *
     * @param src - reference to the other instance of this class
     * @return CoreSystem - reference to this instance of this class
     */
    CoreSystem& CoreSystem::operator = (const CoreSystem &src)
    {
        return *this;
    }
    
    /**
     * Returns only existing instance of this class.
     *
     * In case that the instance doesn't exist yet, 
     * this method will create one.
     *
     * @note This is part of the Singleton-Pattern.
     * @return CoreSystem - reference to the only existing instance of this class.
     */
    CoreSystem& CoreSystem::getInstance(void)
    {
        if(_instance == NULL){
            _instance = new CoreSystem();
        }
        
        return *_instance;
    }
    
    /**
     * Releases memory of this instance.
     *
     * @note This is part of the Singleton-Pattern.
     */
    void CoreSystem::release(void)
    {
        if (_instance != NULL) {
            _instance->_release();
            
            delete _instance;
            _instance = NULL;
        }
    }
    
    /**
     * Releases reserved memory of this module.
     */
    void CoreSystem::_release(void)
    {
        if (this->_context != NULL) {
            alcMakeContextCurrent(NULL);
            alcDestroyContext(this->_context);
        }
        
        if (this->_device != NULL) {
            alcCloseDevice(this->_device);
        }
    }
    
    /**
     * Creates a new audio entity including audio data from an audio file.
     *
     * @param path - string including path to the audio file
     * 
     * @return AudioEntity - entity class in case that the file was successfuly loaded otherwise NULL
     *
     * @throws InvalidPathException 	- in case that given path parameter is empty
     * @throws CorruptedFileException	- in case that the audio file couldn't be opened
     */
    AudioEntity* CoreSystem::_loadWaveFile(const std::string path) const throw(InvalidPathException, CorruptedFileException)
    {
        AudioEntity* entity = NULL;
        
        if (path.empty()) {
            throw InvalidPathException("Load wave file failure: no path to file defined!");
        }
        
        std::ifstream file(path.c_str(), std::ifstream::binary);
        
        if (!file.is_open()) {
            throw CorruptedFileException("Load wave file failure: file couldn't be opened!");
        } else {
            char chunkId[5] 	= "\0";
            unsigned int size 	= 0;
        
            // read header
            file.read(chunkId, 4);
            file.read((char*)&size, 4);
        
            chunkId[4] = '\0';
#ifdef _DEBUG		
            std::cout << "Chunk ID: " << chunkId << std::endl;
            std::cout << "Size: " << size << "bytes" << std::endl;
#endif		
            file.read(chunkId, 4);
        
            chunkId[4] = '\0';
#ifdef _DEBUG			
            std::cout << "Wave ID: " << chunkId << std::endl;
#endif		
            // read first chunk header
            file.read(chunkId, 4);
            file.read((char*)&size, 4);
        
            chunkId[4] = '\0';
#ifdef _DEBUG			
            std::cout << "Chunk ID: " << chunkId << std::endl;
            std::cout << "Size: " << size << "bytes" << std::endl;
#endif		
            // read first chunk content
            short formatTag 		= 0;
            short channels 			= 0;
            int samplesPerSec 		= 0;
            int averageBytesPerSec 	= 0;
            short blockAlign 		= 0;
            short bitsPerSample 	= 0;
        
            file.read((char*)&formatTag, 2);
            file.read((char*)&channels, 2);
            file.read((char*)&samplesPerSec, 4);
            file.read((char*)&averageBytesPerSec, 4);
            file.read((char*)&blockAlign, 2);
            file.read((char*)&bitsPerSample, 2);
            
            if (size > 16) {
                file.seekg((int)file.tellg() + (size - 16));
            }
            
#ifdef _DEBUG			
            switch (formatTag) {
                case 0x0001: {
                    std::cout << "PCM Format" << std::endl;
                } break;
            
                case 0x0003: {
                    std::cout << "IEEE Float Format" << std::endl;
                } break;
            
                case 0x0006: {
                    std::cout << "8-bit ITU-T G.711 A-law Format" << std::endl;
                } break;
            
                case 0x0007: {
                    std::cout << "8-bit ITU-T G.711 mi-law Format" << std::endl;
                } break;
            
                default: {
                    std::cout << "Unknown format tag" << std::endl;
                } break;
            }

            std::cout << "Channels: " << channels << std::endl;
            std::cout << "Samples Per Second: " << samplesPerSec << std::endl;
            std::cout << "average bytes per second: " << averageBytesPerSec << std::endl;
            std::cout << "Block align: " << blockAlign << std::endl;
            std::cout << "bit per sample: " << bitsPerSample << std::endl;
#endif		
            // read data chunk header
            file.read(chunkId, 4);
            file.read((char*)&size, 4);
        
            chunkId[4] = '\0';
            
#ifdef _DEBUG			
            std::cout << "Chunk ID: " << chunkId << std::endl;
            std::cout << "Size: " << size << "bytes" << std::endl;
#endif		
            unsigned char* data = new unsigned char[size];
        
            file.read((char*)data, size);
            
            entity = new AudioEntity(data, size, samplesPerSec, channels);
        
            delete[] data;
            data = NULL;
            
#ifdef _DEBUG
            std::cout << "--- Done\n" << std::endl;
#endif			
        }
        
        file.close();
        
        return entity;
    }
    
    /**
     * Initilizes this system with the default audio device.
     *
     * @throws NoDeviceException - in case that no device is available
     */
    void CoreSystem::initWithDefaultDevice(void) throw(NoDeviceException, NoContextException)
    {
        this->_device = alcOpenDevice(NULL);
        
        if (this->_device == NULL) {
            throw NoDeviceException("Init with default device failure: Couldn't open a connection to audio device!");
        }
        
        this->_context = alcCreateContext(this->_device, NULL);
        
        if (this->_context == NULL) {
            throw NoContextException("Init with default device failure: Couldn't create OpenAL context!");
        } else {
            alcMakeContextCurrent(this->_context);
        }
    }
    
    /**
     * Creates a new audio entity including audio data from an audio file.
     *
     * @param path - string including path to the audio file
     * @return object of the audio entity class in case that the file was successfuly loaded otherwise NULL
     * @throws InvalidPathException 	- in case that given path parameter is empty
     * @throws CorruptedFileException	- in case that the audio file couldn't be opened
     */
    AudioEntity* CoreSystem::createAudioEntityFromFile(const std::string path) const throw(InvalidPathException, CorruptedFileException)
    {
        return this->_loadWaveFile(path);
    }
    
    /**
     * Assigns position to listener.
     *
     * @param x - value on the x-axis of listener position
     * @param y - value on the y-axis of listener position
     * @param z - value on the z-axis of listener position
     */
    void CoreSystem::setListenerPosition(const float x, const float y, const float z)
    {
        alListener3f(AL_POSITION, x, y, z);
    }
    
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
    void CoreSystem::setListenerOrientation(const float atX, const float atY, const float atZ, const float upX, const float upY, const float upZ)
    {
        float orientation[6] = {atX, atY, atZ, upX, upY, upZ};
        
        alListenerfv(AL_ORIENTATION, orientation);
    }
    
    /**
     * Assigns velocity to listener.
     *
     * @param x - value on the x-axis of listener velocity
     * @param y - value on the y-axis of listener velocity
     * @param z - value on the z-axis of listener velocity
     */
    void CoreSystem::setListenerVelocity(const float x, const float y, const float z)
    {
        alListener3f(AL_VELOCITY, x, y, z);
    }
}
