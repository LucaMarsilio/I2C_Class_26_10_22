/*
*   Source file for the logging interface.
*/


#define UART_Debug_Name(fn) UART_Debug_ ## fn
#define UART_Debug_Name_Header_File "UART_Debug.h"

// Include required libraries
#include "Logging_Interface.h"
#include "stdio.h"
#include UART_Debug_Name_Header_File

Logging_Error Logging_Interface_Start(void)
{
    UART_Debug_Name(Start)();
    
    return LOGGING_OK;
}

Logging_Error Logging_Interface_Stop(void)
{
    UART_Debug_Name(Stop)();
    
    return LOGGING_OK;
}
    

Logging_Error Logging_Interface_PutString(const char8 string[])
{
    UART_Debug_Name(PutString)(string);
    
    return LOGGING_OK;
}
    
    
Logging_Error Logging_Interface_PutArray(const uint8 string[], 
                                            uint8 byteCount)
{
    UART_Debug_Name(PutArray)(string, byteCount);
    return LOGGING_OK;
}


Logging_Error Logging_Interface_PutInt(int value) 
{
    char message[30];
    sprintf(message,"%d",value);
    return Logging_Interface_PutString(message);
}

Logging_Error Logging_Interface_PutChar(char value)
{
    UART_Debug_Name(PutChar)(value);
    return LOGGING_OK;
}

Logging_Error Logging_Interface_PutFloat(float value)
{
    char message[30];
    sprintf(message,"%f",value);
    return Logging_Interface_PutString(message);
}
/* [] END OF FILE */
