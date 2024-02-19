/****************************************************************************
MiniSobot Library
Created By   : Rodrigo L. de Carvalho
Version      : 1.0
Company      : Solis Tecnologia

readButton.ino :
    This sketch demonstrates the use of the read_button() function to 
    read data in push_button.

    Read if the button is pressed or not:

    int read_button()

    Pressed: Retorned 1
    Not Pressed:  Retorned 0
****************************************************************************/

// Include Library code:
#include "MiniSobot.h"

// Initialize the library 
MiniSobot robot;

// The setup function runs once when you press reset or power the board
void setup(){

    // Nothing here..

}

// The loop function runs over and over again forever
void loop (){

    // When the button is pressed
    if (robot.read_button()) 
    {
        robot.led_rgb(0,255,0); // Turn on LED RGB in GREEN Color
    }

    // When the button is not pressed
    else{
        robot.led_rgb(255,0,0); // Turn on LED RGB in RED Color 
    }

}

