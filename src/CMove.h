/*
 * @author Zilinek Jakub 
 * on 11.05.20
 */


#pragma once
#include "COperations.h"
#include "CFolder.h"
#include <filesystem>
#include <algorithm>

/**
 * CMove is class that gonna move file/folder from path_from to path_to.
 * We have UserInput thats gonna determinate the users paths we will operate with. Then method Execute will move
 * files from one path to the other one.
 * ValidatePath will check paths if they are correct
 * If either of 2 parameters that we take from user in UserInputs is gonna be "exit" we return false
 */

class CMove : public COperations {
protected:
public:
    CMove() = default;
    bool UserInput() override;
    bool Execute()const override;
    static bool MakeMove(const string & from , const string & to);
    bool ValidatePath( const CFolder & folder , string & current_m_Path )override;
};
