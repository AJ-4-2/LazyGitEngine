#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>

#include <sstream>
#include <iostream>
#include <fstream>

/*
* loads files and reads them to strings
 Make this a new class: validates, and manages xml files, and prepares them for parsing
*/
class FileReader
{
    public:
        FileReader();
        virtual ~FileReader();
        std::string readFile(std::string path);
        bool getFileExists(std::string, std::vector<std::string>&);


    protected:
        bool fileExists (const std::string&);
        std::string readFileToString(std::string);

    private:
        bool getFileEmpty(std::string);


};


#endif // FILEREADER_H
