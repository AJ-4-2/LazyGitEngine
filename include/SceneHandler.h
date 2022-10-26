#ifndef SCENEHANDLER_H
#define SCENEHANDLER_H
#include <string>
#include <vector>
#include "XmlReaderOld.h"
#include "Scene.h"

/*
 *Reads from a master list of scene collections and their file
 *locations and loads a set of scenes from the corresponding file.
 *the scenes are stored in sceneStorage and they are sorted and searchable by name
 *the scenes are stored in a 4d vector, the hierarchy being: scenes < scene items < item attributes < attribute data
 *
*/
class SceneHandler : public XmlReaderOld
{
    public:
        SceneHandler(std::string, std::string);
        virtual ~SceneHandler();
        void loadSceneGroup(std::string);
        std::vector<std::vector<std::vector<std::string> > > getSceneData(std::string);

    protected:

    private:
        std::vector<std::vector<std::vector<std::string> > > sceneGroupList;
        std::vector<std::vector<std::vector<std::string> > > currentSceneObjectList;
        //where the scenes are stored
        std::vector<std::vector<std::vector<std::vector<std::string> > > > sceneStorage;
        std::vector<std::string> currentSceneNameList;

        std::vector<int> sceneGroupIndex;
        std::vector<int> sceneFileIndex;
        //index of item names for index search
        std::vector<std::vector<int> > sceneItemNameIndex;
        //index of item types for index search
        std::vector<std::vector<int> > sceneItemTypeIndex;
        std::vector<int> sceneIndex;

        std::string getSceneName(unsigned int);
        int findScene(std::string );

        void sortScenes();

        void displaySceneData(); // outputs to console for debugging

        //std::vector<Scene*> sceneList;


};

#endif // SCENEHANDLER_H
