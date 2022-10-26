/*XmlReader.h
 * Author: Ytivarg
 * Description: Takes an XML file and a tag, searches for each instance of that tag,
 * and stores the info with all tags stripped out into a vector
 * Still very simple, but works for what is needed now and will be updated if needed
 * designed to work with data that looks like this: <tag>data</tag>
 * works when nested, but only tested for single item tags at the lowest level
 */
#ifndef XMLREADER_H
#define XMLREADER_H
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "searchSort.h"

class XmlReader
{
    public:
        XmlReader(std::string, std::string);
        virtual ~XmlReader();
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

#endif // XMLREADER_H





/*XmlReader.h
 * Author: Ytivarg
 * Description: Takes an XML file and a tag, searches for each instance of that tag,
 * and stores the info with all tags stripped out into a vector
 * Still very simple, but works for what is needed now and will be updated if needed
 * designed to work with data that looks like this: <tag>data</tag>
 * works when nested, but only tested for single item tags at the lowest level
 */
#ifndef XMLREADER_H
#define XMLREADER_H
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "searchSort.h"


class XmlReader
{
    public:
        XmlReader(std::string, std::string);
        XmlReader(std::string);
        virtual ~XmlReader();

        //return the entire vector
        std::vector<std::string> getData();
        //return an item at an address of the vector
        std::string getItem(int);
        int FindTexture(std::string);
        int getSize();
        bool getFileExists();


        void loadFile(std::string);
        void processFile(std::string);


    protected:

    private:
        std::string tag;
        //the vector storing the data
        std::vector<std::string> data;
        std::string text;
        void selectionSort();
        void sawp (std::string &, std::string &);
        bool  fileExists (const std::string &);
        bool fileIsLoaded;
};

#endif // XMLREADER_H
