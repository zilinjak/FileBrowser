/*
 * @author Zilinek Jakub 
 * on 11.05.20
 */


#include "CCopy.h"

/**Takes input from user*/
bool CCopy::UserInput() {
    cout << "Type source of copying: ";
    if ( Inputs(m_PathFrom) ){   //Inputs returns 0 if input is "exit"
        cout << "Type path to folder where we are moving: ";
        return Inputs(m_PathTo);
    } else
        return false;
}

/**Validating paths, we are also looking for targets in our currently opened folder. */
bool CCopy::ValidatePath( const CFolder & folder , string & current_m_Path ) {
    /*Setting up PathTo and checking if is directory*/
    if ( folder.findFolder(m_PathTo) ) /**Trying to find sub-folder */
        m_PathTo = folder.getPath() + m_PathTo;
    m_PathTo = filesystem::path(m_PathTo).lexically_normal();

    /*setting up PathFrom*/
    if ( folder.findFile(m_PathFrom) || folder.findFolder(m_PathFrom) || folder.findLink(m_PathFrom) )
        m_PathFrom = folder.getPath() + m_PathFrom; /*Trying to find sub-folder file/folder/symlink*/
    m_PathFrom = filesystem::path(m_PathFrom).lexically_normal();

    /*checking if we are not copying from subfolder to folder
       example: copy from /home/progtest/ to /home/protest/test ->
       -> this would never end cuz of filesystem::copy_options::recursive */
    if (m_PathTo.find(m_PathFrom) == string::npos)
        return true;
    else {
        cout << "We are sorry but you cant copy this folder to sub-folder. The program would cycle forever.\n" << endl;
        cout << "You tried to copy - \"" << m_PathFrom << "\" into - \"" << m_PathTo << "\"\n";
        return false;
    }
}

/**After we are sure that the paths are fine to use, we can try to execute them with following methods,
 * Execute is providing us the operations to this class variables we did specify before, MakeCopy with parameters will
 * do this operations to these parameters not to the class variables*/
bool CCopy::Execute() const{
    if ( ! filesystem::is_symlink(m_PathFrom) ) {
        try {
            filesystem::copy(m_PathFrom, m_PathTo,
                             filesystem::copy_options::copy_symlinks |
                             filesystem::copy_options::recursive |
                             filesystem::copy_options::overwrite_existing);
        } catch (filesystem::filesystem_error &e) {
            cout << e.what() << endl;
            return false;
        }
        return true;
    } else {
        system( string("cp -P " + m_PathFrom + " " + m_PathTo ).c_str() );
        return true;
    }
}
bool CCopy::MakeCopy(const string &from, const string &to) {
    if ( ! filesystem::is_symlink(from) ) {
        try {
            filesystem::copy(from, to,
                             filesystem::copy_options::copy_symlinks |
                             filesystem::copy_options::recursive |
                             filesystem::copy_options::overwrite_existing);
        } catch (filesystem::filesystem_error &e) {
            cout << e.what() << endl;
            return false;
        }
        return true;
    } else {
        system( string("cp -P " + from + " " + to ).c_str() );
        return true;
    }
}
