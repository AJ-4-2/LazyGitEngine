#include "XmlReaderOld.h"
#include <sys/stat.h>

//PUBLIC MEMBERS

//base constructor just sets the read position to 0
XmlReader::XmlReader()
{
    //int readPos = 0;
}
//read file to data
XmlReader::XmlReader(std::string path, std::string targetTag)
{
    fileError = false;
    readTagFromFile(path, targetTag);
}

XmlReader::~XmlReader()
{

}

void XmlReader::readTagFromFile(std::string path, std::string targetTag)
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


//returns the whole data vector
std::vector<std::string> XmlReader::getData()
{
    return data;
}

//returns an item in the data vector
std::string XmlReader::getItem(int item)
{
    return data[item];
}

unsigned int XmlReader::getSize()
{
    return data.size();
}


//PROTECTED MEMBERS


bool XmlReader::getFileError(std::string path, std::string targetTag)
{
    bool fileError = false;
    //detect if the file is an xml file
    //the find ".xmll" is to cover an edge case
    if (path.find(".xml") == std::string::npos || path.find(".xmll") != std::string::npos || path.back() != 'l')
    {
        setError(path + " is not an xml file\n");
        fileError = true;
    }
    else
    {
        //read the file to a string
        fileText = readFileToString(path);
        //check to see if readFileToString() failed to find the file
        if (fileText.compare("ERROR") == 0)
        {
            setError("Cannot find " + path + "\n");
            fileError = true;
        }
        else
        {
            //check to see if the file is empty
            if (fileText.empty())
            {
                setError(path + " is empty\n");
                fileError = true;
            }
            else
            {
                //check to see if the file contains the xml header
                //searches for the opening and closing of the header, and the xml version line
                if (fileText.find("<?") == std::string::npos && fileText.find("xml version= \"1.0\"") == std::string::npos && fileText.find("?>") == std::string::npos )
                {
                    setError("XML header is missing\n");
                    fileError = true;
                }
                else
                {
                    //check to see if the file contains the target tag
                    if (fileText.find("<" + targetTag + ">") == std::string::npos || fileText.find("</" + targetTag + ">") == std::string::npos)
                    {
                        setError("Cannot find target tag: " + targetTag + "\n");
                        fileError = true;
                    }
                }
            }
        }
    }
    return fileError;
}


//sort the data in alphabetical order
void XmlReader::sortData()
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



//search a 1d string vector for a specific value and returns an int for the position in the vector, or -1 if no result
int XmlReader::search1dVector(std::vector<std::string> & vectorBeingSearched, std::string target)
{
    int first, last, middle, position;
    bool found, noResult;

    first = 0;
    position = -1;
    found = false;
    noResult = false;
    last = vectorBeingSearched.size();
    //bounds checking so if lower than the lowest or visa versa for highest, don't bother searching
    if (target.compare(vectorBeingSearched[0]) < 0 || target.compare(vectorBeingSearched[vectorBeingSearched.size() -1]) > 0)
        {
            noResult = true;
        }
    while (!found && !noResult)
    {
        if (middle == ((first + last) / 2))
        {
            noResult = true;
        }
        else
        {
            middle = (first + last) / 2;
        }

        if (!found && !noResult && vectorBeingSearched[middle].compare(target) == 0)
        {
            found = true;
            position = middle;
        }
        else if (!found && !noResult && vectorBeingSearched[middle].compare(target) > 0)
        {
            last = middle - 1;
        }
        else if (!found && !noResult && vectorBeingSearched[middle].compare(target) < 0)
        {
            first = middle + 1;
        }
    }
    return position;
}


//PRIVATE MEMBERS


//finds the target tag starting at the read position
//returning only the next of the target tag plus the tags content
//works for tags with child tags
bool XmlReader::findNextOfTag(std::string targetTag, std::string text)
{
    unsigned int finish, start;
    bool processing = true;
    std::string tagPlusContent;

    //find the start of the target tag starting the search from position: startPos
    start = text.find("<" + targetTag + ">", readPos);
    if (start == std::string::npos)
    {
        processing = false;
    }
    //find the closest closing tag for the target
    finish = text.find("</" + targetTag + ">", start) + (targetTag.length() + 3);
    if (finish == std::string::npos)
    {
        processing = false;
    }

    if (processing)
    {
        //create substring with tags
        tagPlusContent = text.substr(start, finish - start);
        data.push_back(tagPlusContent);
    }
    //this sets up for next line and sets to npos when finished
    readPos = finish;
    return processing;

}

//removes the first instance of target tag in an XML string
//used for removing the first instance of a target tag
std::string XmlReader::removeTag(std::string text, std::string tag)
{
    return text.substr(text.find("<" + tag + ">", 0) + tag.length() + 2, (text.length() - ((2 * tag.length()) + 5)));
}

//strip the first instance of a target tag from every item in data[]
void XmlReader::removeTagsFromData(std::string tag)
{
    for (unsigned int c = 0; c < data.size(); c++)
    {
        //check to make sure the tag is there
        if (data[c].find("<" + tag + ">") != std::string::npos && data[c].find("</" + tag + ">") != std::string::npos)
        {
            //remove the tag
            data[c] = removeTag(data[c], tag);
        }
    }
}

//get the first tag in a string
std::string XmlReader::getFirstTag(std::string inputData)
{
    return inputData.substr(inputData.find("<") + 1, inputData.find(">") - 2);
}

std::string XmlReader::stripOuterTag(std::string inputData)
{
    std::string tag = getFirstTag(inputData);
    std::string dataMinusTag = inputData.substr(inputData.find(">") + 1, inputData.find("</" + tag + ">")  - (tag.length() + 3));
    return dataMinusTag;
}

//this struct returns true if the file is detected using stat
//this is the fastest possible method to detect files
bool XmlReader::fileExists (const std::string& path)
{
  struct stat buffer;
  return (stat (path.c_str(), &buffer) == 0);
}

//takes a file and reads it into a string
std::string XmlReader::readFileToString(std::string path)
{
    std::ifstream file;
    std::string text;
    file.open(path.c_str());
    //check to see if files exists and set text to error if so
    if (!fileExists(path))
    {
        printf("ERROR file not found\n");
        fileIsLoaded = false;
        text = "ERROR";
    }
    else
    {
        //copy the contents of the file to the string character by character
        //(probably super slow gonna find a better solution)
        fileIsLoaded = true;
        char c;
        if (file.is_open() && file.good())
        {
            while (file.get(c))
            {
                text += c;
            }

            file.close();
        }
    }
    //returns the file contents if the file exists
    //otherwise returns "ERROR"
    return text;
}


//ERROR SYSTEM

std::vector<std::string> XmlReader::getError()
{
    return errorLog;
}

void XmlReader::setError(std::string error)
{
    errorLog.push_back(error);
}

bool XmlReader::isError()
{
    return fileError;
}





std::vector<std::vector<std::vector<std::string> > >XmlReader::getSceneInfo(std::string inputData)
{
    bool processing = true;
    readPos = 0;
    unsigned int start, finish, start2;
    std::string tag, tag2, content, readFrom;
    std::vector<std::string> processedItem;
    std::vector<std::vector<std::vector<std::string> > > outputData;
    readFrom = inputData;
    //each iteration is a tag being processed
    //note that any child tags and content will still be one big string
    //it will look like: [0][0] = tag [0][1] = one long string of inner tags and content
    while (processing)
    {
        //find the start of the current tags opening
        start = readFrom.find("<", readPos);
        if (start == std::string::npos)
        {
            processing = false;
        }
        //find the end of the current tags opening
        finish = readFrom.find(">", readPos);
        if (finish == std::string::npos)
        {
            processing = false;
        }
        if (processing)
        {
            //create a string of the tag (no arrow bracket)
            tag = readFrom.substr(start + 1, (finish - 1) - start);
        }

        //set start to after current tag, and find closing tag
        start2 = finish + 1;
        if (start2 == std::string::npos)
        {
            processing = false;
        }
        finish = readFrom.find("</" + tag + ">", start);
        if (finish == std::string::npos)
        {
            processing = false;
        }
        if (processing)
        {
            tag2 = readFrom.substr(finish + 1, (finish + tag.length() + 1));
        }
        //create a 1d vector of the tag and the content, then push it to the 2d vector
        if (processing)
        {
            content = readFrom.substr(start - 1, (finish + tag.length() + 1) - start + 3);
            content = stripOuterTag(content);
            content.append("<dataType>" + tag + "</dataType>");

            processedItem.push_back(content);
            readPos = finish + tag.length() + 3;
            content.clear();
            //processing = false;
        }
    }
    for (unsigned int c = 0; c < processedItem.size(); c++)
        {
            outputData.push_back(getTagsAndData(processedItem[c]));
        }
    return outputData;
}




/*
 *  reads a spot in data[] and returns a vector containing the data
 *  returns a 2d vector of strings of the xml data
 *  each inner vector is a vector of strings
 *  each vector of strings represents a tag inside the outer tag
 *  the first string in [0] is the tag (minus the "<" ">")
 *  the second string is the data inside the tag
 */
std::vector<std::vector<std::string> > XmlReader::getTagsAndData(std::string inputData)
{
    bool processing = true;
    int readPos = 0;
    unsigned int start, finish;
    std::string tag, content;
    std::vector<std::string> separatedData;
    std::vector<std::vector<std::string> > processedItem;
    //each iteration is a tag being processed
    //note that any child tags and content will still be one big string
    //it will look like: [0][0] = tag [0][1] = one long string of inner tags and content
    while (processing)
    {
        //find the start of the current tags opening
        start = inputData.find("<", readPos);
        if (start == std::string::npos)
        {
            processing = false;
        }
        //find the end of the current tags opening
        finish = inputData.find(">", readPos);
        if (finish == std::string::npos)
        {
            processing = false;
        }
        if (processing)
        {
            //create a string of the tag (no arrow bracket)
            tag = inputData.substr(start + 1, (finish - 1) - start);
            //std::cout << "\ntag output\n" << tag << "\n\n";
        }

        //set start to after current tag, and find closing tag
        start = finish + 1;
        if (start == std::string::npos)
        {
            processing = false;
        }
        finish = inputData.find("</", start);
        if (finish == std::string::npos)
        {
            processing = false;
        }
        //create a 1d vector of the tag and the content, then push it to the 2d vector
        if (processing)
        {
            content = inputData.substr(start, (finish) - start);
            separatedData.push_back(tag);
            separatedData.push_back(content);
            processedItem.push_back(separatedData);

            readPos = finish + tag.length() + 3;
            separatedData.clear();
        }
    }
    return processedItem;
}

//sorts the attributes (tags) within the objects to make the searchable
void XmlReader::sortAttributes(std::vector<std::vector<std::string> > & item)
{
    int minIndex;
    std::string minValue;
    for (unsigned int start = 0; start < (item.size() - 1); start++)
    {
        minIndex = start;
        minValue = item[start][0];
        for (unsigned int index = start + 1; index < item.size(); index++)
        {
            if (item[index][0] < minValue)
            {
                minValue = item[index][0];
                minIndex = index;
            }
        }
        swap(item[minIndex], item[start]);
    }
}


//searches the [0] space in each vector in a 2d vector for a string.  returns the position, or -1 if no result
int XmlReader::findAttribute(std::vector<std::vector<std::string> > & vectorBeingSearched, std::string target)
{
    int first, last, middle, position;
    bool found, noResult;

    first = 0;
    position = -1;
    found = false;
    noResult = false;
    last = vectorBeingSearched.size();
    //bound checking again
    if (target.compare(vectorBeingSearched[0][0]) < 0 || target.compare(vectorBeingSearched[vectorBeingSearched.size() -1][0]) > 0)
        {
            noResult = true;
        }
    //binary search
    while (!found && !noResult)
    {
        if (middle == ((first + last) / 2))
        {
            noResult = true;
        }
        else
        {
            middle = (first + last) / 2;
        }

        if (!found && !noResult && vectorBeingSearched[middle][0].compare(target) == 0)
        {
            found = true;
            position = middle;
        }
        else if (!found && !noResult && vectorBeingSearched[middle][0].compare(target) > 0)
        {
            last = middle - 1;
        }
        else if (!found && !noResult && vectorBeingSearched[middle][0].compare(target) < 0)
        {
            first = middle + 1;
        }
    }
    return position;
}



//selection sort for sorting a 3d vector of items
void XmlReader::sortItems(std::string target, std::vector<std::vector<std::vector<std::string> > > & inputList)
{
    int minIndex;
    std::string minValue;

    for (unsigned int start = 0; start < (inputList.size() -1); start++)
    {
        minIndex = start;
        minValue = inputList[start][findAttribute(inputList[start], target)][1];
        for (unsigned int index = start + 1; index < inputList.size(); index++)
        {

            if (inputList[index][findAttribute(inputList[index], target)][1] < minValue)
            {
                minValue = inputList[index][findAttribute(inputList[index], target)][1];
                minIndex = index;
            }
        }
        swap(inputList[minIndex], inputList[start]);
    }
}

std::vector<int> XmlReader::index3dListByTag(std::string target, std::vector<std::vector<std::vector<std::string> > > inputList)
{
    std::vector<int> objectNameIndex;
    for (unsigned int c = 0; c < inputList.size(); c++)
        {
            objectNameIndex.push_back(findAttribute(inputList[c], target));
            //std::cout << "\n\n\n" << objectNameIndex[c] << "\n\n\n";
        }
    return objectNameIndex;
}


//binary search using the name index for finding objects
int XmlReader::indexSearch3d(std::vector<std::vector<std::vector<std::string> > > vectorBeingSearched, std::vector<int> index, std::string target)
{
    int first, last, middle, position;
    bool found, noResult;
    std::string currentString;

    first = 0;
    position = -1;
    found = false;
    noResult = false;
    last = vectorBeingSearched.size();
    //bounds checking.  if the search target is out of bounds no need to search because it's not there
    if (target.compare(vectorBeingSearched[0][index[0]][1]) < 0 || target.compare(vectorBeingSearched[vectorBeingSearched.size() - 1][index[vectorBeingSearched.size() - 1]][1]) > 0)
        {
            noResult = true;
        }
    while (!found && !noResult)
    {
        if (middle == ((first + last) / 2))
        {
            noResult = true;
        }
        else
        {
            middle = (first + last) / 2;
        }

        if (!found && !noResult && vectorBeingSearched[middle][index[middle]][1].compare(target) == 0)
        {
            found = true;
            position = middle;
        }
        else if (!found && !noResult && vectorBeingSearched[middle][index[middle]][1].compare(target) > 0)
        {
            last = middle - 1;
        }
        else if (!found && !noResult && vectorBeingSearched[middle][index[middle]][1].compare(target) < 0)
        {
            first = middle + 1;
        }
    }
    return position;
}
