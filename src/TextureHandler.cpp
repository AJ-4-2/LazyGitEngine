#include "TextureHandler.h"

TextureHandler::TextureHandler(std::string path, std::string targetTag) : XmlReaderOld(path, targetTag)
{
    if (!isError())
    {
        sortData();
        //load the texture paths
        updateList(getData());

    }
}

TextureHandler::~TextureHandler()
{
    //dtor
}

//PUBLIC MEMBERS

//return the texture path in a specific location
std::string TextureHandler::getItem(int item)
{
    return currentTextureList[item];
}

//find a specific texture, searched by name.  Returns position
int TextureHandler::findTexture(std::string str)
{
    return search1dVector(currentTextureList, str);
}

Texture* TextureHandler::getTexture(std::string path)
{
    return textures[findTexture(path)];
}

void TextureHandler::unloadTextures()
{
    for (unsigned int c = 0; c < currentTextureList.size(); c++)
    {
        printf("%s\n", currentTextureList[c].c_str());
        delete textures[c];
    }
}

//PRIVATE MEMBERS

//update the current texture list with a provided list
void TextureHandler::updateList(std::vector<std::string> textureList)
{
    currentTextureList.clear();
    for (unsigned int c = 0; c < textureList.size(); c++)
    {
        currentTextureList.push_back(textureList[c]);
    }
}
//loads a vector of each texture int the same order as the list to be searchable
void TextureHandler::loadTextures(SDL_Renderer* renderer)
{
    for (unsigned int c = 0; c < currentTextureList.size(); c++)
    {
        printf("%s\n", currentTextureList[c].c_str());
        textures.push_back(new Texture(renderer, currentTextureList[c]));
    }
}




