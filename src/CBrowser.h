/*
 * @author Zilinek Jakub 
 * on 08.05.20
 */

#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include "CFolder.h"
#include "CDelete.h"
#include "CMove.h"
#include "CCopy.h"
#include <filesystem>
#include <fstream>
using namespace std;

/** CBrowser
 * This simple class is gonna be representing File Browser. Into the constructor goes always path
 * that is check by CInterface::BrowserSetUp -> that means that we dont need to expect that if
 * we can enter wrong path to folder. This folder simply creates CFolder and prints it out,
 * also its checking if user types "exit" to leave browsing. After every successful creating and
 * printing of folder we set m_Path to folder.GetPath() . that means that we always have the right
 * folder.
 * IMPORTANT NOTE: WE CANT SET m_Path to folder.GetPath() if folder.getState() = true -> if the
 * folder.getState() equals true means that the folder could not find the right path -> that means we
 * cant set m_Path
 *
 * CBrowser is file browser thats allowing us to move in file system, delete files using delete and then typing sub-folder/file
 * name to remove them or we can type full path to file/folder. The same is working for copy. CBrowser takes input and decides
 * what command did user use and what method do we need to use now and starts it. The main while loop end by typing exit.
 * We are processing input from use every iteration of while loop. This is basically sub-UI after main-menu UI.
 *
 * CBrowser has map of operations, this map is declared like map <string , unique_ptr < COperations > > operations;
 * All operations that we can use must be child of COperations, if we add key with unique pointer to new class operations
 * to the map, we can will automatically look for that key when user is trying to call some filesystem operation.
 *  __________________________________
 * |************MAIN MENU ************|
 * |**********************************|
 *            |                  |
 *   _________|__________    ____|____
 *  |******CBrowser******|  | CRegExp |
 *
 *  __________________________________     ___________________________________
 * |************CData ****************|   |************COperations************|
 * |**********************************|   |***********************************|
 *      |           |           |               |            |          |
 *   CFile       CFolder     CSymLink        CDelete      CMove       CCopy
 */

class CBrowser{
private:
    string m_Path;
    map <string , unique_ptr < COperations > > operations;
public:
    explicit CBrowser(string & path);
    string getPath()const{ return this->m_Path; }

    /**This methods opens folder, creates CFolder and print it out*/
    void enterFolder(CFolder & folder , string input);

    /**methods to create dirs/.txt file or symLinks inside of our dir*/
    bool MakeDir()const;
    bool MakeLink(const CFolder & folder)const;
    bool MakeText( CFolder & folder );

    void InitializeOperations();
    void FolderGetSize(const CFolder & folder)const;
    void Execute( bool function , CFolder & folder );
};

