#include "Engine.h"

Engine::Engine()
{
    fileReader = new FileReader();

    dataManager = new DataManager("data.xml");

    systemManager = new SystemManager();

    dataManager->textureHandler->loadTextures(systemManager->renderer->getRenderer());
}


Engine::~Engine()
{
    delete dataManager;
    delete systemManager;
}
