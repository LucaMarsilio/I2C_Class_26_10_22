/**
*   \file ErrorCodes.h
*   \brief Error codes definition.
*   
*   This file contains several definition of error codes to be used throughout
*   the project to be consisted with the written firmware.
*
*   \author Davide Marzorati
*   \date September 12, 2019
*/

/**
*   \brief Error codes.
* 
*   This definition defines several error codes that will
*   be used throughout the project.
*/
#ifndef __ERRORCODES_H
    #define __ERRORCODES_H
    
    typedef enum {
        NO_ERROR,           ///< No error generated
        ERROR               ///< Error generated
    } ErrorCode;

#endif
/* [] END OF FILE */
