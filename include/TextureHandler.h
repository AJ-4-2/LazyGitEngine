#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
#include "XmlReaderOld.h"
/*
 * reads a texture path file into the XmlReader and stores the paths into a vector (fullTextureList)
 * will update the current texture list based on the scene maybe (will come once scene manager is built)
 */
class TextureHandler : public XmlReaderOld
{
    public:
        TextureHandler(std::string, std::string);
        virtual ~TextureHandler();
        //return the texture path in a specific location
        std::string getItem(int);
        //find a specific texture, searched by name.  Returns position
        int findTexture(std::string);
        void loadTextures(SDL_Renderer*);
        void unloadTextures();
        Texture* getTexture(std::string);
    protected:

    private:
        //list of textures currently loaded into memory
        std::vector<std::string > currentTextureList;
        //list of all textures
        std::vector<std::string> fullTextureList;
        //update the current texture list with a provided list
        void updateList(std::vector<std::string>);


        std::vector<Texture*> textures;

};

#endif // TEXTUREHANDLER_H
