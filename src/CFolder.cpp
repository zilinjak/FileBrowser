/*
 * @author Zilinek Jakub 
 * on 08.05.20
 */

#include "CFolder.h"

using namespace std;

CFolder::CFolder( string & inPath ){

    if ( inPath[ inPath.size() - 1] != '/' )
        inPath = ( inPath + string("/"));
    struct stat info{};
    struct dirent * entry;
    DIR * dir;
    dir = opendir( inPath.c_str() ) ;
    if (dir){
        this->setPath( inPath.c_str() );
        while (	( entry = readdir(dir) ) != nullptr) { // going through all the files
            string path = this->getPath() + string(entry->d_name);
            stat ( path.c_str() , &info );
            if ( filesystem::is_symlink(inPath + entry->d_name) ){
                m_InFiles["SymLinks"].push_back( new CSymlink(path) );
            }
            else if ( S_ISDIR(info.st_mode) != 0  ){
                m_InFiles["Directories"].push_back( new CFolder ( path.c_str() ) ) ;
            }
            else if ( S_ISREG(info.st_mode) != 0 ){
                m_InFiles["Files"].push_back(new CFile ( info , entry->d_name , path.c_str() ) );
            }
        }
        closedir(dir);
    } else
        m_error = true;
}

ostream& operator << (ostream& os, const CFolder& x){
    x.printAll();
    return os;
}

/**recursive call to get size of our currently opened folder*/
off_t CFolder::getSize()const {
    off_t result = 0;
    /*recursive call of getSize to all subfolders returning size of all files inside of these folders*/
    try {
        /*directory iterator*/
        for (filesystem::directory_entry const &entry : filesystem::directory_iterator(m_Path)) {
            if (entry.is_regular_file() && !entry.is_symlink())
                result += entry.file_size();
            else if (entry.is_directory() && !entry.is_symlink()) {
                string tmpPath = m_Path + string(entry.path().filename());
                CFolder tmp(tmpPath);
                result += tmp.getSize();
                tmp.ClearMemory();
            }
        }
    } catch (filesystem::filesystem_error & e){
        cout << "Dont exit, we are still calculating.\n\n";
        cout << e.what() << endl;
        return 0;
    }
    return result;
}

/**Updates folder with path we pass it in parameter*/
void CFolder::UpdateFolder(CFolder &folder , string & path) {
    folder.ClearMemory();
    folder = CFolder( path );
}

/**Methods that we use to find some file/folder/link name in our currently opened folder. If we want to
 * find folder progtest inside of our currently opened folder we use findFolder("progtest"), if we find progtest folder
 * we return true, otherwise false*/
bool CFolder::findFile(const string & target) const {
    for (auto & it : m_InFiles){
        if (it.first == "Files")
            for ( auto & it2 : it.second )
                if (it2->getName() == target)
                    return true;
    }
    return false;
}
bool CFolder::findFolder(const string& target) const {
    for (auto & it : m_InFiles){
        if (it.first == "Directories")
            for ( auto & it2 : it.second )
                if (it2->getName() == target)
                    return true;
    }
    return false;

}
bool CFolder::findLink (const string& target) const {
    for (auto & it : m_InFiles){
        if (it.first == "SymLinks")
            for ( auto & it2 : it.second )
                if (it2->getName() == target)
                    return true;
    }
    return false;
}

void CFolder::printAll() const {
    system("clear");
    for ( auto & it : m_InFiles ) {
        cout << "\n\t" << it.first << endl << endl;
        for (auto &it2 : it.second) //CFile, CFolder, CSymLink
            it2->print();
    }
}
void CFolder::print()const{
    cout << m_Name << endl;
}

CFolder::CFolder(const char *inPath) {
    m_Path = inPath;
    m_Name = filesystem::path(m_Path).filename().string();
}

CFolder &CFolder::operator=(const CFolder &x) {
    this->m_error = x.m_error;
    this->m_Name =  x.m_Name;
    this->m_Path = x.m_Path;
    this->m_InFiles = x.m_InFiles;
    return *this;
}

void CFolder::ClearMemory() {
    for ( auto & it : m_InFiles ) {
        for (auto &it2 : it.second) {
            delete it2;
        }
    }
}
