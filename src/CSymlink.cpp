/*
 * @author Zilinek Jakub 
 * on 27.06.2020
 */
#include "CSymlink.h"

CSymlink::CSymlink(const string & path) {
    m_Target = filesystem::read_symlink(path);
    m_Path = path;
    m_Name = filesystem::path(m_Path).filename();
}

void CSymlink::print() const {
    cout << m_Name << " ---> " << m_Target << endl;
}

off_t CSymlink::getSize() const {
    cout << "This is symlink, we are sorry but we are not providing an size of symlink." << endl;
    return 0;
}

bool CSymlink::operator<(const CSymlink &x) const {
    string z = x.m_Path;
    string y = this->m_Path;
    transform(z.begin() , z.end() , z.begin() , ::tolower); /*need to transform them to lower to get nice compare*/
    transform(y.begin() , y.end() , y.begin() , ::tolower);
    return ! (z < y);
}
