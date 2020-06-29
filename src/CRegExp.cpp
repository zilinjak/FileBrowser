/*
 * @author Zilinek Jakub
 * on 14.05.20
 */

#include "CRegExp.h"

/**Basic while loop for RegExp menu*/
CRegExp::CRegExp() {
    while( m_Running ) {
        Clear();
        UserInput();
        if (m_UserInput != "exit") {
            if (ParseInput()) {
                if (m_Operation != "delete") {
                    cout << "Target path: ";
                    getline(cin, m_Target);
                    if ( cin.eof() ) {
                        break;
                    }
                }
                if (ValidatePath())
                    if (setTargets()) {
                        if (Execute())
                            cout << "Success.\n";
                    }
            }
        }
        else
            system("clear");
    }
}

/**This methods gets an input from user*/
void CRegExp::UserInput() {
    string input;
    cout << "Type your regular expression: ";
    getline(cin,input);
    if ( cin.eof() ) {
        input = "exit";
    }
    if ( input == "exit" )
            m_Running = false;
    m_UserInput = input;
}

/**We are parsing input from user with sscanf */
bool CRegExp::ParseInput() {
    char *operation = new char[m_UserInput.size()];
    char *path = new char[m_UserInput.size()];
    char *reg = new char [m_UserInput.size()];

    if ( sscanf(m_UserInput.c_str(), "%s %s %s", operation, path , reg ) != 3){
        cout << "Missing an argument.\n";
        delete[] path;
        delete[] operation;
        delete[] reg;
        return false;
    }
    m_Path = path;
    m_Operation = operation;
    m_RegExp = reg;

    delete[] path;
    delete[] operation;
    delete[] reg;
    return true;
}

/** We need to check if the paths user typed are valid */
bool CRegExp::ValidatePath() {

    m_Path = filesystem::path(m_Path).lexically_normal();
    m_Target = filesystem::path(m_Target).lexically_normal();
    if ( m_Path.back() != '/')
        m_Path = m_Path + "/";
    if (m_Path.front() != '/')
        m_Path = "/" + m_Path;


    if ( m_Target.back() != '/')
        m_Target = m_Target + "/";
    if (m_Target.front() != '/')
        m_Target = "/" + m_Target;


    if ( ! filesystem::is_directory(m_Path) ){
        cout << "\n\n\t\tInvalid path.\n\n";
        return false;
    }
    if ( ! m_Target.empty() && !filesystem::is_directory(m_Target) ){
        cout << "\n\n\t\tInvalid path.\n\n";
        return false;
    } else
        return true;
}

/**retunts us vector of strings. these strings represents all file names of core path user wants to use
 *
 * Example of command - delete /home/progtest/ .*
 * this vector will contain all file/folder names of /home/progtest/ *these names* /
 * */
vector <string> CRegExp::getTargets() {
    vector<string> targets;
    for(auto& p: filesystem::directory_iterator(m_Path) )
        targets.emplace_back( p.path().filename() );
    return targets;
}

/** takes all core file/folder names and filter them with regex */
bool CRegExp::setTargets() {
    vector <string> folder = getTargets(); //taking all file/folder names from core path
    try {
        regex reg(m_RegExp.c_str() , regex::icase ); //filtering them with regex, if we find match we will add it to m_Result vector
        for (const auto& x: folder) {
            if (std::regex_match(x , reg ) )
                m_Result.emplace_back(x);
        }
    } catch (regex_error& e) {
        cout << e.what() << endl;
        return false;
    }
    if ( m_Result.empty() ) {
        cout << "Without an result.\n\n";
        return false;
    }
    return true;
}

/**Method that clears all class variables*/
void CRegExp::Clear(){
    m_Result.clear();
}

/**Method that executes command of users choice, we execute it to every file in our m_Result vector*/
bool CRegExp::Execute() {
    if (m_Operation == "delete") {
        for (const auto &name: m_Result) { //-> for every filename in this vector
            if ( ! CDelete::ErasePath( string(m_Path + name) ) ) { //need to add m_Path -> core_path
                cout << "Unable to delete " << "\"" << string(m_Path + name).c_str() << "\""<< endl;
                return false;
            }
            cout << "Deleting: \"" << string(m_Path + name).c_str() << "\"" << endl;
        }
        return true;
    }
    else if (m_Operation == "move"){
        for (const auto &name: m_Result) {
            if ( ! CMove::MakeMove( (m_Path + name) , (m_Target + name) ) ) { //need to add m_Path -> core_path
                cout << "Unable to move " << "\"" << string(m_Path + name).c_str() << "\""<< endl;
                return false;
            }
            cout << "Moving: \"" << (m_Path + name) << "\" into \"" << (m_Target + name) << "\"" << endl;
        }
        return true;
    }
    else if (m_Operation == "copy"){
        for (const auto &name: m_Result) {
            if ( m_Target.find(m_Path) != string::npos ) { //checkig for subfolder - more on CCopy header and implementation comments
                cout << "Invalid copy.\n";
                return false;
            }
            if ( ! CCopy::MakeCopy( (m_Path+name) , (m_Target + name) ) ){ //need to add m_Path -> core_path
                cout << "Unable to copy " << "\"" << string(m_Path + name).c_str() << "\"" << endl;
                return false;
            }
            cout << "Copying: \"" << (m_Path + name) << "\" into \"" << (m_Target + name) << "\"" << endl;
        }
        Clear();
        return true;
    } else {
        Clear();
        return false;
    }
}
