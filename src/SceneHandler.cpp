#include "SceneHandler.h"

//Reads a list of scene files.  Scene file locations and names are stored in the sceneGroupList.xml file by default
//but this can be changed in the master file
//from the sceneGroupList file it reads a default scene group (i.e. main menu and logos)
SceneHandler::SceneHandler(std::string path, std::string targetTag) : XmlReaderOld(path, targetTag)
{
    if (!isError())
    {
        for(unsigned int c = 0; c < getSize(); c++)
        {
            //read scene data from data[]
            sceneGroupList.push_back(getTagsAndData(data[c]));
            sortAttributes(sceneGroupList[c]);
        }
        sortItems("sceneGroupName", sceneGroupList);
        //create an index of scene collections
        sceneGroupIndex = index3dListByTag("sceneGroupName", sceneGroupList);
        sceneFileIndex = index3dListByTag("file", sceneGroupList);

        loadSceneGroup("scenes");
    }
}

SceneHandler::~SceneHandler()
{
    //dtor
}
//loads data for the selected scene file into storage
void SceneHandler::loadSceneGroup(std::string sceneCollection)
{
    int item = indexSearch3d(sceneGroupList, sceneGroupIndex, sceneCollection);
    std::vector<std::vector<std::vector<std::string> > > sceneDataList;

    fileError = false;
    readTagFromFile(sceneGroupList[item][sceneFileIndex[item]][1], "scene");

    if (!isError())
    {
    //iterates each scene
        for (unsigned int c = 0; c < getSize(); c++)
        {
            sceneStorage.push_back(getSceneInfo(data[c]));
            for (unsigned int c1 = 0; c1 < sceneStorage[c].size(); c1++)
            {
                sortAttributes(sceneStorage[c][c1]);
            }
            sortItems("name", sceneStorage[c]);
            sceneItemNameIndex.push_back(index3dListByTag("name", sceneStorage[c]));
            sceneItemTypeIndex.push_back(index3dListByTag("dataType", sceneStorage[c]));

            //std::cout << "\nSCENE:: " << c << "......\n";
            displaySceneData();
        }
        sortScenes();


    }
    std::cout << "sceneName:::::: " << getSceneName(findScene("scene0")) << "\n";
}

//sorts the scenes by name
void SceneHandler::sortScenes()
{
    int minIndex;
    std::string minValue;

    for (unsigned int start = 0; start < (sceneStorage.size() -1); start++)
    {
        minIndex = start;
        minValue = getSceneName(0);

        for (unsigned int index = start + 1; index < sceneStorage.size(); index++)
        {

            if (getSceneName(index) < minValue)
            {
                minValue = getSceneName(index);
                minIndex = index;
            }
        }
        swap(sceneStorage[minIndex], sceneStorage[start]);
        swap(sceneItemNameIndex[minIndex], sceneItemNameIndex[start]);
        swap(sceneItemTypeIndex[minIndex], sceneItemTypeIndex[start]);
    }
}
//this gets the scene name for inputed scene by position
std::string SceneHandler::getSceneName(unsigned int scene)
{
    std::string output;
    //Check for valid scene number
    if (scene < 0 || scene >= sceneStorage.size())
    {
        output = "INVALID SCENE";
    }
    else
    {
        output = sceneStorage[scene][indexSearch3d(sceneStorage[scene], sceneItemTypeIndex[scene], "sceneInfo")][findAttribute(sceneStorage[scene][indexSearch3d(sceneStorage[scene], sceneItemTypeIndex[scene], "sceneInfo")], "name")][1];
    }
    return output;
}

//binary search to find a scene from sceneStorage by name
int SceneHandler::findScene(std::string target)
{
    int first, last, middle, position;
    bool found, noResult;

    first = 0;
    position = -1;
    found = false;
    noResult = false;
    last = sceneStorage.size();
    //bounds checking so if lower than the lowest or visa versa for highest, don't bother searching
    /*if (target.compare(getSceneName(0) < 0 || target.compare(getSceneName(sceneStorage.size() -1)) > 0)
        {
            noResult = true;
        }*/
    while (!found && !noResult)
    {
        if (middle == ((first + last) / 2))
        {
            noResult = true;
        }
        else
        {
            middle = (first + last) / 2;
        }

        if (!found && !noResult && getSceneName(middle).compare(target) == 0)
        {
            found = true;
            position = middle;
        }
        else if (!found && !noResult && getSceneName(middle).compare(target) > 0)
        {
            last = middle - 1;
        }
        else if (!found && !noResult && getSceneName(middle).compare(target) < 0)
        {
            first = middle + 1;
        }
    }
    return position;
}
//for debug purposes
//outputs all scene data with hierarchical notation
void SceneHandler::displaySceneData()
{
    std::cout << "\n.....................................\n";
    for (unsigned int c = 0; c < sceneStorage.size(); c++)
    {
        for (unsigned int c1 = 0; c1 < sceneStorage[c].size(); c1++)
        {
            for (unsigned int c2 = 0; c2 < sceneStorage[c][c1].size(); c2++)
            {
                std::cout << sceneStorage[c][c1][c2][0] << ".................." <<  sceneStorage[c][c1][c2][1] << "..........." << c << " " << c1 << " " << c2 << " " << "\n";
            }
            std::cout << ".....................................\n";
        }
        std::cout << ".....................................\n";
    }
    std::cout << ".....................................\n";
}


std::vector<std::vector<std::vector<std::string> > > SceneHandler::getSceneData(std::string name)
{
    return sceneStorage[findScene(name)];
}


