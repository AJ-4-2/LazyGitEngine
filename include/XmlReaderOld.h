#ifndef XMLREADEROLD_H
#define XMLREADEROLD_H

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdio.h>

/*XmlReader.h
 * Author: Ytivarg
 * Description: Takes an XML file and a target tag, searches for each instance of that tag,
 * and stores the info with the target tags stripped out into a vector
 * This prepares the data for further processing based on the type of data
 */

class XmlReaderOld
{
    public:
        XmlReaderOld();
        XmlReaderOld(std::string, std::string);
        virtual ~XmlReaderOld();

        //return the entire vector
        std::vector<std::string> getData();
        //return an item at an address of the vector
        std::string getItem(int);
        //get the size of the data vector
        unsigned int getSize();

        std::vector<std::string> getError();
        bool isError();

    protected:

        void readTagFromFile(std::string, std::string);

        bool getFileError(std::string, std::string);
        //sorts string data (1d vector) in ascii order to make it searchable
        void sortData();

        //simple binary search in a sorted 1d string vector
        int search1dVector(std::vector<std::string> &, std::string);

        void setError(std::string);



        std::vector<std::vector<std::string> > getTagsAndData(std::string);

        //sorts the attributes in the objects to make searching them faster
        void sortAttributes(std::vector<std::vector<std::string> > &);

        //2d vector search for object attributes
        int findAttribute(std::vector<std::vector<std::string> > &, std::string);

        void sortItems(std::string, std::vector<std::vector<std::vector<std::string> > > &);

        std::vector<int> index3dListByTag(std::string , std::vector<std::vector<std::vector<std::string> > > );

        //searches for an object based off of the name index
        int indexSearch3d(std::vector<std::vector<std::vector<std::string> > >, std::vector<int>, std::string);
        //the vector storing the data
        std::vector<std::string> data;
        bool fileError;

        std::vector<std::vector<std::vector<std::string> > > getSceneInfo(std::string);
        //finds the next instance of a tag
        bool findNextOfTag(std::string, std::string);
    private:

        unsigned int readPos;

        //returns a string stripped of the first instance of a target tag
        std::string removeTag(std::string, std::string);
        //iterates through data calling removeTag on each element on a target tag
        void removeTagsFromData(std::string);
        std::string stripOuterTag(std::string);
        std::string getFirstTag(std::string);

        //file validation
        bool  fileExists (const std::string &);
        bool fileIsLoaded;

        std::string fileText;
        std::string readFileToString(std::string);
        //bool fileError;


        std::vector<std::string> errorLog;





};

#endif // XMLREADEROLD_H



