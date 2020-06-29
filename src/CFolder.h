/*
 * @author Zilinek Jakub 
 * on 08.05.20
 */

/** CFolder is  inherited by class CData. We are having abstract method called print, this prints out info of this folder
 * we are representing. Then we have method called PrintAll, this method prints out all info we know about sub-folder/files
 * We have 2 constructors, one that will set only path and name with parameter const chat * and the other one that will generate
 * everything with string constructor.
 *
 * Files and subfolder are represented by map, we have keys SymLinks, Files and Folder, and to all of these we have CData*
 * that means we can use polymorfism for printing the info from the map using print() method.
 */

#pragma once
#include "CFile.h"
#include "CData.h"
#include "CSymlink.h"
#include <filesystem>
#include <set>
#include <map>


class CFolder : public CData{
protected:
    bool m_error = false;
    map < string , vector < CData* > > m_InFiles;
public:

    ~CFolder() override = default;
    CFolder(string & inPath );          //constructor to create in structure aswell
    CFolder( const char * inPath );     //sets only the name

    friend ostream& operator << (ostream& os, const CFolder& x);
    CFolder & operator = (const CFolder & x);

    off_t getSize( )const;

    void printAll()const;
    void print() const override;
    void UpdateFolder(CFolder & folder,  string & path);
    void ClearMemory();

    bool findFolder(const string & target )const;
    bool findFile(const string& target )const;
    bool findLink(const string & target)const;
};

