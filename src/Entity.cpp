#include "Entity.h"
//get object data and get scene data
//object data is the data from the obj.xml file
//scene data is the data from the scene.xml file
Entity::Entity(std::vector<std::vector<std::string > > objectData, std::vector<std::vector<std::string > > sceneData)
{
    getObjectData(objectData);
    getSceneData(sceneData);

}
Entity::Entity(std::vector<std::vector<std::string > > data, int x, int y)
{

}
Entity::~Entity()
{
    //dtor
}

/*
so we're going to get the object data from the scene manager
so far its just objType, name, and image
*/
void Entity::getObjectData(std::vector<std::vector<std::string > > data)
{
    for (unsigned int c = 0; c < data.size(); c++)
    {
        if (data[c][0] == "objType")
        {
            objectType = data[c][1];
        }
        else if (data[c][0] == "name")
        {
            objectName = data[c][1];
        }
        else if (data[c][0] == "image")
        {
            image = data[c][1];
        }
    }
}
void Entity::getSceneData(std::vector<std::vector<std::string > > data)
{
    for (unsigned int c = 0; c < data.size(); c++)
    {
        if (data[c][0] == "posX")
        {
            posX = stoi(data[c][1]);
        }
        if (data[c][0] == "posY")
        {
            posY = stoi(data[c][1]);
        }
        else if (data[c][0] == "name")
        {
            instanceName = data[c][1];
        }
        else if (data[c][0] == "layer")
        {
            layer = stoi(data[c][1]);
        }
    }
}
