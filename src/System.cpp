#include "System.h"
System::System()
{
    //initialize sdl video and check for errors
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
         printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
         init= false;
    }

    else
    {
        //Set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}


        //once properly initialized, initialize image
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            init = false;
        }
        else
        {
            init = true;
        }
    }
}

System::~System()
{
    //exit SDL
    SDL_Quit();
    IMG_Quit();
}

bool System::getInitSuccess()
{
    return init;
}
