/*
 * @author Zilinek Jakub 
 * on 11.05.20
 */
#pragma once
#include "CFolder.h"
#include "COperations.h"
#include <filesystem>
#include <string>
#include <iostream>
#include <cstdio>
#include <unistd.h>

using namespace std;

/**This class is taking care of deleting files/folder*/

class CDelete : public COperations {
protected:
    string delete_Path;
public:
    CDelete() = default;
    bool UserInput() override;
    static bool ErasePath(const string & path);
    bool Execute()const override;
    bool ValidatePath( const CFolder & folder , string & current_m_Path  )override;
};
