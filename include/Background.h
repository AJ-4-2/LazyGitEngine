#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>

#include "Entity.h"


class Background : public Entity
{
    public:
        Background(std::vector<std::vector<std::string > > data, int x, int y);
        virtual ~Background();

    protected:

    private:
};

#endif // BACKGROUND_H
