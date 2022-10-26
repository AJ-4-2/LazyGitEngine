#include "EventHandler.h"
#include <iostream>

EventHandler::EventHandler()
{
    //need to prime quitRequested to false
    quitRequested = false;
}

EventHandler::~EventHandler()
{

}
//poll events from the queue
void EventHandler::pollEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            std::cout << "quit\n";
            quitRequested = true;
            break;
        }

        //check if the close button was pressed
        if (event.type  == SDL_WINDOWEVENT_CLOSE)
        {
            quitRequested = true;
        }

        //if the user presses a key
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_LSHIFT:
                {
                    lShiftHeld = true;
                    break;
                }
            case SDLK_RSHIFT:
                {
                    rShiftHeld = true;
                    break;
                }
            }
        }

        //check if user releases a key
        if (event.type == SDL_KEYUP)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_LSHIFT:
                {
                    lShiftHeld = false;
                    break;
                }
            case SDLK_RSHIFT:
                {
                    rShiftHeld = false;
                    break;
                }
            }
        }
    }
}
//check to see if an exit has been requested
bool EventHandler::quit()
{
    return quitRequested;
}

bool EventHandler::shift()
{
    return (lShiftHeld || rShiftHeld);
}
