#ifndef RENDERER_H
#define RENDERER_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
/*
 * Create the renderer for an inputed window
 * and returns the renderer for use
 */
class Renderer
{
    public:
        Renderer(SDL_Window*);
        virtual ~Renderer();

        SDL_Renderer* getRenderer();

        bool getRendererSuccess();

    protected:

    private:
        bool success;
        SDL_Renderer* renderer = NULL;
};

#endif // RENDERER_H
