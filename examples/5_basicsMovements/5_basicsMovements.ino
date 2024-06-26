/****************************************************************************
MiniSobot Library
Created By   : Rodrigo L. de Carvalho
Version      : 1.2
Company      : Solis Tecnologia

basicsMovements.ino :
    This sketch demonstrates the use of the all fuction to drive MiniSobot.
    drive_forward(speed)
    drive_backward(speed)
    drive_curve_left(speed)
    drive_curve_right(speed)
    drive_curve_differential_left(speed, percent)
    drive_curve_differential_right(speed, percent)
    drive_break()

    All speed parameters has a default 150 value. 
    and use drive_break() function whenever changing the direction of the motor
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

    robot.drive_forward(150); // Forward
    delay(2000); // Wait a two seconds
    robot.drive_break(); // Stop the motors
    delay(2000); // Wait a two seconds

    robot.drive_backward(150); // Backward
    delay(2000); // Wait a two seconds
    robot.drive_break(); // Stop the motors
    delay(2000); // Wait a two seconds

    robot.drive_curve_left(150); // Left Curve  
    delay(2000); // Wait a two seconds
    robot.drive_break(); // Stop the motors
    delay(2000); // Wait a two seconds

    robot.drive_curve_right(150); // Right Curve
    delay(2000); // Wait a two seconds 
    robot.drive_break(); // Stop the motors
    delay(2000); // Wait a two seconds

    robot.drive_curve_differential_left(150, 60); // Differential left curve
    delay(2000); // Wait a two seconds
    robot.drive_break(); // Stop the motors
    delay(2000); // Wait a two seconds

    robot.drive_curve_differential_right(150, 60); // Differential right curve
    delay(2000); // Wait a two seconds
    robot.drive_break(); // Stop the motors
    delay(2000); // Wait a two seconds and repeat

}