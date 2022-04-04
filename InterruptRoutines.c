/**
* This file contains all the source code required
* for the interrupt service routines.
*/

// Include required header files
#include "InterruptRoutines.h" 
#include "PWM_LED.h"
#include "Timer_Count.h"

// Our global variables
extern uint8_t PWM_compare, PWM_period;
extern uint8_t slaveBuffer[];
    

CY_ISR(Custom_Timer_Count_ISR)
{
    // Read timer status register to pull interrupt line low
    Timer_Count_ReadStatusRegister();
    // Increment counter in slave buffer
    slaveBuffer[2]++;
}

/**
*   This function is called when exiting the EZI2C_ISR. Here we
*   perform all the tasks based on the requests.
*/
void EZI2C_ISR_ExitCallback(void)
{
    // Update PWM compare value if it was updated and it is lower than period value
    if ( (slaveBuffer[0] != PWM_compare) && (slaveBuffer[0] <= PWM_period) )
    {
        PWM_LED_WriteCompare(PWM_period - slaveBuffer[0]);
        PWM_compare = slaveBuffer[0];
    }
    else
    {
        slaveBuffer[0] = PWM_compare;
    }
    // Update PWM period value if it was updated and it is greater than compare value
    if ( (slaveBuffer[1] != PWM_period) && (slaveBuffer[1] >= PWM_compare) )
    {
        PWM_LED_WritePeriod(slaveBuffer[1]);
        PWM_period = slaveBuffer[1];
    }
    else
    {
        slaveBuffer[1] = PWM_period;
    }
}
/* [] END OF FILE */
