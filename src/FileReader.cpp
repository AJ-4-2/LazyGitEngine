#include "FileReader.h"
#include <sys/stat.h>
#include <vector>
/*
steps:
*/
FileReader::FileReader()
{

}

FileReader::~FileReader()
{
    //dtor
}

std::string FileReader::readFile(std::string path)
{
    std::string fileContent;
    //check to see if files exists
    // set fileContent the files contents if it exists
    // and sets to "ERROR" as well as return an Error code if not
    fileContent = readFileToString(path);
    getFileEmpty(path);
    return fileContent;
}


//this struct returns true if the file is detected using stat
//this is the fastest possible method to detect files
bool FileReader::fileExists (const std::string& path)
{
  struct stat buffer;
  return (stat (path.c_str(), &buffer) == 0);
}

//takes a file and reads it into a string
std::string FileReader::readFileToString(std::string path)
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
    return text;
}

bool FileReader::getFileExists(std::string path, std::vector<std::string> &log)
{
    bool error = false;
    if (!fileExists(path))
    {
        error = true;
        log.push_back(path + " does not exist");
    }
    return error;
}

bool FileReader::getFileEmpty(std::string fileContent)
{
    /*bool isEmpty = false;
        if (fileContent.empty())
    {
        //log.push_back(path + " is empty");
        fileError = true;
        //isEmpty =
    }*/

    return fileContent.empty();
}
