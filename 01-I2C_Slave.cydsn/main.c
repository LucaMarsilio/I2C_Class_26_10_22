/**
* \brief Main source file for the I2C-Slave project.
*
* In this project we emulate a slave device with
* only 4 registers on aPSoC 5LP device to showcase the I2C 
* communication protocol using a I2C Master device (that runs
* on another PSoC 5LP). We use th EZI2C component.
*
* \author Davide Marzorati
* \date October 14, 2019
*/

#include "InterruptRoutines.h"
#include "Logging.h"
#include "project.h"

/**
* \brief Size of data buffer for I2C slave device
*/
#define SLAVE_BUFFER_SIZE 4

uint8_t slaveBuffer[SLAVE_BUFFER_SIZE]; ///< Buffer for the slave device
uint8_t PWM_period;     ///< Period of the PWM for LED blinking
uint8_t PWM_compare;    ///< Compare of the PWM for the LED blinking

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Start logging interface */
    Logging_Start();
    
    /* Start EZI2C Component */
    EZI2C_Start();
    
    /* Start timer and associated ISR */
    Timer_Count_Start();
    isr_Count_StartEx(Custom_Timer_Count_ISR);
    
    /* Start PWM Component */
    PWM_LED_Start();
    
    // Set up variables for PWM component
    PWM_compare  = PWM_LED_ReadCompare();
    PWM_period  = PWM_LED_ReadPeriod();
    
    // Set up Slave Buffer
    slaveBuffer[0] = PWM_compare;
    slaveBuffer[1] = PWM_period;
    
    // Set up who am i register
    slaveBuffer[SLAVE_BUFFER_SIZE-1] = 0xBC;
    
    // Set up EZI2C buffer
    EZI2C_SetBuffer1(SLAVE_BUFFER_SIZE, SLAVE_BUFFER_SIZE - 1 ,slaveBuffer);
    
    for(;;)
    {
        /* Place your application code here. */
    }
}



/* [] END OF FILE */
