#ifndef MANAGER_H
#define MANAGER_H
#include "TextureHandler.h"
#include "ObjHandler.h"
#include "SceneHandler.h"

class Manager
{
    public:
        Manager();
        virtual ~Manager();

        TextureHandler* textureHandler;
        ObjHandler* objHandler;
        SceneHandler* sceneHandler;




    protected:

    private:
};

#endif // MANAGER_H
