#include "XmlParser.h"

XmlParser::XmlParser()
{
    //ctor

}

XmlParser::~XmlParser()
{
    //dtor
}
/*
    data inside target tag
    data inside first outermost tag

    data is already in a string, and validated by this point, adjust accordingly

    ***** FUNCTIONS / STEPS / ACTIONS *****
        -go through file, read each top level tag
        -organize in parallel vectors:
            -list of tags found
            -vector of data for each tag in list
*/

void XmlParser::readData(std::string data)
{
    //read each outer tag into a vector of strings
    //std::vector<std::string> dataVector;
    if (validateHeader(data))
    {
        xmlData = new XmlData(data, readPos);
    }
}
/*

    (later) a validation system that goes through the file and detects any incomplete tags
*/

//

bool XmlParser::validateHeader(std::string fileContent)
{
    //check to see if the file contains the xml header
    //searches for the opening and closing of the header, and the xml version line
    if (fileContent.find("<?") == std::string::npos && fileContent.find("xml version= \"1.0\"") == std::string::npos && fileContent.find("?>") == std::string::npos )
    {
        //log.push_back(path + " is missing XML header");
        return false;
    }
    readPos = fileContent.find("?>") + 2;
    return true;
}










