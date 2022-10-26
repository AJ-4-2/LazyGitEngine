#include "XmlReader.h"
#include <sys/stat.h>

bool XmlReader::fileExists (const std::string& name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

bool XmlReader::getFileExists()
{
    return fileIsLoaded;
}

XmlReader::XmlReader(std::string path, std::string targetTag)
{
    std::string text;
    std::ifstream file;
    file.open(path.c_str());
    if (!fileExists(path))
    {
        printf("ERROR file not found\n");
        fileIsLoaded = false;
    }
    else
    {
        fileIsLoaded = true;
        char c;
        if (file.is_open())
        {
            while (file.get(c))
            {
                text += c;
            }
        }

        file.close();

        unsigned int finish = 0, start;
        bool processing = true;
        std::string cleanText;
        //take the string and isolate each instance of the given tag
        //and all data/text contained within the tag, strips out the tags,
        //and pushes a string containing the clean text into a vector
        while(processing)
        {
            //find the start of the target tag
            start = text.find("<" + targetTag, finish) - 1;
            if (start == std::string::npos)
            {
                processing = false;
            }
            start++;
            //find the closest closing tag for the target
            finish = text.find("</" + targetTag, start) + (targetTag.length() + 3);
            if (finish == std::string::npos)
            {
                processing = false;
            }
            if (start >= text.length())
            {
                processing = false;
            }
            if (processing)
            {
                //create substring with tags
                cleanText = text.substr(start, finish - start);
                //remove the opening tag
                cleanText.erase(0, targetTag.length() + 2);
                //remove the closing tag
                cleanText.erase(cleanText.find("</" + targetTag), targetTag.length() + 3);
                if (fileExists(cleanText))
                {
                    //push the sanitized data to the vector
                    data.push_back(cleanText);
                }
                else
                {
                    printf("Texture not found\n");
                }

            }
        }
        selectionSort();
    }
}

XmlReader::~XmlReader()
{
    //delete [] data;
    //data = nullptr;
}

std::vector<std::string> XmlReader::getData()
{
    return data;
}
std::string XmlReader::getItem(int item)
{
    return data[item];
}
//sort the data in alphabetical order
void XmlReader::selectionSort()
{
    int minIndex;
    std::string minValue;

    for (unsigned int start = 0; start < (data.size() -1); start++)
    {
        minIndex = start;
        minValue = data[start];
        for (unsigned int index = start + 1; index < data.size(); index++)
        {
            if (data[index] < minValue)
            {
                minValue = data[index];
                minIndex = index;
            }
        }
        swap(data[minIndex], data[start]);
    }
}

void XmlReader::sawp (std::string & a, std::string & b)
{
    std::string temp = a;
    a = b;
    b = temp;
}
//this is a binary search
int XmlReader::FindTexture(std::string str)
{
    return searchForString(data, str);
}



int XmlReader::getSize()
{
    return data.size();
}
























#include "XmlReader.h"
#include <sys/stat.h>


XmlReader::XmlReader(std::string path, std::string targetTag)
{
    loadFile(path);
    processFile(targetTag);
}

XmlReader::XmlReader(std::string path)
{
    loadFile(path);
}

XmlReader::~XmlReader()
{
    //delete [] data;
    //data = nullptr;
}


bool XmlReader::fileExists (const std::string& name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

bool XmlReader::getFileExists()
{
    return fileIsLoaded;
}

void XmlReader::loadFile(std::string path)
{
    std::ifstream file;
    file.open(path.c_str());
    if (!fileExists(path))
    {
        printf("ERROR file not found\n");
        fileIsLoaded = false;
    }
    else
    {
        fileIsLoaded = true;
        char c;
        if (file.is_open())
        {
            while (file.get(c))
            {
                text += c;
            }
        }

        file.close();
    }
}

void XmlReader::processFile(std::string targetTag)
{
    unsigned int finish = 0, start;
    bool processing = true;
    std::string cleanText;
    //take the string and isolate each instance of the given tag
    //and all data/text contained within the tag, strips out the tags,
    //and pushes a string containing the clean text into a vector
    while(processing)
    {
        std::string target = targetTag;
        //find the start of the target tag
        start = text.find("<" + target, finish) - 1;
        if (start == std::string::npos)
        {
            processing = false;
        }
        start++;
        //find the closest closing tag for the target
        finish = text.find("</" + target, start) + (target.length() + 3);
        if (finish == std::string::npos)
        {
            processing = false;
        }
        if (start >= text.length())
        {
            processing = false;
        }
        if (processing)
        {
            //create substring with tags
            cleanText = text.substr(start, finish - start);
            //remove the opening tag
            cleanText.erase(0, target.length() + 2);
            //remove the closing tag
            cleanText.erase(cleanText.find("</" + target), target.length() + 3);
            if (fileExists(cleanText))
            {
                //push the sanitized data to the vector
                data.push_back(cleanText);
            }
            else
            {
                printf("Texture not found\n");
            }

        }
    }
    selectionSort();
}





std::vector<std::string> XmlReader::getData()
{
    return data;
}
std::string XmlReader::getItem(int item)
{
    return data[item];
}
//sort the data in alphabetical order
void XmlReader::selectionSort()
{
    int minIndex;
    std::string minValue;

    for (unsigned int start = 0; start < (data.size() -1); start++)
    {
        minIndex = start;
        minValue = data[start];
        for (unsigned int index = start + 1; index < data.size(); index++)
        {
            if (data[index] < minValue)
            {
                minValue = data[index];
                minIndex = index;
            }
        }
        swap(data[minIndex], data[start]);
    }
}

void XmlReader::sawp (std::string & a, std::string & b)
{
    std::string temp = a;
    a = b;
    b = temp;
}
//this is a binary search
int XmlReader::FindTexture(std::string str)
{
    int first = 0,              //first vector element
        last = data.size(),     //last vector element
        middle,                 //midpoint of the search
        position = -1;          //position of the search value
    bool found = false;

    while (!found)
    {
        middle = (first + last) / 2;   //calculate midpoint
        if (data[middle] == str)
        {
            found = true;
            position = middle;
        }
        else if (data[middle] > str)
        {
            last = middle - 1;
        }
        else
        {
            first = middle + 1;
        }
    }
    return position;
}



int XmlReader::getSize()
{
    return data.size();
}


