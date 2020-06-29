/*
 * @author Zilinek Jakub 
 * on 08.05.20
 */

/**
 * CInterface is basically switch, at the beginning we print our main title, after that we only type our menu.
 * Constructor creates while loop, this loop is gonna be going till user types "exit" , and if he types exit its gonna
 * end the program.
 *      MainMenu, represent Interface of main menu, in here user chooses what he wants to do. MainMenu() returns string of users input.
 *      Then There is ProcessInput -> this is gonna take the input of user as parameter and process it. This is the switch. For example
 * if he wants to browser files we firstly run BrowserSetUp -> this method is gonna set default path of users Browsing aka where
 * are we gonna start. If it wasnt done successfully we cant open CBrowser ! This means that CBrowser is always gonna have an
 * right path to folder. We dont have to check it anymore. After that we are only creating CBrowser, the while loop for searching in
 * file system is already inside of CBrowser so thats it. After every ended browsing we are taking the last path we visited
 * in case user wants to use it with some other function - move, delete, copy.
 */

#pragma once
#include <string>
#include "CBrowser.h"
#include "CRegExp.h"


using namespace std;

class CInterface{
private:
    string m_Input;
    string m_Path = "None";
    bool m_BrowserSetUp = false; //represent if user has already done Setting up his default folder
    bool InterfaceRunning = true;
    bool MainMenuRunning = true;
public:
    CInterface ();
    string MainMenu()const;
    void ProcessInput(const string & result);
    string BrowserSetUp()const;
};

