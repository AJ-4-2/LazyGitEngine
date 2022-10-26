#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
//#include <algorithm>

#include <iostream>

#include <System.h>
#include <EventHandler.h>
#include <Window.h>
#include <Renderer.h>
#include <Texture.h>
#include <XmlReader.h>
#include <Rect.h>
#include <Viewport.h>
#include <TextureHandler.h>

int main(int argc, char* args[])
{

    //

     //load the texture paths
    XmlReader* texturePaths = new XmlReader("img.xml", "image");
    //texturePaths->processFile("image");
    //XmlReader* objects = new XmlReader("obj.xml", "image");


    //test if file exists
    if (!texturePaths->getFileExists())
    {
        printf("Could not find textures");
    }
    else
    {
         //TextureHandler* textureHandler = new TextureHandler(texturePaths->getData());
        //Start up SDL and create window
        System* system = new System();
        //check system
        if (!system->getInitSuccess())
        {
            printf("Could not initialize system");
        }
        else
        {
            //create window
            Window* window = new Window(800, 600);
            //check window
            if (!window->getWindowSuccess())
            {
                printf("Could not create window\n");
            }
            else
            {

                Viewport* viewport = new Viewport(VIEWPORT_FULL, window->getXRes(), window->getYRes());
                //create renderer
                Renderer* renderer = new Renderer(window->getWindow());
                //check renderer
                if (!renderer->getRendererSuccess())
                {
                    printf("Could not create renderer\n");
                }
                else
                {
                    //create the texture vector
                    std::vector<Texture*> textures;

                    //textureHandler->updateList(textureHandler->currentTextureList);
                    //load the images into texture
                    for (int c = 0; c < texturePaths->getSize(); c++)
                    {
                        textures.push_back(new Texture(renderer->getRenderer(), texturePaths->getItem(c)));

                        if (!textures[c]->getTextureLoaded())
                        {
                            std::cout << "texture not found\n";
                        }
                        else
                        {

                        }
                    }

                    //create the event handler
                    EventHandler* hndlr = new EventHandler();

                    //Main loop flag
                    bool running = true;

                    //While application is running
                    while(running)
                    {
                        running = true;
                        SDL_SetRenderDrawColor( renderer->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear(renderer->getRenderer());
                        //handle events
                        hndlr->pollEvents();
                        //if the window is closed, quit the program
                        if (hndlr->quit())
                        {
                            running = false;
                        }
                        //Clear screen
                        SDL_RenderClear(renderer->getRenderer());

                        //set the renderer to the viewport
                        viewport->setViewport(renderer->getRenderer());

                        //Render texture to screen
                        SDL_RenderCopy(renderer->getRenderer(), textures[4]->getTexture(), NULL, NULL);

                        //Update screen
                        SDL_RenderPresent(renderer->getRenderer());
                    }
                    for (unsigned int c = 0; c < textures.size(); c++)
                    {
                        delete textures[c];
                    }
                    delete hndlr;
                }
                delete renderer;
                delete viewport;
            }
            delete window;
        }
        delete system;
    }
    delete texturePaths;
//        delete texturePaths2;
	return 0;
}
