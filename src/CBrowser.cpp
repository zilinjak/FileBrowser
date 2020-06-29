/*
 * @author Zilinek Jakub 
 * on 08.05.20
 */

#include "CBrowser.h"

CBrowser::CBrowser( string & path ){

    InitializeOperations();
    m_Path = path;
    string input;
    CFolder folder (m_Path); // creating folder with path in parameter
    folder.printAll();
    while(true){ //loop that ends when user types "exit" -> until then its going through all folders user wants to see
        cout << "\nCurrent path: " << m_Path << endl;
        cout << "Type command: ";
        getline( cin , input);
        if ( cin.eof() ) {
            cout << "Invalid Input.\n";
            break;
        }
        if (input == "exit"){
            system("clear");
            folder.ClearMemory();
            break;
        }
        else if ( operations.find(input) != operations.end() ) {
            bool result = operations.at(input)->Run(folder, m_Path);
            Execute(result, folder);
        }
        else if (input == "mkdir")
            Execute ( MakeDir() , folder );
        else if (input == "makelink")
            Execute (MakeLink(folder) , folder);
        else if (input == "maketxt")
            MakeText(folder);
        else if (input == "size") {
            cout << endl;
            FolderGetSize(folder);
        }
        else {
            enterFolder(folder, input);
        }
    }
}

/**This method is getting an bool from operation what we are trying to execute. If we execute function with with success we will update folder*/
void CBrowser::Execute( bool function , CFolder & folder) {
    if (function) {
        folder.UpdateFolder(folder, m_Path);
        folder.printAll();
        cout << "\nSuccess!" << endl;
    } else {
        cout << "\n\tSomething went wrong.\n";
    }
}

/**This method is creating folder and printing it out. We are also taking care of some inputs from user.
 * So if user decides to browse in file system this method is always gonna create CFolder of his path.
 * And Its gonna print it out. Also at the end set m_Path to right one after entering/leaving current folder/path
 * and leaving CFolder folder as it should be so we can search in it later
 */
void CBrowser::enterFolder(CFolder & folder , string input)  {
    string current_path = folder.getPath();
    if (input == ".."){
        if ( current_path[current_path.size() - 1 ] == '/')
            current_path.pop_back(); //for parent_path() we need to remove the last / we are creating with CFolder !
        input = filesystem::path( current_path ).parent_path().string(); //setting input into this is nice for us so we dont find it on with std::find
    }
    if (input == "."){
        input = folder.getPath();
    }
    if ( folder.findFolder(input) ) { //if we find subfolder we will set path to current path + sub-folder name
        input = current_path + input;
    }

    input = filesystem::path(input).lexically_normal();

    if ( ! filesystem::is_directory(input) || filesystem::is_symlink(input) ) {
        cout << "Ouch, We couldn't find your folder.\n\n";
    }
    else{
        folder.ClearMemory();
        folder = CFolder ( input );
        folder.printAll();
        m_Path = folder.getPath();
    }
}

/**Method that is creating directory, returns false if not success*/
bool CBrowser::MakeDir() const{
    string input;
    cout << "Whats gonna be name of your folder: ";
    getline( cin , input);
    if ( cin.eof() ) {
        return false;
    }
    if (input != "exit") {
        input = m_Path + input;
        try {
            if ( ! filesystem::create_directories( input.c_str() ) )
                return false;
        } catch (filesystem::filesystem_error & e){
            cout << e.what() << endl;
            return false;
        }
        return true;
    } else
        return false;
}

/**Allows us to make an system link to folder/file. Allowing us to create it from and to currently opened folder. We are
 ** also able to create path from "." or "..", returns false if not success */
bool CBrowser::MakeLink(const CFolder & folder) const {
    string path_target;
    string name;
    cout << "Path to target: ";
    getline( cin , path_target);
    if ( cin.eof() ) {
        return false;
    }
    if (path_target == ".")
        path_target = m_Path;
    else if (path_target == "..") {
        path_target = m_Path;
        path_target.pop_back();
        path_target = filesystem::path(path_target).parent_path().string() + string("/");
    }
    else if ( folder.findFolder(path_target) || folder.findFile(path_target) )
        path_target = m_Path + path_target;

    if (path_target != "exit"){
        cout << "Path to new system link: ";
        getline( cin , name);
        if ( cin.eof() ) {
            return false;
        }
        if (*name.begin() != '/')
            name = m_Path + name;
        if ( filesystem::is_directory(path_target) ) {
            try {
                filesystem::create_directory_symlink(path_target, name);
            } catch (filesystem::filesystem_error &e) {
                cout << e.what() << endl;
                return false;
            }
            return true;
        }
        else {
            try {
                filesystem::create_symlink(path_target, name);
            } catch (filesystem::filesystem_error &e) {
                cout << e.what() << endl;
                return false;
            }
            return true;
        }
    } else
        return false;
}

/**Method that will trigger folder.getSize(),
 * this is an recursive call thats returning an size of currently opened dir and will print result to console*/
void CBrowser::FolderGetSize(const CFolder & folder)const{
    uintmax_t result = folder.getSize();
    if (result < 1024)
        cout << "Currently opened folder has " << fixed << setprecision(2) << result << " B size.\n";
    else if (result < 1024 * 1024)
        cout << "Currently opened folder has " << fixed << setprecision(2) << result / 1024 << " KB size.\n";
    else if (result < 1024 * 1024 * 1024)
        cout << "Currently opened folder has " << fixed << setprecision(2) << result / (1024 * 1024)
             << " MB size.\n";
    else
        cout << "Currently opened folder has " << fixed << setprecision(2) << result / (1024 * 1024 * 1024)
             << " GB size.\n";
}

/**Method that is creating txt file or reads and print it to console if the same named file is already created with size > 0,
   returns false if not success  */
bool CBrowser::MakeText(CFolder & folder) {
    string name;
    cout << "File name : ";
    getline( cin , name);
    if ( cin.eof() ) {
        return false;
    }
    if (name != "exit") {
        if (folder.findFile(name) && filesystem::file_size(m_Path + name) > 0) {
            cout << "\n\tFile with this name already exists with following content: \n";
            cout << ifstream(m_Path + name).rdbuf() << endl;
            return true;
        } else {
            ofstream created(m_Path + name);
            system("clear");
            cout << "Type content of your file,\n\t end typing with 'new line' and  *end*.\n";
            string tmp;
            while ( getline(cin, tmp) ) {
                if ( tmp == "*end*" ) {
                    created.close();
                    folder.UpdateFolder(folder , m_Path);
                    cout << folder << endl;
                    cout << "Success" << endl;
                    return true;
                }
                created << tmp << endl;
                tmp.clear();
            }
            return false;
        }
    } else
        return false;
}

void CBrowser::InitializeOperations() {
    operations["delete"] = make_unique<CDelete>();
    operations["move"] = make_unique<CMove>();
    operations["copy"] = make_unique<CCopy>();
}
