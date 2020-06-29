/*
 * @author Zilinek Jakub 
 * on 11.05.20
 */


#include "COperations.h"
#include <string>
#include <iostream>

using namespace std;

/*Function to shorter the code in CCopy::UserInput and CMove::UserInput*/
bool COperations::Inputs(string & source){
    getline( cin , source);
    if ( cin.eof() ) {
        return false;
    }
    return source != "exit";
}

bool COperations::Run( const CFolder & folder , string & m_Path ) {
    if ( UserInput() )
        if ( ValidatePath( folder , m_Path ) )
            return Execute();
    return false;
}
