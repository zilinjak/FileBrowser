/*
 * @author Zilinek Jakub
 * on 08.05.20
 */

#include "CInterface.h"


/** This the the main menu */
CInterface::CInterface () {
    system("clear");
    cout << "\n\t\t\t WELCOME TO BASIC FILESYSTEM BROWSER AND EDITOR\n\n";
    while ( CInterface::MainMenuRunning ) {
        m_Input = MainMenu();
        if (m_Input == "exit") {
            CInterface::MainMenuRunning = false;
            system("clear");
        }
        ProcessInput(m_Input);
    }
}

/**This method is printing options which can user do as well as its returning input of user*/
string CInterface::MainMenu() const{
    string input;
    while ( CInterface::InterfaceRunning ) {
        cout << "\n\n\t\t***Main Menu***\n\n";
        cout << "Current path: " << m_Path << endl;
        cout << "1 - for browsing in file system. Here you can move/copy/delete files/folder\n"
                "2 - for deleting/moving/coping files using regular expressions\n";
        cout << "\n\nbrowser_reset - to reset default browsing folder\n";
        getline( cin , input);
        if ( cin.eof() )
            return "exit";
        if ( input == "2" || input == "1" || input == "browser_reset" || input == "exit" )
            return input;
        cout << "Invalid choice, try again.\n\n";
    }
    return "exit";
}

/**This method is processing input of user after he chooses in main menu what he wants to do*/
void CInterface::ProcessInput(const string & in_result) {
    if (in_result == "1") {
        if ( ! m_BrowserSetUp ) {
            string user_path = BrowserSetUp();
            if (user_path != "exit") {
                m_BrowserSetUp = true;
                m_Path = user_path;
                CBrowser browser(m_Path);
                m_Path = browser.getPath();
            }
        }
        else { //if user has already use file browser
            CBrowser browser(m_Path);
            m_Path = browser.getPath();
        }
    }
    else if (in_result == "2") {
        system("clear");
        CRegExp RegExp;
    }
    else if (in_result == "browser_reset") {
        cout << "Browser default folder was reseted !" << endl;
        m_BrowserSetUp = false;
        m_Path = "Reseted!";
    }
    else if (in_result == "exit")
        CInterface::InterfaceRunning = false;
}

/**This method is asking user where are we starting his browsing in filesystem incase he did reset it or he hasnt use it yet*/
string CInterface::BrowserSetUp() const {
    cout << "Set your starting folder: ";
    while(true){
        string user_path;
        getline( cin , user_path);
        if ( cin.eof() )
            return "exit";
        if (user_path == "exit")
            return user_path;
        if (*user_path.begin() != '/')      //need to add this otherwise we might open home sub-directory
            user_path = "/" + user_path;
        if ( filesystem::is_directory(user_path) ){         //folder that we created must be found !
            return user_path;
        }
        cout << "Try again !\n";
    }
}