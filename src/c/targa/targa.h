/*
 * targa.h
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
 * format, header file.
 *
 * Written by Joshua S. English.
 *
 *
 * The TARGA Specification:
 *
 *	Position:	Length:		Description:
 *	--------	------		-----------
 *	0			1			length of the image ID
 *	1			1			type of color map included (if any)
 *								0	=>	no color map
 *								1	=>	has color map
 *	2			1			image type
 *								0	=>	no image data
 *								1	=>	color-mapped image
 *								2	=>	true-color image
 *								3	=>	black & white image
 *								9	=>	RLE color-mapped image
 *								10	=>	RLE true-color image
 *								11	=>	RLE black & white image
 *	3			2			index of the first color-map entry as an offest
 *							into the color-map table
 *	5			2			color-map length (number of entries)
 *	7			1			color-map entry length - (number of bits per entry)
 *	8			2			x-origin of image
 *	10			2			y-origin of image
 *	12			2			image width in pixels
 *	14			2			image height in pixels
 *	16			1			pixel depth - the number of bits per pixel
 *	17			1			image descriptor
 *	n			var			image id - only exists if non-zero
 *	n			var			color-map data - only exists if non-zero
 *	n			var			image data
 */

#if !defined(_TARGA_H)

#define _TARGA_H


// define targa public constants

#define TARGA_COLOR_RED										1
#define TARGA_COLOR_GREEN									2
#define TARGA_COLOR_BLUE									3
#define TARGA_COLOR_ALPHA									4


// define targa public data types

typedef struct _Targa {
	int width;
	int height;
	int imageLength;
	unsigned char *image;
} Targa;


// declare targa public functions

/**
 * targa_init()
 *
 * Initilize the Targa structure for utilization.
 *
 * @param	targa(in)	The Targa struct to initialize.
 *
 * @return	An integer where zero is pass, less than zero is failure.
 */
int targa_init(Targa *targa);


/**
 * targa_free()
 *
 * Free the Targa structure.
 *
 * @param	targa(in)	The Targa struct to free.
 *
 * @return	An integer where zero is pass, less than zero is failure.
 */
int targa_free(Targa *targa);


/**
 * targa_getDimensions()
 *
 * Obtain the width and height in pixels of a loaded Targa image.
 *
 * @param	targa(in)	The Targa struct of a loaded image.
 *
 * @param	width(out)	The width in pixels of a loaded Targa image.
 *
 * @param	height(out)	The height in pixels of a loaded Targa image.
 *
 * @return	An integer where zero is pass, less than zero is failure.
 */
int targa_getDimensions(Targa *targa, int *width, int *height);


/**
 * targa_getImageLength()
 *
 * Obtain the length in bytes of the serialized RGBA image.
 *
 * @param	targa(in)			The Targa struct of a loaded image.
 *
 * @param	imageLength(out)	The length in bytes of the RGBA image.
 *
 * @return	An integer where zero is pass, less than zero is failure.
 */
int targa_getImageLength(Targa *targa, int *imageLength);


/**
 * targa_getRgbaTexture()
 *
 * Obtain the serialized RGBA texture and its' length from a Targa image.
 *
 * @param	targa(in)			The Targa struct of a loaded image.
 *
 * @param	texture(out)		The serialized RGBA image pointer.
 *
 * @param	textureLength(out)	The serialized RGBA image length in bytes.
 *
 * @return	An integer where zero is pass, less than zero is failure.
 */
int targa_getRgbaTexture(Targa *targa, char **texture, int *textureLength);


/**
 * targa_loadFromFile()
 *
 * Load a targa file and decode it into a 32-bit RGBA serialized image.
 *
 * @param	targa(in)		The Targa struct of an image to load.
 *
 * @param	filename(in)	The filename of the image to load.
 *
 * @return	An integer where zero is pass, less than zero is failure.
 */
int targa_loadFromFile(Targa *targa, char *filename);


/**
 * targa_loadFromData()
 *
 * Load the targa from an in-memory location and decode it into a 32-bit RGBA
 * serialize image.
 *
 * @param	targa(in)		The Targa struct an image to load.
 *
 * @param	data(in)		A pointer to an in-memory location containing a
 *							Targa image.
 *
 * @param	dataLength(in)	The length of the Targa in-memory image.
 *
 * @return	An integer where zero is pass, less than zero is failure.
 */
int targa_loadFromData(Targa *targa, unsigned char *data, int dataLength);


/**
 * targa_applyRgbaMask()
 *
 * Apply a red, green, blue or alpha-channel additive color-mask to a loaded
 * Targa image.
 *
 * @param	targa(in)		The Targa struct of a loaded image.
 *
 * @param	colorType(in)	The color channel to mask.
 *
 * @param	value(in)		The color code (0 - 255) to mask.
 *
 * @return	An integer where zero is pass, less than zero is failure.
 */
int targa_applyRgbaMask(Targa *targa, int colorType, unsigned char value);


/**
 * targa_setRgbaChannel()
 *
 * Apply a red, green, blue or alpha-channel additive color-channel
 * replacement to a loaded Targa image.
 *
 * @param	targa(in)		The Targa struct of a loaded image.
 *
 * @param	colorType(in)	The color channel to replace.
 *
 * @param	value(in)		The color code (0 - 255) to replace.
 *
 * @return	An integer where zero is pass, less than zero is failure.
 */
int targa_setRgbaChannel(Targa *targa, int colorType, unsigned char value);


#endif // _TARGA_H

