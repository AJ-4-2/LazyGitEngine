#ifndef OBJHANDLER_H
#define OBJHANDLER_H

#include "XmlReaderOld.h"
#include "Entity.h"
#include "Player.h"
#include "Background.h"

/*
 * uses the XmlReader as a parent class to read object data from an xml file
 * The object xml file is structured as follows with each objects denoted with a <obj> </obj> tag:
 *  <objects>
 *      <obj>
 *		    <objType>background</objType>
 *		    <name>background0</name>
 *	        <image>img/background0.png</image>
 *      </obj>
 *      <obj>
 *		    <objType>type of object</objType>
 *		    <any other tags the object might have> attribute data </end tag>
 *      </obj>
 *  </objects>
 *
 * The data is extracted into a sorted 3d vector
 * The vector structure is as follows: [object][attribute][data]
 * the first dimension represents each individual object
 * the second dimension represents the location of an attribute for the object
 * for the third dimension, [0] is the type of attribute (the tag, i.e. <objType> or <name>)
 * and [1] is the data for the attribute (the data between the tags)
 */
class ObjHandler: public XmlReaderOld
{
    public:
        //the string is the path/filename for the xml file being read into the handler
        ObjHandler(std::string, std::string);
        virtual ~ObjHandler();

        std::vector<std::vector<std::string> > getObject(std::string);

    protected:

private:
        //the space between the end brackets prevents a crash
        //I don't know why, but it does
        std::vector<std::vector<std::vector<std::string> > > objectList;
        //object search index by objName
        std::vector<int> objectNameIndex;
        std::vector<int> objectTypeIndex;

        //sorts the objects in alphabetical order by name
        //void sortItems();


        std::vector<Entity*> entityList;


};

#endif // OBJHANDLER_H
