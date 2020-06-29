/*
 * @author Zilinek Jakub 
 * on 11.05.20
 */
#include "CDelete.h"

/**Takes Users Input, returns false if he wants to exit*/
bool CDelete::UserInput() {
    string input;
    cout << "Type path to file u want to delete:";
    getline( cin , input);
    if ( cin.eof() ) {
        return false;
    }
    if (input == "exit")
        return false;
    else {
        delete_Path = input;
        delete_Path = filesystem::path(delete_Path).lexically_normal();
        return true;
    }
}

/**Looks for sub-folder files and folder, if we find sub-folder according to users command we set delete_path
 * to actually opened folder path + filename he wants to delete (line 27-28) returns true on success*/
bool CDelete::ValidatePath( const CFolder &folder , string & current_m_Path ){
    if ( folder.findFolder(delete_Path) || folder.findLink(delete_Path) || folder.findFile(delete_Path) ) {
        delete_Path = folder.getPath() + delete_Path;
    }
    delete_Path = filesystem::path(delete_Path).lexically_normal();
    /**We need to check if we are not deleting curerently opened folder or some part of currently opened folder.
     * If so we set CBrowser_m_Path (this parameter is currently opened path in CBrowser) to parent_path() of our delete target*/
    if ( current_m_Path.find(delete_Path) != string::npos ) {
        if (delete_Path [delete_Path.size() - 1] == '/' )
            delete_Path [delete_Path.size() - 1] = '\0';
        current_m_Path = filesystem::path(delete_Path).parent_path().string();
    }
    return true;
}

/**Methods that are taking care of deleting path, returns true on success, ErasePath will delete path we are providing
 * in parameter, Execute will do the same but with class variable */
bool CDelete::ErasePath(const string &path){
    try {
        if ( filesystem::remove_all( path ) )
            return true;
    } catch (filesystem::filesystem_error & e){
        cout << e.what() << endl;
        return false;
    }
    return false;
}
bool CDelete::Execute()const{
    try {
        if ( filesystem::remove_all( delete_Path.c_str() ) )
            return true;
    } catch (filesystem::filesystem_error & e){
        cout << e.what() << endl;
        return false;
    }
    return false;
}
