#include "Renderer.h"

Renderer::Renderer(SDL_Window* window)
{
    //create the renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    //check the renderer
    if( renderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        success = true;
        //Initialize renderer color
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer( renderer );
    renderer = NULL;
}

SDL_Renderer* Renderer::getRenderer()
{
    return renderer;
}

bool Renderer::getRendererSuccess()
{
    return success;
}
