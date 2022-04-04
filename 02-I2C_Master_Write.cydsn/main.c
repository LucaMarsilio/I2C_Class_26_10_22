/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <stdio.h>
#include "project.h"
#include "../src_shared/I2C_Interface.h"
#include "../src_shared/LIS3DH.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Peripheral_Start();
    UART_1_Start();
    
    CyDelay(5); //"The boot procedure is complete about 5 ms after device power-up."
    
    // Check if LIS3DH is connected
    uint32_t rval = I2C_Master_MasterSendStart(LIS3DH_DEVICE_ADDRESS, I2C_Master_WRITE_XFER_MODE);
    if( rval == I2C_Master_MSTR_NO_ERROR ) {
        UART_1_PutString("LIS3DH found @ address 0x18\r\n");
    }
    I2C_Master_MasterSendStop();
    
    UART_1_PutString("**************\r\n");
    UART_1_PutString("** I2C Scan **\r\n");
    UART_1_PutString("**************\r\n");
    
    CyDelay(10);
    
    // String to print out messages over UART
    char message[50] = {'\0'};
    
  
	// Setup the screen and print the header
	UART_1_PutString("\n\n   ");
	for(uint8_t i = 0; i<0x10; i++)
	{
        sprintf(message, "%02X ", i);
		UART_1_PutString(message);
	}
    
    // SCAN the I2C BUS for slaves
	for( uint8_t i2caddress = 0; i2caddress < 0x80; i2caddress++ ) {
        
		if(i2caddress % 0x10 == 0 ) {
            sprintf(message, "\n%02X ", i2caddress);
		    UART_1_PutString(message);
        }
 
		rval = I2C_Master_MasterSendStart(i2caddress, I2C_Master_WRITE_XFER_MODE);
        
        if( rval == I2C_Master_MSTR_NO_ERROR ) // If you get ACK then print the address
		{
            sprintf(message, "%02X ", i2caddress);
		    UART_1_PutString(message);
		}
		else //  Otherwise print a --
		{
		    UART_1_PutString("-- ");
		}
        I2C_Master_MasterSendStop();
	}
	UART_1_PutString("\n\n");
    
    /******************************************/
    /*            I2C Reading                 */
    /******************************************/
    
    // Check the defines in LIS3DH.h for the address of the
    // registers to read
    
    /*      I2C Master Read - WHOAMI Register       */
    uint8_t whoami_reg;
    ErrorCode error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, 
                                                  LIS3DH_WHO_AM_I_REG_ADDR,
                                                  &whoami_reg);
    if( error == NO_ERROR ) {
        sprintf(message, "WHOAMI register value: 0x%02X [Expected value: 0x%02X]\r\n", whoami_reg, LIS3DH_WHOAMI_RETVAL);
        UART_1_PutString(message);
    }
    else {
        UART_1_PutString("I2C error while reading LIS3DH_WHO_AM_I_REG_ADDR\r\n");
    }
    
    
    /*      I2C Master Read - STATUS Register       */
    
    uint8_t status_reg;
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, 
                                        LIS3DH_STATUS_REG,
                                        &status_reg);
    if( error == NO_ERROR ) {
        sprintf(message, "STATUS register value: 0x%02X\r\n", status_reg);
        UART_1_PutString(message);
    }
    else {
        UART_1_PutString("I2C error while reading LIS3DH_STATUS_REG\r\n");
    }
    
    /*      I2C Master Read - CTRL Register 1       */
    
    uint8_t control_reg;
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, 
                                        LIS3DH_CTRL_REG1,
                                        &control_reg);
    if( error == NO_ERROR ) {
        sprintf(message, "CTRL register 1 value: 0x%02X\r\n", control_reg);
        UART_1_PutString(message);
    }
    else {
        UART_1_PutString("I2C error while reading LIS3DH_CTRL_REG1\r\n");
    }
    
    /******************************************/
    /*       I2C Writing CTRL REG1            */
    /******************************************/
    
    UART_1_PutString("\r\nWriting new values...\r\n");
    
    if (control_reg != LIS3DH_NORMAL_MODE_CTRL_REG1)
    {
        control_reg = LIS3DH_NORMAL_MODE_CTRL_REG1;
        
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                             LIS3DH_CTRL_REG1,
                                             control_reg);
        
        if (error == NO_ERROR)
        {
            sprintf(message, "\r\nCTRL register 1 successfully written as: 0x%02X\r\n", control_reg);
            UART_1_PutString(message);
        }
        else
        {
            UART_1_PutString("\r\nError occured during I2C comm to set control register 1\r\n");
        }
    }
    
    /******************************************/
    /*     I2C Reading CTRL REG1 again        */
    /******************************************/
    
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_CTRL_REG1,
                                        &control_reg);
    
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL register 1 after overwrite operation: 0x%02X\r\n", control_reg);
        UART_1_PutString(message);
    }
    else
    {
        UART_1_PutString("Error occured during I2C comm to read control reg1\r\n");
    }
      
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
