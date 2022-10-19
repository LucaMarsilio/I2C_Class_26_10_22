# PSoC I2C 26 - 10 - 22

This repository contains the projects for the I2C class with PSoC Creator for the LTEBS course.

## Instructions
Clone this repository on your local machine. You can either work directly in the master branch or create a development branch (hereafter called dev)

At the end of each task, the solution will be pushed to the branch solution.
Now, students may pull the commit(s) from the remote solution branch and:
- compare their work with the solution using git diff
- if needed, merge the solution into their work (either master or dev branch)

## Project 1
Program the PSoC as I2C slave and interact with it using the Bridge Control Panel

## Project 2a
- Program the PSoC as I2C master and connect to it the Adafruit LIS3DH 3-axis Accelerometer
- Write the interface function to read the registers of the device

## Project 2b 
- Write the interface function to write the registers of the device

## Project 3
- Using your I2C interface functions, setup and read the built-in temperature sensor, convert the raw byte data and send it over UART to the PC
