#include "XmlFileReader.h"
#include <sys/stat.h>

XmlFileReader::XmlFileReader()
{
    //ctor
}

XmlFileReader::~XmlFileReader()
{
    //dtor
}


std::string XmlFileReader::readFile(std::string path)
{
    fileError = false;
    std::string fileContent;
    //check to see if files exists
    // set fileContent the files contents if it exists
    // and sets to "ERROR" as well as return an Error code if not
    if (!getFileError(path))
    {
        fileContent = readFileToString(path);
    }
    else
    {
        errorLog.push_back("ERROR file: " + path + " not found");
        fileContent = errorLog[errorLog.size() - 1];
    }

    return fileContent;
}


//this struct returns true if the file is detected using stat
//this is the fastest possible method to detect files
bool XmlFileReader::fileExists (const std::string& path)
{
  struct stat buffer;
  return (stat (path.c_str(), &buffer) == 0);
}

//takes a file and reads it into a string
std::string XmlFileReader::readFileToString(std::string path)
{
    std::ifstream file;
    std::string text;
    file.open(path.c_str());

    //copy the contents of the file to the string character by character
    //(probably super slow gonna find a better solution)
    //fileIsLoaded = true;
    char c;
    if (file.is_open() && file.good())
    {
        while (file.get(c))
        {
            text += c;
        }

        file.close();
    }

    //returns the file contents if the file exists
    //otherwise returns "ERROR"
    return text;
}


//move this
//or split apart
//i could read it to a string and return it, then have something else verify the file
//
//
//
//
bool XmlFileReader::getFileError(std::string path)
{
    //detect if the file is an xml file
    //the find ".xmll" is to cover an edge case
    if (path.find(".xml") == std::string::npos || path.find(".xmll") != std::string::npos || path.back() != 'l')
    {
        setError(path + " is not an xml file\n");
        fileError = true;
    }
    else
    {
        //check to see if readFileToString() failed to find the file
        if (!fileExists(path))
        {
            setError("Cannot find " + path + "\n");
            fileError = true;
        }
        else
        {
            //read the file to a string
            fileContent = readFileToString(path);
            //check to see if the file is empty
            if (fileContent.empty())
            {
                setError(path + " is empty\n");
                fileError = true;
            }
            else
            {
                //check to see if the file contains the xml header
                //searches for the opening and closing of the header, and the xml version line
                if (fileContent.find("<?") == std::string::npos && fileContent.find("xml version= \"1.0\"") == std::string::npos && fileContent.find("?>") == std::string::npos )
                {
                    setError("XML header is missing\n");
                    fileError = true;
                }
                /*
                else
                {
                    //check to see if the file contains the target tag
                    if (fileText.find("<" + targetTag + ">") == std::string::npos || fileText.find("</" + targetTag + ">") == std::string::npos)
                    {
                        setError("Cannot find target tag: " + targetTag + "\n");
                        fileError = true;
                    }
                }
                */
            }
        }
    }
    return fileError;
}

//ERROR SYSTEM

std::vector<std::string> XmlFileReader::getError()
{
    return errorLog;
}

void XmlFileReader::setError(std::string error)
{
    errorLog.push_back(error);
}
/*
bool XmlFileReader::isError()
{
    return fileError;
}
*/
