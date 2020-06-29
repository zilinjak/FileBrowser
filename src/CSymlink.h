/*
 * @author Zilinek Jakub 
 * on 27.06.2020
 */
#pragma once
#include "CData.h"
#include <filesystem>


/**child of CData, having all abstract methods, print() method will print name and target of symlink*/
class CSymlink : public CData{
protected:
    string m_Target;
public:
    ~CSymlink() = default;
    CSymlink(const string & path);
    CSymlink & operator = (const CSymlink & x) = default;

    void print()const override;
    off_t getSize( )const;

    bool operator < (const CSymlink & x)const;
};
