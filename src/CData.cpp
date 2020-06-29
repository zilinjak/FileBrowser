/*
 * @author Zilinek Jakub 
 * on 08.05.20
 */

#include "CData.h"

void CData::setPath(const char * path){
    this->m_Path = path;
}
void CData::setName(const char * name){
    this->m_Name = name;
}

string CData::getName()const{
    return this->m_Name;
}
string CData::getPath()const{
    return this->m_Path;
}