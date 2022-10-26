#ifndef WINDOW_H
#define WINDOW_H
#include <SDL.h>
#include <stdio.h>

/*
 * Creates and manages windows
 */
class Window
{
    public:
        Window(int, int);
        virtual ~Window();

        SDL_Window* getWindow();
        bool getWindowSuccess();
        int getXRes();
        int getYRes();

    protected:

    private:
        SDL_Window* window = NULL;
        bool success;
        int width, height;
};

#endif // WINDOW_H
