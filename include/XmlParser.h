#ifndef XMLPARSER_H
#define XMLPARSER_H
#include <string>
#include <vector>
#include <iostream>
#include "XmlData.h"

class XmlParser
{
    public:
        XmlParser();
        virtual ~XmlParser();
        void readData(std::string);
        XmlData* xmlData;
    protected:

    private:

        int readPos;


        //std::string getNextOuterTag(std::string, int);
        bool validateHeader(std::string);
};

#endif // XMLPARSER_H
