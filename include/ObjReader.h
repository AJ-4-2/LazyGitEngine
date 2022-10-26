#ifndef OBJREADER_H
#define OBJREADER_H
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "searchSort.h"

class ObjReader
{
    public:
        ObjReader(std::string, std::string);
        virtual ~ObjReader();
        //return the entire vector
        std::vector<std::string> getData();
        //return an item at an address of the vector
        std::string getItem(int);
        int FindTexture(std::string);
        int getSize();
        bool getFileExists();

    protected:

    private:
        std::string tag;
        //the vector storing the data
        std::vector<std::string> data;
        void selectionSort();
        void sawp (std::string &, std::string &);
        bool  fileExists (const std::string &);
        bool fileIsLoaded;

};

#endif // OBJREADER_H

