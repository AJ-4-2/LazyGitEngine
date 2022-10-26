#include "Viewport.h"

//take position p (enumerator) and calculate position and size of the rect using the resolution
Viewport::Viewport(Position p, int xRes, int yRes) : Rect()
{
    changePosition(p, xRes, yRes);
    changeColor(255, 255, 255, 255);
}

Viewport::~Viewport()
{
    //dtor
}

//set the renderer to the viewport
void Viewport::setViewport(SDL_Renderer* renderer)
{
    SDL_RenderSetViewport( renderer, &rect);
}

void Viewport::changePosition(Position p, int xRes, int yRes)
{
    pos = p;
     switch (p)
    {
        case VIEWPORT_FULL:
            rect.x = 0;
            rect.y = 0;
            rect.w = xRes;
            rect.h = yRes;
            break;
        case VIEWPORT_LEFT:
            rect.x = 0;
            rect.y = 0;
            rect.w = xRes / 2;
            rect.h = yRes;
            break;
        case VIEWPORT_RIGHT:
            rect.x = xRes / 2;
            rect.y = 0;
            rect.w = xRes / 2;
            rect.h = yRes;
            break;
        case VIEWPORT_TOP:
            rect.x = 0;
            rect.y = 0;
            rect.w = xRes;
            rect.h = yRes / 2;
            break;
        case VIEWPORT_BOTTOM:
            rect.x = 0;
            rect.y = yRes / 2;
            rect.w = xRes;
            rect.h = yRes / 2;
            break;
        case VIEWPORT_TOP_LEFT:
            rect.x = 0;
            rect.y = 0;
            rect.w = xRes / 2;
            rect.h = yRes / 2;
            break;
        case VIEWPORT_TOP_RIGHT:
            rect.x = xRes / 2;
            rect.y = 0;
            rect.w = xRes / 2;
            rect.h = yRes / 2;
            break;
        case VIEWPORT_BOTTOM_LEFT:
            rect.x = 0;
            rect.y = yRes / 2;
            rect.w = xRes / 2;
            rect.h = yRes / 2;
            break;
        case VIEWPORT_BOTTOM_RIGHT:
            rect.x = xRes / 2;
            rect.y = yRes / 2;
            rect.w = xRes / 2;
            rect.h = yRes / 2;
            break;
    }
}
