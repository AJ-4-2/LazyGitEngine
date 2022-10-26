#ifndef XMLREADER_H
#define XMLREADER_H
#include <string>
#include <vector>
#include <iostream>
#include "FileReader.h"

class XmlReader : public FileReader
{
    public:
        XmlReader();
        virtual ~XmlReader();


        bool validateFileType(std::string, std::vector<std::string> &);
        bool validateContents(std::string, std::string, std::vector<std::string> &);

        std::string processFile(std::string, std::vector<std::string> &);

    protected:

    private:
        bool fileError;


};

#endif // XMLREADER_H
