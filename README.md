# Simple Audio Library

This is a simple audio library using OpenAL. It was made with the thought in mind to have a pretty simple tool
for playing sound/music in a game or another multimedia application.

WARNING: This is a pretty early version, keep in mind, that method/classes can be removed/renamed/changed at any time.

## License

Simple Audio Library is released under the [MIT license](http://opensource.org/licenses/MIT).

## Platform

### Mac OS X

This library is available for Mac OS X by compiling it via make and GCC/Clang.

### Windows

This library includes the Visual Studio Express 2010 solution files and is therefore 
available for Windows projects as well.

## How to build

### Mac OS X

- Open your console and go to ```"[directory of your copy]/Code/"```
- Enter: ```make```

Now it'll compile the library on your machine and after it's finished it copies all header files into:
```"[directory of your copy]/Header/"``` and the bineary to
```"[directory of your copy]/Lib/"```.

So, to use this library in your application, all you have to do is to set the header path to:
```"[directory of your copy]/Header/"``` and the library path to:
```"[directory of your copy]/Lib/"``` and here we go, you're ready to work with this libary.

### Visual Studio Code

The current version also includes a tasks configuration file for Visual Studio Code. All you have to
do is to open the project in Visual Studio Code and hit ```CTRL + Shift + B``` to start the build process
directly in Visual Studio Code.

```NOTE: The build process in Visual Studio Code triggers the make file and is therefore only available for those platforms where GNU make is installed and functional. Currently it was only tested on Mac OS X.```

### Visual Studio Express 2010

Open the Visual Studio Express 2010 solution files and compile the library the usual way within Visual Studio Express 2010.
Afterwards you can add the library into your project like every other library.

## Code Example

This is the simplest version to work with this library:

```c++
// include needed header file
#include <SimpleAudioLib/CoreSystem.h>

// before you can use this library, you have to initialize it
SimpleAudioLib::CoreSystem& system = SimpleAudioLib::CoreSystem::getInstance();

system.initWithDefaultDevice();

// load audio file in wave format
SimpleAudioLib::AudioEntity* sound = system.createAudioEntityFromFile("YourAudioFile.wav");

// play sound
sound.play();

// clean up
delete sound;
sound = NULL;

SimpleAudioLib::CoreSystem::release();
```