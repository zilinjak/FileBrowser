/*
 * @author Zilinek Jakub 
 * on 11.05.20
 */
#pragma once
#include "COperations.h"
#include "CFolder.h"
#include <algorithm>
#include <filesystem>

/**
 * CCopy is class thats gonna copy source path -> can be folder or file and will copy it to target folder
 * This class has UserInput, this class is will take 2 parameters from user, source and target paths. If either
 * is gonna be "exit" we will return false.
 */

class CCopy : public COperations{
protected:
public:
    CCopy() = default;
    bool UserInput() override;
    bool ValidatePath( const CFolder & folder , string & current_m_Path )override;
    bool Execute()const override;
    static bool MakeCopy( const string & from , const string & to );
};
