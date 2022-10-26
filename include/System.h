#ifndef SYSTEM_H
#define SYSTEM_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

/*
 * Initializes and quits the system process for SDL and SDL_Image
 */
class System
{
    public:
        System();
        virtual ~System();
        bool getInitSuccess();

    protected:

    private:
        bool init;
};

#endif // SYSTEM_H
