#include "searchSort.h"
#include <string>
#include <vector>

//this is a binary search
int searchForString(std::vector<std::string> data, std::string str)
{
    int first = 0,              //first vector element
        last = data.size(),     //last vector element
        middle,                 //midpoint of the search
        position = -1;          //position of the search value
    bool found = false;

    while (!found)
    {
        middle = (first + last) / 2;   //calculate midpoint
        if (data[middle] == str)
        {
            found = true;
            position = middle;
        }
        else if (data[middle] > str)
        {
            last = middle - 1;
        }
        else
        {
            first = middle + 1;
        }
    }
    return position;
}
