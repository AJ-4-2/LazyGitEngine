#ifndef VIEWPORT_H
#define VIEWPORT_H
#include <iostream>
#include <SDL.h>
#include "Rect.h"

/**
 * Sets up the rect for the viewport and sets a renderer to it
 * uses Rect as a parent class
 */
enum Position
    {
        VIEWPORT_FULL,
        VIEWPORT_LEFT,
        VIEWPORT_RIGHT,
        VIEWPORT_TOP,
        VIEWPORT_BOTTOM,
        VIEWPORT_TOP_LEFT,
        VIEWPORT_TOP_RIGHT,
        VIEWPORT_BOTTOM_LEFT,
        VIEWPORT_BOTTOM_RIGHT
    };

class Viewport : public Rect
{

        public:
        Viewport(Position, int, int);
        virtual ~Viewport();
        void setViewport(SDL_Renderer*);
        void changePosition(Position, int, int);

    protected:

    private:
        Position pos;

};

#endif // VIEWPORT_H
