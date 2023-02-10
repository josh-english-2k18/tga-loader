# Targa (TGA) Plug-in Library
### Load TGA Textures - reference implementation in C

## Overview
I found that the TGA file format is quite useful in game development, and is used extensively by a number of modern game-engines, including Unreal Engine 3. There are a number of online examples and tutorials describing how to bang out some C or C++ code to load a TGA file so that it can be used by a DirectX or OpenGL application. However, I wanted to create my own library that solves the following problems:

* It can load the file into a graphics-library compatible format in a single pass (thus being much faster than the online examples I’ve read).
* Handles arbitrary bit-length encoding.
* Handles run-length encoded (RLE) Targa files.
* Automatically converts any TGA file to my desired format – 32-bit RGBA. If an alpha channel is missing, a default one is automatically created. It also converts from black & white encoding.
* Allows me to apply color-channel masking or replacement by modifying the serialized RGBA value, allowing me to manipulate the image prior to creation as a graphics-library texture.

Given that I’ve never found a real use for Targa color mappings, I dropped support for using them in my reference library. The reference library I created is written in C, and compiles natively on Windows, Linux and Mac OS X. This repository contains both a Microsoft Visual Studio solution and a simple makefile, in order to make this as portable as possible.

## Execute Example

### Building with Make
Simply run:
```
$ make
gcc -g -O -Wall -c src/c/targa/targa.c -o src/c/targa/targa.o
rm -f lib/libtarga*
ar cq lib/libtarga.a src/c/targa/targa.o
gcc -g -O -Wall src/c/targa/targaDemo.c -o bin/targaDemo \
        -Llib -ltarga
```

### Building with Visual Studio
Simply open the solution and build it.

### Execution
Run the resulting binary from one of the above build steps, e.g.
```
$ ./bin/targaDemo.exe
Simple TARGA library demonstration application.
Copyright (C) 2006 - 2009 by Joshua S. English.
Written by Joshua S. English.

Loaded 'assets/targaTest.RLE.tga', image length: 262144, (256 x 256) pixels
Loaded 'assets/targaTest.NON-RLE.tga', image length: 262144, (256 x 256) pixels
```
