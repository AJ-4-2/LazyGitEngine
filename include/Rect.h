#ifndef RECT_H
#define RECT_H
#include <SDL.h>
//takes in x and y positions, width and height, and color/alpha
//and can edit these values at any time
//also takes a renderer and renders it to the renderer
class Rect
{
    public:
        Rect();
        Rect(int, int, int, int);
        Rect(int []);
        virtual ~Rect();

        void drawToRenderer(SDL_Renderer*);
        //change the size and position
        void transformRect(int, int, int, int);
        void changeColor(int, int, int, int);
         SDL_Rect getRect();


    protected://these are in protected to be accessible by the child classes
        SDL_Rect rect;
        int red, green, blue, alpha; //0-255

    private:

};

#endif // RECT_H
