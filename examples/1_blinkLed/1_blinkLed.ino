/****************************************************************************   
MiniSobot Library

Created By   : Rodrigo L. de Carvalho
Version      : 1.0
Company      : Solis Tecnologia

blinkLed.ino :

    This sketch demonstrates the use of the led_rgb() function to 
    turn Led RGB on in different colors.

    Set the colors LED RGB:

    Led_rgb(RED, GREEN, BLUE, DISABLE_LED)

    RED, GREEN and BLUE: 0-255 values range
    DISABLE_LED: 1 disable | 0 enable

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

    robot.led_rgb(255,0,0); // Color is red 
    delay(1000); // wait for a second


    robot.led_rgb(0,255,0); // Color is green
    delay(1000); // wait for a second


    robot.led_rgb(0,0,255); // Color is blue
    delay(1000); // wait for a second

}

