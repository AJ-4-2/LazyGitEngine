#include "Window.h"

Window::Window(int xRes, int yRes)
{
    width = xRes;
    height = yRes;
    //create the window
    window = SDL_CreateWindow( "Engine Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, xRes, yRes, SDL_WINDOW_SHOWN);
    //SDL_SetWindowFullscreen(window, 0);
    //SDL_SetWindowResizable(window, SDL_TRUE);
    //check window
    if( window == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        success = true;
    }
}

Window::~Window()
{
    SDL_DestroyWindow(window);
    window = NULL;
}

SDL_Window* Window::getWindow()
{
    return window;
}

bool Window::getWindowSuccess()
{
    return success;
}

int Window::getXRes()
{

    return width;
}

int Window::getYRes()
{
    return height;
}
