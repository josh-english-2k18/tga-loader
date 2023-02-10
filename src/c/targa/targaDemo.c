/*
 * targaDemo.c
 *
 * Copyright (c) 2023 Josh English
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Notes:
 *
 * A plugin to read targa (TGA) image files into an OpenGL-compatible RGBA
 * format, simple demonstration program.
 *
 * Written by Joshua S. English.
 */

// preprocessor directives

#include <stdio.h>
#include "targa.h"


// define constants

#define TARGA_RLE_FILENAME					"assets/targaTest.RLE.tga"

#define TARGA_NON_RLE_FILENAME				"assets/targaTest.NON-RLE.tga"


// main function

int main(int argc, char *argv[])
{
	Targa targa;

	printf("Simple TARGA library demonstration application.\n");
	printf("Copyright (C) 2006 - 2009 by Joshua S. English.\n");
	printf("Written by Joshua S. English.\n\n");

	// an RLE TARGA File example

	// initialize the struct

	if(targa_init(&targa) < 0) {
		return 1;
	}

	// load the TARGA from a file

	if(targa_loadFromFile(&targa, TARGA_RLE_FILENAME) < 0) {
		return 1;
	}

	printf("Loaded '%s', image length: %i, (%i x %i) pixels\n",
			TARGA_RLE_FILENAME, targa.imageLength, targa.width, targa.height);

	// apply a red-channel mask of 255

	if(targa_applyRgbaMask(&targa, TARGA_COLOR_RED, 255) < 0) {
		return 1;
	}

	// replace the blue-channel with color 127

	if(targa_applyRgbaMask(&targa, TARGA_COLOR_BLUE, 127) < 0) {
		return 1;
	}

	// free the struct

	if(targa_free(&targa) < 0) {
		return 1;
	}


	// an non-RLE TARGA File example

	// initialize the struct

	if(targa_init(&targa) < 0) {
		return 1;
	}

	// load the TARGA from a file

	if(targa_loadFromFile(&targa, TARGA_NON_RLE_FILENAME) < 0) {
		return 1;
	}

	printf("Loaded '%s', image length: %i, (%i x %i) pixels\n",
			TARGA_NON_RLE_FILENAME, targa.imageLength, targa.width,
			targa.height);

	// apply a red-channel mask of 255

	if(targa_applyRgbaMask(&targa, TARGA_COLOR_RED, 255) < 0) {
		return 1;
	}

	// replace the blue-channel with color 127

	if(targa_applyRgbaMask(&targa, TARGA_COLOR_BLUE, 127) < 0) {
		return 1;
	}

	// free the struct

	if(targa_free(&targa) < 0) {
		return 1;
	}


	// exit program

	return 0;
}

