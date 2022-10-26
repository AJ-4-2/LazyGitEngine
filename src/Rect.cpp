#include "Rect.h"


Rect::Rect()
{

}

Rect::Rect(int x, int y, int  w, int  h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

//rect: x, y, width, height, red, green, blue, alpha
Rect::Rect(int rectData[8])
{
    rect.x = rectData[0];
    rect.y = rectData[1];
    rect.w = rectData[2];
    rect.h = rectData[3];
    red = rectData[4];
    green = rectData[5];
    blue = rectData[6];
    alpha = rectData[7];
}

Rect::~Rect()
{

}

void Rect::drawToRenderer(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    SDL_RenderFillRect(renderer, &rect);
}

void Rect::transformRect(int x, int y, int width, int height)
{
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
}

void Rect::changeColor(int r, int g, int b, int a)
{
    red = r;
    green = g;
    blue = b;
    alpha = a;
}


 SDL_Rect Rect::getRect()
{
    return rect;
}

