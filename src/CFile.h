/*
 * @author Zilinek Jakub 
 * on 08.05.20
 */

#pragma once
#include "CData.h"
#include <sys/stat.h>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <strings.h>
#include <stdio.h>
#include <string.h>

/** Class that is inherited from CData. GetSize() is very simple, we use stat.h to
 * give us file size. Print() will print out name and stats of this file we are representing
 * constructor is very simple, it takes stat info, name and path and will set its variable to it.
 *  This class is just representing us File in filesystem.
 */


class CFile : public CData{
protected:
    struct stat m_Info;
public:
    ~CFile() = default ;
    CFile(struct stat & info, const char * name, const char * path);
    friend ostream& operator << (ostream& os, const CFile& x);
    CFile & operator = (const CFile & x) = default;
    bool operator < (const CFile & x)const;


    off_t getSize( )const{ return m_Info.st_size; }
    void print () const override;
};
