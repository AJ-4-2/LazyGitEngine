#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include <SDL.h>

/*
 * Handles system events
 */
class EventHandler
{
    public:
        EventHandler();
        virtual ~EventHandler();

        //function for reading events from the queue
        void pollEvents();
        //return if a program exit is requested
        bool quit();
        bool shift();

    protected:

    private:
        //set up variable for event handling
        SDL_Event event;
        //for setting the exit state
        bool quitRequested;
        //for setting the shift state (both sides)
        bool lShiftHeld, rShiftHeld;

};

#endif // EVENTHANDLER_H
