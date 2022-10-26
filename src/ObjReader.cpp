#include "ObjReader.h"
#include <sys/stat.h>

bool ObjReader::fileExists (const std::string& name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

bool ObjReader::getFileExists()
{
    return fileIsLoaded;
}

ObjReader::ObjReader(std::string path, std::string targetTag)
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
        if (file.is_open() && file.good())
        {
            while (file.get(c))
            {
                text += c;
            }
        }
    }
    file.close();



        /*
        //File reading/writing (We're only going to read)
        std::ifstream edict2("dict/edict2u");
        if (edict2.is_open() && edict2.good()) {
            std::string buffer;
            while (std::getline(edict2, buffer)) {
                //Do something about the buffer.
                doAction(buffer);

                //Then clear the buffer once you're done with it.
                buffer.clear();
            };
        }

*/





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


ObjReader::~ObjReader()
{
    //delete [] data;
    //data = nullptr;
}

std::vector<std::string> ObjReader::getData()
{
    return data;
}
std::string ObjReader::getItem(int item)
{
    return data[item];
}
//sort the data in alphabetical order
void ObjReader::selectionSort()
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

void ObjReader::sawp (std::string & a, std::string & b)
{
    std::string temp = a;
    a = b;
    b = temp;
}
//this is a binary search
int ObjReader::FindTexture(std::string str)
{
    return searchForString(data, str);
}



int ObjReader::getSize()
{
    return data.size();
}

