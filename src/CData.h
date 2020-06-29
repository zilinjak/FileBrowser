/*
 * @author Zilinek Jakub 
 * on 08.05.20
 */


/** This is an abstract class. We are having bunch of getters but we have the abstract method called print().
 * This method prints info of your chosen data type.
 *
 * From this class we inherit class CFolder and CFile and CSymLink
 */


#pragma once
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <map>


using namespace std;
class CData{
protected:
    string m_Name; //name of file/folder
    string m_Path; //full path to file/folder
public:
    CData() = default;
    virtual ~CData() = default;
    CData & operator = (const CData & x) = default;

    string getName()const;
    string getPath()const;
    void setPath(const char * path);
    void setName(const char * name);

    virtual void print() const = 0;
};

