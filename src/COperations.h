/*
 * @author Zilinek Jakub 
 * on 11.05.20
 */

/** COperations in an abstract class. From this class we inherit CCopy, CDelete and CMove.
 *  We are using polymorphism for methods UserInput, ValidatePath and Execute().
 *  ValidatePath might be different for every sub class aswell.
 *  But in class CDelete we actually dont need to validate the class we simply try deleting the file and check the result of it.
 *
 *  ValidatePath is also an abstract method that is gonna be different for every implementation, because
 *  if we are deleting we will be checking for different things then for example with moving
 *
 *  Execute will provide us class operation with class variables
 */

#pragma once

#include "CFolder.h"
#include <string>


using namespace std;
class COperations {
protected:
    string m_PathFrom;
    string m_PathTo;
public:
    virtual ~COperations() = default;
    virtual bool UserInput() = 0;
    virtual bool ValidatePath( const CFolder & folder , string & current_m_Path ) = 0;
    virtual bool Execute() const = 0;
    static bool Inputs(string & source);
    bool Run( const CFolder & folder , string & m_Path );
};
