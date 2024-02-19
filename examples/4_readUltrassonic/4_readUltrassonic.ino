/****************************************************************************
MiniSobot Library
Created By   : Rodrigo L. de Carvalho
Version      : 1.0
Company      : Solis Tecnologia

readUltrassonic.ino : 
    This sketch demonstrates the use of the read_ultrassonic() function to 
    make a MiniSobot calculate distance beetween robot and obstacles.

    Read the distance calculate by sensor:

    float read_ultrassonic()

    the distance range is 2 - 400 CM.
    datas upper or bellow this, are not confiable
****************************************************************************/

//  Include Library code:
#include "MiniSobot.h"

//  Initialize the library 
MiniSobot robot;

//  The setup function runs once when you press reset or power the board
void setup(){

    //  Initialize serial communication at 9600 bits per second:
    Serial.begin(9600);    
     
}


void loop (){

    float distance = 0; //  Initialize the variable that will store distance data
    distance = robot.read_ultrasonic(); //  read the sensor data and store in the variable

    Serial.print("The Distance in CM: "); //  Print this text in terminal "The Distance in CM: "
    Serial.println(distance); //  Print out the value you read
    
    delay(1000); //  Wait a second and repeat 
}

