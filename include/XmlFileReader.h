#ifndef XMLFILEREADER_H
#define XMLFILEREADER_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

/*
* loads files and reads them to strings
 Make this a new class: validates, and manages xml files, and prepares them for parsing
*/
class XmlFileReader
{
    public:
        XmlFileReader();
        virtual ~XmlFileReader();
        std::string readFile(std::string path);
        bool fileExists (const std::string&);

    protected:

    private:

        bool fileError;
        std::string readFileToString(std::string);
        void setError(std::string);
        bool getFileError(std::string);


        std::vector<std::string> errorLog;
        std::vector<std::string> getError();


        std::string fileContent;






        //fileContentList and fileNameList are parallel.  the later is to identify the former
        std::vector<std::string> fileContentList;
        std::vector<std::string> fileNameList;
};


#endif // XMLFILEREADER_H
