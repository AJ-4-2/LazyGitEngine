#include "SystemManager.h"

SystemManager::SystemManager()
{

    //Start up SDL and create window
    system = new System();

    //check system
    if (!system->getInitSuccess())
    {
        printf("Could not initialize system");
    }
    else
    {
        //create window
        window = new Window(800, 600);
        std::cout << "post build window\n";
        //check window
        if (!window->getWindowSuccess())
        {
            printf("Could not create window\n");
        }
        else
        {

            viewport = new Viewport(VIEWPORT_FULL, window->getXRes(), window->getYRes());
            std::cout << "post set viewport\n";
            //create renderer
            renderer = new Renderer(window->getWindow());
            std::cout << "post set renderer\n";
            //check renderer
            if (!renderer->getRendererSuccess())
            {
                printf("Could not create renderer\n");
            }
            else
            {
                //create the event handler
                eventHandler = new EventHandler();
                std::cout << "post init event handler\n";
            }
        }
    }
}

SystemManager::~SystemManager()
{
    delete system;
    delete window;
    delete viewport;
    delete renderer;
    delete eventHandler;
}
