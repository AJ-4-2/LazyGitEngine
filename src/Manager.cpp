#include "Manager.h"


Manager::Manager()
{
    std::cout << "begin\n";
    //errorLog eLog;
    textureHandler = new TextureHandler("img.xml", "image");
    std::cout << "post load list of textures\n";

    if (textureHandler->isError())
    {
        //eLog.addErrors(textureHandler->getError());
    }
    else
    {
        objHandler = new ObjHandler("obj.xml", "obj");
        if (objHandler->isError())
        {
            //eLog.addErrors(objHandler->getError());
        }
        else
        {
            //scene handler
            sceneHandler = new SceneHandler("scene.xml", "obj");
        }
    }
}

Manager::~Manager()
{
    delete textureHandler;
    delete sceneHandler;
    delete objHandler;
}
