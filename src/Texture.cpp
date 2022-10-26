#include "Texture.h"

Texture::Texture(SDL_Renderer* renderer, std::string path)
{
    freeTexture();
    freeSurface();
    surface = IMG_Load(path.c_str());
    if( surface == NULL )
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		textureLoaded = false;
	}
	else
	{
		//Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, surface);
		if( texture == NULL )
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			textureLoaded = false;
		}
		else
        {
            textureLoaded = true;
            width = surface->w;
            height = surface->h;
            textureName = path;
        }
	}
}

Texture::~Texture()
{
    freeTexture();
    freeSurface();
}

void Texture::clearTexture()
{
    freeTexture();
    freeSurface();
}

SDL_Texture* Texture::getTexture()
{
    return texture;
}

bool Texture::getTextureLoaded()
{
    return textureLoaded;
}

int Texture::getWidth()
{
    return width;
}

int Texture::getHeight()
{
    return height;
}

void Texture::freeTexture()
{
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void Texture::freeSurface()
{
    SDL_FreeSurface(surface);
    surface = NULL;
}

void Texture::changeColorKey(SDL_Renderer* renderer, int r, int g, int b)
{
    freeTexture();
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, r, g, b));
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if( texture == NULL )
		{
			printf("Unable to change texture color key. SDL Error: %s\n", SDL_GetError());
			textureLoaded = false;
		}
		else
        {
            textureLoaded = true;
            width = surface->w;
            height = surface->h;
        }
}

void Texture::render(SDL_Renderer* renderer, int posX, int posY)
{
    SDL_Rect renderQuad =
    {
         posX,
         posY,
         width,
         height
    };
	SDL_RenderCopy( renderer, texture, NULL, &renderQuad);
}

std::string Texture::getName()
{
    return textureName;
}
