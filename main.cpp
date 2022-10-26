#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include <Engine.h>

struct errorLog
{
    std::vector<std::string> errors;
    void addErrors(std::vector<std::string> err)
    {
        errors.insert(errors.end(), err.begin(), err.end());
    }
    void printErrors()
    {
        for (unsigned int c = 0; c < errors.size(); c++)
        {
            printf("%s\n", errors[c].c_str());
        }
    }
};


int main(int argc, char* args[])
{
    Engine* engine = new Engine();

    //Main loop flag
    bool running = true;
    //std::cout << "test000\n\n\n";
    //While application is running
    while(running)
    {
        running = true;
        SDL_SetRenderDrawColor(engine->systemManager->renderer->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(engine->systemManager->renderer->getRenderer());
        //handle events

        engine->systemManager->eventHandler->pollEvents();

        //if the window is closed, quit the program
        if (engine->systemManager->eventHandler->quit())
        {
            running = false;
        }
        //std::cout << "post quit\n";
        //Clear screen
        SDL_RenderClear(engine->systemManager->renderer->getRenderer());

        //set the renderer to the viewport
        engine->systemManager->viewport->setViewport(engine->systemManager->renderer->getRenderer());

        //Render texture to screen
        //engine->dataManager->textureHandler->getTexture("img/backgroundNight.png")->render(engine->systemManager->renderer->getRenderer(), 0, 0);
        //engine->dataManager->textureHandler->getTexture("img/bldgFrntA.png")->render(engine->systemManager->renderer->getRenderer(), 256, 230);
        //SDL_RenderCopy(renderer->getRenderer(), textures[3]->getTexture(), NULL, NULL);

        //Update screen
        SDL_RenderPresent(engine->systemManager->renderer->getRenderer());
    }
    engine->dataManager->textureHandler->unloadTextures();

    delete engine;

	return 0;
}
