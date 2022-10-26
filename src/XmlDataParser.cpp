#include "XmlDataParser.h"

XmlDataParser::XmlDataParser()
{
    //ctor
}

XmlDataParser::~XmlDataParser()
{
    //dtor
}
/*

void XmlDataParser::readTagFromFile(std::string file, std::string targetTag)
{
    readPos = 0;
    data.clear();
    if (getFileError(path, targetTag))
    {
        fileError = true;
    }
    else
    {
        //set the read position to after the header
        readPos = fileText.find("?>");
        while (findNextOfTag(targetTag, fileText));
        removeTagsFromData(targetTag);
    }
}
*/
