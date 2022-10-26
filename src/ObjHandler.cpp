#include "ObjHandler.h"

//constructor
ObjHandler::ObjHandler(std::string path, std::string targetTag) : XmlReaderOld(path, targetTag)
{
    if (!isError())
    {
        for(unsigned int c = 0; c < getSize(); c++)
        {
            objectList.push_back(getTagsAndData(data[c]));
            sortAttributes(objectList[c]);

        }

        sortItems("objName", objectList);
        objectNameIndex = index3dListByTag("objName", objectList);
        objectTypeIndex = index3dListByTag("objType", objectList);
/*
        for (unsigned int c = 0; c < objectNameIndex.size(); c++)
        {
            std::cout << objectList[c][objectNameIndex[c]][1] << std::endl << std::endl;

            if (objectList[c][objectTypeIndex[c]][1] == "PLAYER")
            {
                entityList.push_back(new Player(objectList[c], 0, 0));
            }
            else if (objectList[c][objectTypeIndex[c]][1] == "BACKGROUND")
            {
                entityList.push_back(new Background(objectList[c], 0, 0));
            }
        }*/
    }
}

ObjHandler::~ObjHandler()
{
    //dtor
}

std::vector<std::vector<std::string> > ObjHandler::getObject(std::string name)
{
    return (objectList[indexSearch3d(objectList, objectNameIndex, name)]);
}

