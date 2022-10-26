#ifndef RWOREADER_H
#define RWOREADER_H
#include <SDL.h>
#include <SDL_image.h>

class RwoReader
{
    public:
        RwoReader();
        virtual ~RwoReader();
        char* file_read(const char*);

    protected:

    private:
};

#endif // RWOREADER_H
