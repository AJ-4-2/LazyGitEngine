#ifndef ENGINE_H
#define ENGINE_H

#include "DataManager.h"
#include "SystemManager.h"

#include "FileReader.h"


class Engine
{
    public:
        Engine();
        virtual ~Engine();

        DataManager* dataManager;
        SystemManager* systemManager;
        FileReader* fileReader;



    protected:

    private:
};

#endif // ENGINE_H
