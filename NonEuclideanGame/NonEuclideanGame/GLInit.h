#ifndef GLINIT_H
#define GLINIT_H

#include <iostream>
#include "SDL.h"
#include "glew.h"

/*
Call to create a window, initialize a GL context and initialize the GLEW library.
Necessary to start drawing to a window.
*/
void init(SDL_Window*& window);

/*
Call before creating a GL context to set attributes.
Used by init.
*/
void initGLAttributes(int glMajorVersion, int glMinorVersion, int useDoubleBuffering);

/*
Call when program is done.
*/
void GLTearDown(SDL_Window*& window);

#endif