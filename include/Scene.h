#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <string>


class Scene
{
    public:
        //scene data, data type index, data name index
        Scene(std::vector<std::vector<std::vector<std::string> > >, std::vector<int>, std::string);
        virtual ~Scene();



    protected:
        std::string sceneName;
        std::vector<std::vector<std::vector<std::string> > > sceneObjectData;
        std::vector<std::vector<std::string> > sceneInfo;

    private:
};

#endif // SCENE_H
