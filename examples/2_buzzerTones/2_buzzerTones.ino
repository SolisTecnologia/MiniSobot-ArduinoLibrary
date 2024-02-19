/****************************************************************************   
MiniSobot Library
Created By   : Rodrigo L. de Carvalho
Version      : 1.0
Company      : Solis Tecnologia

buzzerTones.ino :
    This sketch demonstrates the use of the buzzer() function to 
    generate different tones in Buzzer.

    Set the tone in BUZZER:

    buzzer(Frequency, Duration)

    Frequency: 0-255 values range
    Duration: duration of tone frequency (optional)
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

    int time = 500; // Set the time duration of notes like 500 ms
    robot.buzzer(262,time); // Dó
    robot.buzzer(294,time); // Ré
    robot.buzzer(330,time); // Mi
    robot.buzzer(349,time); // Fá
    robot.buzzer(392,time); // Sol
    robot.buzzer(440,time); // lá
    robot.buzzer(494,time); // Si
    robot.buzzer(528,time); // #Dó
    delay(1000); // Wait a second for repeat

}

