#ifndef ENTITY_H
#define ENTITY_H
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "Rect.h"
//#include "Texture.h"

/*
the goal of the entity class is simply to represent
the types of data which is shared by all entities
so far that includes :
    texture (can be null), rect (can also be null), name, and enityType
*/
class Entity
{
    public:
        Entity(std::vector<std::vector<std::string > >, int, int);
        Entity(std::vector<std::vector<std::string > >, std::vector<std::vector<std::string > >);
        virtual ~Entity();

    protected:
        std::string image;
        Rect* rect;
        int posX, posY;//x and y position
        std::string objectName, instanceName;
        std::string objectType;
        void getObjectData(std::vector<std::vector<std::string > >);
        void getSceneData(std::vector<std::vector<std::string > >);
        int layer;

    private:


};

#endif // ENTITY_H
