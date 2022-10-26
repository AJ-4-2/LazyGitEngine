#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>

//Load a texture into memory
class Texture
 {
    public:
        Texture(SDL_Renderer*, std::string);
        virtual ~Texture();
        SDL_Texture* getTexture();
        bool getTextureLoaded();
        int getWidth();
        int getHeight();
        void changeColorKey(SDL_Renderer*, int, int, int);
        void render(SDL_Renderer*, int, int);
        void clearTexture();
        std::string getName();

    protected:

    private:
        SDL_Texture* texture = NULL;
        SDL_Surface* surface = NULL;
        bool textureLoaded;
        int width, height;
        void freeTexture();
        void freeSurface();
        std::string textureName;
};

#endif // TEXTURE_H
