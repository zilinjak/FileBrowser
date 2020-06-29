/*
 * @author Zilinek Jakub 
 * on 11.05.20
 */

#include "CMove.h"

bool CMove::UserInput() {
    cout << "Folder we are moving: ";
    //Inputs returns false if input is "exit"
    if ( Inputs(m_PathFrom) ){
        cout << "Target path: ";
        return Inputs(m_PathTo);
    }
    else
        return false;
}

/**
 * This method is gonna set m_PathFrom and m_PathTo to its full path -> or if they are invalid it will log an error
 * Also we are giving it a parameter of folder so we can look in folder set -> files and sub-folder
 * current implementation is always returning true because filesystem::rename will throw an error incase we fail
 */
bool CMove::ValidatePath(const CFolder & folder , string & current_m_Path) {
        /*setting up m_PathFrom*/
    if ( folder.findFolder(m_PathFrom) || folder.findFile(m_PathFrom) || folder.findLink(m_PathFrom) )
        m_PathFrom = folder.getPath() + m_PathFrom;
    if (*m_PathFrom.begin() != '/')
        m_PathFrom = "/" + m_PathFrom;
    m_PathFrom = filesystem::path(m_PathFrom).lexically_normal();

        /*setting up m_PathTo*/
    if ( folder.findFolder(m_PathTo) ) {
        m_PathTo = folder.getPath() + m_PathTo + "/" + filesystem::path(m_PathFrom).filename().string();
        m_PathTo = filesystem::path(m_PathTo).lexically_normal();
    }
    if (*m_PathTo.begin() != '/')
        m_PathTo = "/" + m_PathTo;
    m_PathTo = filesystem::path(m_PathTo).lexically_normal();

    /*Checking if we are not moving our currently opened folder if so we set current_m_Path to m_PathTo*/
    if ( current_m_Path.find(m_PathFrom) != string::npos ){         //EXAMPLE: current:/home/progtest/test/test/test
        current_m_Path = m_PathFrom;                                //EXAMPLE: moving /home/progtest/test/
        if ( current_m_Path[ current_m_Path.size() -1 ] == '/' )    //we set current path to moving path.parent_path()
            current_m_Path.pop_back();
        current_m_Path = filesystem::path(current_m_Path).parent_path().string();
    }
    return true;
}

/** Methods that are executing the actuall move of files, Execute will provide the operations to class variables,
 * MakeMove is an method that can do the same but to paths that we provide it in parameters. */
bool CMove::Execute()const{
    if (filesystem::is_symlink(m_PathFrom) && filesystem::is_directory(m_PathTo) ){ //filesystem::rename seems to not work with symLinks
        system( ("mv " + m_PathFrom + " " + m_PathTo).c_str() );
        return true;
    }
    try {
        filesystem::rename(filesystem::path(m_PathFrom), filesystem::path(m_PathTo));
    } catch (filesystem::filesystem_error & e){
        cout << e.what() << endl;
        return false;
    }
    return true;
}
bool CMove::MakeMove(const string &from, const string &to) {
        if (filesystem::is_symlink(from) && filesystem::is_directory(to) ){ //filesystem::rename seems to not work with symLinks
            system( ("mv " + from + " " + to).c_str() );
            return true;
        }
        try {
            filesystem::rename(filesystem::path(from), filesystem::path(to));
        } catch (filesystem::filesystem_error & e){
            cout << e.what() << endl;
            return false;
        }
        return true;
}

