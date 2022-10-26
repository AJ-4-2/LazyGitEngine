#include "Scene.h"

Scene::Scene(std::vector<std::vector<std::vector<std::string> > > data, std::vector<int> typeIndex, std::string name)
{
    for (unsigned int c = 0; c < data.size(); c++)
    {
        sceneName = name;
        if (data[c][typeIndex[c]][1] == "obj")
        {
            sceneObjectData.push_back(data[c]);
        }
        else if (data[c][typeIndex[c]][1] == "sceneInfo")
        {
            sceneInfo = data[c];
        }
    }

}

Scene::~Scene()
{
    //dtor
}
