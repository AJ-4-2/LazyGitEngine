#include "XmlReader.h"

XmlReader::XmlReader() : FileReader()
{
    //ctor
}

XmlReader::~XmlReader()
{
    //dtor
}
//this might be put into parent class or rename "validateXmlFileType"
bool XmlReader::validateFileType(std::string path, std::vector<std::string> & log)
{
    //detect if the file is an xml file
    //the find ".xmll" is to cover an edge case
    if (path.find(".xml") == std::string::npos || path.find(".xmll") != std::string::npos || path.back() != 'l')
    {
        log.push_back(path + " is not an xml file");
        return true;
    }
    return false;
}



bool XmlReader::validateContents(std::string fileContent, std::string path, std::vector<std::string> & log)
{
    bool fileError = false;
    //check to see if the file is empty
    if (fileContent.empty())
    {
        log.push_back(path + " is empty");
        fileError = true;
    }
    else
    {
        //check to see if the file contains the xml header
        //searches for the opening and closing of the header, and the xml version line
        if (fileContent.find("<?") == std::string::npos && fileContent.find("xml version= \"1.0\"") == std::string::npos && fileContent.find("?>") == std::string::npos )
        {
            log.push_back(path + " is missing XML header");
            fileError = true;
        }

    }
    return fileError;
}

std::string XmlReader::processFile(std::string path, std::vector<std::string> & errorLog)
{
    std::string dataFile;
     //check if file exists.  If not file error, then proceed
    if (!getFileExists(path, errorLog))
    {
        //validate file type, if not error then proceed
        if (!validateFileType(path, errorLog))
        {
            //read the file into a string
            dataFile = readFile(path);
            //std::cout << dataFile << "\n\n";
            //perform the post-load validations, if not error then proceed
            if (!validateContents(dataFile, path, errorLog))
            {

            }
        }
    }
    return dataFile;
}
