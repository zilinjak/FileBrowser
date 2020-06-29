
/*
 * @author Zilinek Jakub
 * on 14.05.2020
 */

/** This class is taking care when user wants to do operations under regular expresition */

#pragma once
#include <vector>
#include <cstring>
#include <filesystem>
#include <regex>
#include "CDelete.h"
#include "CMove.h"
#include "CCopy.h"

using namespace std;


class CRegExp {
protected:
    string m_RegExp;
    string m_Operation;
    string m_Path;

    string m_UserInput;
    string m_Target;

    vector <string> m_Result;

    bool m_Running = true;
public:
    CRegExp();
    void UserInput();
    bool ParseInput();
    bool ValidatePath();
    bool Execute();
    vector <string> getTargets();
    void Clear();

    bool setTargets();
};