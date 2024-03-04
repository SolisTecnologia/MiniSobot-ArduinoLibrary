/****************************************************************************   
MiniSobot Library
Created By   : Rodrigo L. de Carvalho
Version      : 1.1
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
    robot.buzzer(262,time); // C (Dó)
    robot.buzzer(294,time); // D (Ré)
    robot.buzzer(330,time); // E (Mi)
    robot.buzzer(349,time); // F (Fá)
    robot.buzzer(392,time); // G (Sol)
    robot.buzzer(440,time); // A (lá)
    robot.buzzer(494,time); // B (Si)
    robot.buzzer(528,time); // C# (Dó#)
    delay(1000); // Wait a second for repeat

}

