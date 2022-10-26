#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <vector>
/*
* loads files and reads them to strings
 Make this a new class: validates, and manages xml files, and prepares them for parsing
*/
class FileManager
{
    public:
        FileManager();
        virtual ~FileManager();
        std::string processFile(std::string path);

    protected:

    private:

        bool fileError;
        std::string readFileToString(std::string);
        bool fileExists (const std::string&);
        void setError(std::string);
        bool getFileError(std::string);


        std::vector<std::string> errorLog;
        std::vector<std::string> getError();


        std::string fileContent;






        //fileContentList and fileNameList are parallel.  the later is to identify the former
        std::vector<std::string> fileContentList;
        std::vector<std::string> fileNameList;
};

#endif // FILEMANAGER_H
