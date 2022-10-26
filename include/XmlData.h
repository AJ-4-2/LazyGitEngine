#ifndef XMLDATA_H
#define XMLDATA_H
#include <iostream>
#include "XmlData.h"
#include <string>
#include <vector>
class XmlData
{
    public:
        XmlData(std::string, int);
        XmlData(std::string);
        XmlData* buffer;
        virtual ~XmlData();
        XmlData* xmlData;
        void getNextOuterTag(std::string);
        int readPos;
        std::string content;
        bool finished;
        bool noFurtherTags;


        int depth;
        int getDepth();

        //tagList and contentList are parallel
        std::vector<std::string> tagList;
        std::vector<std::string> contentList;
        std::vector<std::string> childList; //list of content that contains tags
        std::vector<XmlData> contentObjectList;
        std::vector<unsigned int> childListIndex; //index of object positions in content list. runs parallel to contentObjectList
        XmlData getChild(unsigned int);

        //std::vector<XmlData>
        bool extractTagsAndContent(std::string);

        bool hasChildren;

        std::vector<std::string> getTagList();
        std::vector<std::string> getContentList();
        std::string getTag(unsigned int);
        std::string getContent(unsigned int);

        void getTest();


    protected:

    private:
};

#endif // XMLDATA_H
