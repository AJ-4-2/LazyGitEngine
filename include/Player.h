#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include <string>

class Player : public Entity
{
    public:
        Player(std::vector<std::vector<std::string > > data, int x, int y);
        virtual ~Player();

    protected:

    private:
};

#endif // PLAYER_H
