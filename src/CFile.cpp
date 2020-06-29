/*
 * @author Zilinek Jakub 
 * on 08.05.20
 */

#include "CFile.h"

CFile::CFile(struct stat & info, const char * name, const char * path){
    this->m_Path = path;
    this->m_Info = info;
    this->m_Name = name;
}
ostream& operator << (ostream& os, const CFile& x){
    struct tm * timeinfo;
    timeinfo = localtime ( &x.m_Info.st_ctime );
    char buffer[32];
    strftime(buffer, 32, "%d.%m.%Y, %H:%M:%S", timeinfo);
    os << x.m_Name << "\t\t";
    if ( x.getSize() < 1024)
        os << fixed << setprecision(2) << float( x.getSize() ) << " B, \t\tLast Mod: " << buffer ;
    else if ( x.getSize() < 1024*1024)
        os << fixed << setprecision(2) << (float( x.getSize())/1024) << " KB, \t\tLast Mod: " << buffer ;
    else if ( x.getSize() < 1024*1024*1024)
        os << fixed << setprecision(2) << (float( x.getSize())/(1024*1024)) << " MB, \t\tLast Mod: " << buffer ;
    else
        os << fixed << setprecision(2) << (float( x.getSize())/float(1024*1024*1024)) << " GB, \t\tLast Mod: " << buffer ;
    return os;
}

bool CFile::operator < (const CFile &x) const {
    string z = x.m_Name;
    string y = this->m_Name;
    transform(z.begin() , z.end() , z.begin() , ::tolower); /*need to transform them to lower to get nice compare*/
    transform(y.begin() , y.end() , y.begin() , ::tolower);
    return ! (z < y);
}

void CFile::print() const {
    cout << *this << endl;
}
