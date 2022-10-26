#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>

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
    //std::vector<Texture*> textures;
    // textures.push_back(new Texture(renderer->getRenderer(), textureHandler->getItem(c)));

    std::vector<XmlReader*> xmlFiles;
    xmlFiles.push_back(new XmlReader("img.xml", "image"));
    //xmlFiles.push_back(new XmlReader("obj.xml", "image"));
     //load the texture paths
    //XmlReader* texturePaths = new XmlReader("img.xml", "image");
    //texturePaths->processFile("image");

    //test if file exists
    if (!xmlFiles[0]->getFileExists())
    {
        printf("Could not find textures");
    }
    else
    {
         TextureHandler* textureHandler = new TextureHandler(xmlFiles[0]->getData());
         textureHandler->updateList((xmlFiles[0]->getData()));

         //delete texturePaths;



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
                    for (int c = 0; c < textureHandler->getSize(); c++)
                    {
                        textures.push_back(new Texture(renderer->getRenderer(), textureHandler->getItem(c)));

                        if (!textures[c]->getTextureLoaded())
                        {
                            std::cout << "texture not found\n";
                        }
                        else
                        {

                        }
                    }
                    textures[2]->changeColorKey(renderer->getRenderer(), 0, 0xFF, 0xFF);
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
                        textures[0]->render(renderer->getRenderer(), 0, 0);
                        textures[2]->render(renderer->getRenderer(), 256, 230);
                        //SDL_RenderCopy(renderer->getRenderer(), textures[3]->getTexture(), NULL, NULL);

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
    //delete texturePaths;
//        delete texturePaths2;
    delete xmlFiles[0];
	return 0;
}
