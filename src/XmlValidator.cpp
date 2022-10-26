#include "XmlValidator.h"

XmlValidator::XmlValidator()
{
    //ctor
}

XmlValidator::~XmlValidator()
{
    //dtor
}

bool XmlValidator::validateFileType(std::string path, std::vector<std::string> & log)
{
    bool fileError = false;
    //detect if the file is an xml file
    //the find ".xmll" is to cover an edge case
    if (path.find(".xml") == std::string::npos || path.find(".xmll") != std::string::npos || path.back() != 'l')
    {
        log.push_back(path + " is not an xml file");
        fileError = true;
    }
    return fileError;
}



bool XmlValidator::validateContents(std::string fileContent, std::string path, std::vector<std::string> & log)
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

