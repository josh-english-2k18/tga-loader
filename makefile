#
# makefile
#
# The make file for the TARGA file-loading example.
#
# Written by Joshua S. English (08/2009).
#
# Intended systems: Cygwin, MinGW (native gcc for Windows), Linux, 64-bit Linux
#

# define platform settings

#RM_COMMAND				= del
RM_COMMAND				= rm -f

#OBJ_EXT				= .obj
OBJ_EXT					= .o

#LIB_EXT				= .lib
LIB_EXT					= .a

#APP_EXT				= .exe
APP_EXT					=


# define compiler settings

CC						= gcc

CFLAGS					= \
			-g \
			-O \
			-Wall

APP_FLAGS				= \
			-Llib \
			-ltarga


# define build targets

OBJECTS					= \
			src/c/targa/targa$(OBJ_EXT)

LIBRARIES				= \
			lib/libtarga$(LIB_EXT)

APPLICATIONS			= \
			bin/targaDemo$(APP_EXT)


# define make target

all:	$(OBJECTS) $(LIBRARIES) $(APPLICATIONS)


# define build instructions

src/c/targa/targa$(OBJ_EXT): \
			src/c/targa/targa.h \
			src/c/targa/targa.c
	$(CC) $(CFLAGS) -c src/c/targa/targa.c -o src/c/targa/targa$(OBJ_EXT)

lib/libtarga$(LIB_EXT):		$(OBJECTS)
	$(RM_COMMAND) lib/libtarga*
	ar cq lib/libtarga$(LIB_EXT) $(OBJECTS)

bin/targaDemo$(APP_EXT): \
			src/c/targa/targaDemo.c
	$(CC) $(CFLAGS) src/c/targa/targaDemo.c -o bin/targaDemo$(APP_EXT) \
		$(APP_FLAGS)


# cleanup compiled binaries

clean:
	$(RM_COMMAND) $(OBJECTS)
	$(RM_COMMAND) $(LIBRARIES)
	$(RM_COMMAND) $(APPLICATIONS)

