#ifndef DATAMANAGER_H
#define DATAMANAGER_H


#include "TextureHandler.h"
#include "ObjHandler.h"
#include "SceneHandler.h"
#include "XmlReaderOld.h"
#include "Entity.h"
#include <iostream>
#include "XmlReader.h"
#include <string>
#include <vector>

#include "XmlParser.h"


class DataManager
{
    public:
        DataManager(std::string);
        virtual ~DataManager();

        TextureHandler* textureHandler;
        ObjHandler* objHandler;
        SceneHandler* sceneHandler;
        XmlReader* xmlReader;
        XmlParser* xmlParser;
        //FileReader* fileReader;
        //XmlValidator* xmlValidator;


    protected:

    private:
        std::string dataFile;
        std::vector<std::string> fileList;

        std::vector<std::string> errorLog;
        void logError(std::string);
        bool error;

};

#endif // DATAMANAGER_H
