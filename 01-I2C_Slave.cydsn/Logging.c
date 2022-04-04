/*
*   This is the source code for the logging
*   driver. 
*
*   \author Davide Marzorati
*   \date September 23, 2019
*/

#include "Logging.h"
#include "stdio.h"

Logging_Error Logging_Start(void)
{
    // Start the interface
    Logging_Error error = Logging_Interface_Start();
    if ( error == LOGGING_ERROR)
    {
        return LOGGING_ERROR;
    }
    
    // Print welcome string
    error = Logging_Interface_PutString(WELCOME_STRING);
    if ( error == LOGGING_ERROR)
    {
        return LOGGING_ERROR;
    }
    
    // Print debug string
    #ifdef DEBUG_ENABLED
        error = Logging_Interface_PutString(DEBUG_ENABLED_STRING);
        if ( error == LOGGING_ERROR)
        {
            return LOGGING_ERROR;
        }
    #endif
    
    return error;
}