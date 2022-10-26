#include "XmlData.h"
#include <stdio.h>

XmlData::XmlData(std::string data, int readPosition)
{
    //noFurtherTags = false;
    //std::cout << "\n\n\n\n\n BEGIN...................\n\n";
    finished = false;
    readPos = readPosition;
    if (extractTagsAndContent(data))
    {
        //clear data to free the memory
        data = "";
        //std::cout << "DATA POST READ: " << data << "\n\n";
        //std::cout << tagList[0] << "\n\n~~~~~~~~~\n\n" << contentList[0] << "\n\n";

        //start drilling down, going through each part in the vector

        for (int c = 0; c < childList.size(); c++)
        {
            //std::cout << "\nCONTENT::::::   " << childList[c] << "\n\n~~~~~~~~";
            //std::cout << "\n\n~~~~~pre buffer~~~~\n\n";
            buffer = new XmlData(childList[c], 0);
            //std::cout << "\n\n~~~~~post buffer~~~~\n\n";
            contentObjectList.push_back(*buffer);
            //std::cout << "\n\n~~~~~post push back~~~~\n\n";
            delete buffer;
            //std::cout << tagList[c] << "\n\n~~~~~~~~~\n\n" << contentList[c] << "\n\n";
        }
        for (int c = 0; c < contentList.size(); c++)
        {
            //std::cout << "\nCONTENT::::::   " << contentList[c] << "\n\n~~~~~~~~";
            //std::cout << tagList[c] << "\n\n~~~~~~~~~\n\n" << contentList[c] << "\n\n";
        }
    }
    else
    {
        std::cout << "ERROR\n\n";
    }
    //std::cout << "\n...................\n\n" << data << "\n...................\n";
    //std::cout << "\n END...................\n\n";
    std::vector<bool> test;
    //test.append(finished);

}
//when making a new object from the content of a tag
XmlData::XmlData(std::string content)
{
    //std::cout << "hiya\n\n";
    //ctor
    //xmlData = new XmlData();
}

XmlData::~XmlData()
{
    //dtor
    for (unsigned int c = 0; c < contentObjectList.size(); c++)
    {
        //delete contentObjectList[c];
    }
    //delete xmlData;
}


/*
//so we want to figure out if the content contains a tag or data
//check to see if theres an open and close tag
//this is becoming more of an extract tag
*/
//exit points:  - found tag (data inside can be blank)
//              - no further outer tag found
//              - tag found but validation error (no matching closing tag, error in tag syntax)
bool XmlData::extractTagsAndContent(std::string text)
{
    bool valid = false;
    //look for the first tag in the text
    unsigned int pos1 = text.find("<", readPos);
    unsigned int pos2 = text.find(">", pos1);

    //verify the tag exists
    if (pos1 != std::string::npos && pos2 != std::string::npos)
    {
        //check for error in opening tag
        if (text.find("<", pos1 + 1) < pos2)
        {
            std::cout << "open tag error\n";
        }
        else
        {
            //gotta make sure theres no slash in an open tag
            if (text.find("/", pos1) < pos2)
            {
                std::cout << "close tag found before open tag\n";
            }
            else
            {
                //set "tag" to the text inside to arrows
                std::string tag = text.substr(pos1 + 1, (pos2 - pos1 - 1));

                //find the first instance of a matching closing tag,
                //starting point of after the right bracket of the opening tag
                pos1 = text.find("</" + tag + ">", pos2 + 1);
                //verify the closing tag exists
                if (pos1 != std::string::npos)
                {
                    valid = true;//contains matching closing tag
                    tagList.push_back(tag);
                    //std::cout << "----------\nTAG:  " << tagList[tagList.size() - 1] << "\n----------\n\n";
                    //detect if content contains a tag
                    if (text.substr(pos2 + 1, pos1 - (pos2 + 1)).find("<") == std::string::npos)
                    {
                        contentList.push_back(text.substr(pos2 + 1, pos1 - (pos2 + 1)));
                    }
                    else
                    {
                        childList.push_back(text.substr(pos2 + 1, pos1 - (pos2 + 1)));
                        contentList.push_back("TAG");
                        childListIndex.push_back(contentList.size() - 1);
                    }



                    //detect end of file
                    readPos = pos1 + tag.length() + 3;
                    if (text.find("<", readPos) == std::string::npos)
                    {
                        //std::cout << "no further tags detected\n\n";
                        noFurtherTags = true;
                    }
                    //recursively check for more tags
                    else if(!extractTagsAndContent(text))
                    {
                        valid = false; //this will cascade down an error if there is one
                    }
                }
                else
                {
                    std::cout << "close tag error\n";
                }
            }
        }
    }
    else
    {
        std::cout << "\n~~~no tag found~~~\n";
    }
    return valid;
}



/*
    now we need to figure out how to extract this data from the object tree we built
    start at top of tree (lowest depths of the levels)
        keep track of the depth number
        segment out main categories at highest level under <xml>
        for each category, start at lowest depth point
        start building the vector of data, keeping track of the number of dimensions as you go up
        if/else to add to higher dimension vectors if (dimension == 1) {...} else if (dimension == 2) {...} etc
        if i can get the variable type i can make it more efficient and not need repeating code

*/

/*

    okay so at the most basic level, i would read the tag, the content, see if the content contains deeper tags,
    and all 3 of those read in deeper level objects

*/


//returns an integer value representing the deepest part of the data tree
int XmlData::getDepth()
{
    int buffer;
    if (!contentObjectList.empty())
    {
        buffer = contentObjectList[0].getDepth() + 1;
        for (unsigned int c = 0; c < contentObjectList.size(); c++)
        {
            depth = contentObjectList[c].getDepth() + 1;
            if (depth < buffer)
            {
                depth = buffer;
            }
            else
            {
                buffer = depth;
            }
        }
    }
    else
    {
        depth = 0;
    }
    return depth;
}



std::vector<std::string> XmlData::getTagList()
{
    return tagList;
}


std::vector<std::string> XmlData::getContentList()
{
    return contentList;
}

std::string XmlData::getTag(unsigned int index)
{
    //std::string s = contentObjectList[0].getTag[index];
    return tagList[index];
}


std::string XmlData::getContent(unsigned int index)
{
    return contentList[index];
}
XmlData XmlData::getChild(unsigned int index)
{
    return contentObjectList[index];
}

void XmlData::getTest()
{
    std::cout << "\n-------------\n";
    std::string s = contentObjectList[0].contentObjectList[0].getContent(0);
    std::cout << s << "\n-------------\n\n";
    return;
}
/*
std::string XmlData::getChild()
{

}
*/

