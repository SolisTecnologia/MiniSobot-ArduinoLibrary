/****************************************************************************
MiniSobot Library
Created By   : Rodrigo L. de Carvalho
Version      : 1.1
Company      : Solis Tecnologia

followLine.ino :
    This sketch demonstrates the use of the read_line() function to 
    make a MiniSobot follow line and turn curves.

    Read if the sensor is under floor or line:

    read_line(sensor)
    Need indicate what sensor is:
    1 - Sensor Left or 2 - Sensor Right, is returned a float data.   

    If follow line: 0 | If in floor: 1
****************************************************************************/

// Include Library code:
#include "MiniSobot.h"

// Initialize the library 
MiniSobot robot;

int flag_sensor_line_right = 2; // Flag to change direction just one time 
int flag_sensor_line_left = 2; // Flag to change direction just one time 
int right, left; // Variables to store data sensor  


// The setup function runs once when you press reset or power the board
void setup(){

    // Nothing here..

}

void loop (){

    // Read the two sensors and store in respective variable your data 
    right = robot.read_line(1);
    left = robot.read_line(2);

    // When the current data is different at past data, is needed change the direction
    if ((flag_sensor_line_left != left)||(flag_sensor_line_right != right)){
        
        // When right sensor and left sensor are detecting the line, the robot moves forward  
        if (right == 0 && left == 0){
            robot.drive_forward(150);  // Moves robot forward    
            }

        // When right sensor is not detecting and left sensor 
        // is detecting the line, the robot makes the differential curve to the right  
        else if (right == 1 && left == 0){
            robot.drive_curve_differential_right(150, 30); // Make a turn to the RIGHT using differential drive
        }

        // When right sensor is detecting and left sensor 
        // is not detecting the line, the robot makes the differential curve to the left
        else if (right == 0 && left == 1){
            robot.drive_curve_differential_left(150, 30); // Make a turn to the LEFT using differential drive
        }

        // Store the last sensor data in the flag
        flag_sensor_line_right = right;
        flag_sensor_line_left = left;
    }
}