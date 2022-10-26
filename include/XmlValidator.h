#ifndef XMLVALIDATOR_H
#define XMLVALIDATOR_H
#include <string>
#include <vector>
#include <iostream>

//error checking system for validating various aspects of an xml file
class XmlValidator
{
    public:
        XmlValidator();
        virtual ~XmlValidator();
        bool validateFileType(std::string, std::vector<std::string> &);
        bool validateContents(std::string, std::string, std::vector<std::string> &);

    protected:

    private:
        bool fileError;



};

#endif // XMLVALIDATOR_H
