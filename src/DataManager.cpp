#include "DataManager.h"

DataManager::DataManager(std::string dataPath)
{
    //initialize the file reader
    xmlReader = new XmlReader();
    xmlParser = new XmlParser();
    error = false;


    dataFile = xmlReader->processFile(dataPath, errorLog);
    if (!errorLog.empty())
    {
        for (unsigned int c = 0; c < errorLog.size(); c++)
        {
        std::cout << errorLog[0] << "\n";
        }
    }
    else
    {
        //std::cout << dataFile << "\n\n";
        xmlParser->readData(dataFile);
    }

    /* 11/12/2021
        now that we have data file in a string and validated, we must prepare it for proper parsing

        STAGE 1: all data in data file is placed in their proper places
            -currently just a list of filenames that contain the actual data
            -so read data.xml into a 1d vector of filenames
        STAGE 2: read and validate first file in list (the files are cascading just like CSS)
            -
    */




    //read master file to get other filenames
    //fileReader->processFile(dataPath);
    //we need data file as a file list, but we dont need a file type

    //we will detect the data types (already have this functionality kinda)
    //so first off validate filetype, reading and validation
    //validate if xml file first, then read to string, then do further validations

/***************************************************************************
    read data file
    handle errors
    parse data string
    log file paths
    loop read each file
    handle errors
    for each file:
        separate out all textures, objects, scenes, and anything else the file might contain into said groups strings
        --make it a vector.  2 parallel vectors 1 has the tag the other has the strings with the data
    parse each data string individually: first textures, then objects, then scenes.  anything new will be fit in
    sort the data
    handle errors and missing dependencies
    write to sorted file

    --game loads with a sorted and stripped-down file for speed.  will be button in launcher to re-read files (for mods)


            XmlParser
        need ways of working with 1d, 2d, 3d, and 4d vector data

        -- 1D data goes through and each outer tag puts its data in a 1D vector slot

        -- 2D data does the same as 1D, but stores the tag in 0 and the data in 1 for each outer vector slot

        -- 3D data takes the concepts of 1 and 2, and puts the groupings of 2 in a list in 3

        -- 4D data


        -- 1D data is a list of data (ex: the texture list)
        -- 2D data is a list of data/attribute pairs (ex: an object)
        -- 3D data is a series of multiple lists of data/attribute pairs (ex: an object list, or a scene)
        -- 4D data is a collection of multiple series of multiple lists of data/attribute pairs (ex: a scene list)

        4D is a child of 3D which is a child of 2D which is a child of 1D
            --reason being is the functions trickle down.
                4D needs the 3D and lower functions as well as its own,
                3D needs the 2D and lower but not the 4D
                2D needs the 1D functions but not the 3D and 4D
                1D only needs itself and has no need for the others

        XmlParser -> Xml1d -> Xml2d -> Xml3d -> Xml4d

        might not need 1d because base will have the single functionality




***************************************************************************/


        /*
        -----might have to set up a data type detection system
            -----will allow for easier future expansion/modding
            -----will take longer to implement
        -----or can just go texture, object, scene, etc
            -----easier to implement
            -----not future-friendly
        */



     std::cout << "begin\n";
    //errorLog eLog;
    std::cout << "\nloading texture handler...\n\n";
    textureHandler = new TextureHandler("img.xml", "image");
    std::cout << "post load list of textures\n";

    if (textureHandler->isError())
    {
        std::cout << "\texture error\n\n";
        //eLog.addErrors(textureHandler->getError());
    }
    else
    {
        std::cout << "\nloading object handler...\n\n";
        objHandler = new ObjHandler("obj.xml", "obj");
        if (objHandler->isError())
        {
            //eLog.addErrors(objHandler->getError());
            std::cout << objHandler->isError() << "\nobject error\n\n";
        }
        else
        {
            std::cout << "\nloading scene handler...\n\n";
            //scene handler
            sceneHandler = new SceneHandler("sceneList.xml", "cityScene");
        }
    }

}

DataManager::~DataManager()
{
    delete textureHandler;
    delete sceneHandler;
    delete objHandler;
    delete xmlReader;
    delete xmlParser;
}
/*
void DataManager::loadScene(std::string sceneName)
{
    sceneHandler->getSceneData(sceneName);
}

void DataManager::loadEntity(std::string entityName)
{
    ojbHandler->getObject(sceneName);
}

*/


void DataManager::logError(std::string errorMessage)
{
    errorLog.push_back(errorMessage);
}
