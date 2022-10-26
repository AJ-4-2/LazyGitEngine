#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "System.h"
#include "EventHandler.h"
#include "Window.h"
#include "Renderer.h"
#include "Texture.h"
#include "Viewport.h"

class SystemManager
{
    public:
        SystemManager();
        virtual ~SystemManager();

        System* system;
        Window* window;
        Viewport* viewport;
        Renderer* renderer;
        EventHandler* eventHandler;

    protected:

    private:
};

#endif // SYSTEMMANAGER_H
