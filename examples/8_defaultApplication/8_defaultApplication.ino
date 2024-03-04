/****************************************************************************
MiniSobot Library
Created By   : Rodrigo L. de Carvalho
Version      : 1.1
Company      : Solis Tecnologia

defaultApplication.ino :
    This sketch demonstrates default application, this demonstre all all functionalities of robot.

    It is separated into 3 modes:

    1 - Safe Car Mode: Moves the car forward, if it detects an obstacle, turn around.
    2 - Follow Line Mode: Follow the Line and Make a Turn if necessary.
    3 - Fun Mode:  Play a melody while turn in the same axis to right nd stop if you detect an obstacle.

    Use the button to change modes.
****************************************************************************/

// Include Library code:
#include "MiniSobot.h"

// Initialize the library 
MiniSobot robot;

// Define frequency notes
#define NOTE_E4  330
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_D5  587
#define NOTE_C5  523
#define NOTE_E5  659
#define NOTE_F5  698
#define REST      0

// Set music speed 
int time_music = 70;

// Set a melody of music
int melody[] = {

  // Asa branca - Luiz Gonzaga
  // https:// github.com/robsoncouto/arduino-songs/tree/master

  NOTE_G4,8, NOTE_A4,8, NOTE_B4,4, NOTE_D5,4, NOTE_D5,4, NOTE_B4,4, 
  NOTE_C5,4, NOTE_C5,2, NOTE_G4,8, NOTE_A4,8,
  NOTE_B4,4, NOTE_D5,4, NOTE_D5,4, NOTE_C5,4,

  NOTE_B4,2, REST,8, NOTE_G4,8, NOTE_G4,8, NOTE_A4,8,
  NOTE_B4,4, NOTE_D5,4, REST,8, NOTE_D5,8, NOTE_C5,8, NOTE_B4,8,
  NOTE_G4,4, NOTE_C5,4, REST,8, NOTE_C5,8, NOTE_B4,8, NOTE_A4,8,

  NOTE_A4,4, NOTE_B4,4, REST,8, NOTE_B4,8, NOTE_A4,8, NOTE_G4,8,
  NOTE_G4,2, REST,8, NOTE_G4,8, NOTE_G4,8, NOTE_A4,8,
  NOTE_B4,4, NOTE_D5,4, REST,8, NOTE_D5,8, NOTE_C5,8, NOTE_B4,8,

  NOTE_G4,4, NOTE_C5,4, REST,8, NOTE_C5,8, NOTE_B4,8, NOTE_A4,8,
  NOTE_A4,4, NOTE_B4,4, REST,8, NOTE_B4,8, NOTE_A4,8, NOTE_G4,8,
  NOTE_G4,4, NOTE_F5,8, NOTE_D5,8, NOTE_E5,8, NOTE_C5,8, NOTE_D5,8, NOTE_B4,8,

  NOTE_C5,8, NOTE_A4,8, NOTE_B4,8, NOTE_G4,8, NOTE_A4,8, NOTE_G4,8, NOTE_E4,8, NOTE_G4,8,
  NOTE_G4,4, NOTE_F5,8, NOTE_D5,8, NOTE_E5,8, NOTE_C5,8, NOTE_D5,8, NOTE_B4,8,
  NOTE_C5,8, NOTE_A4,8, NOTE_B4,8, NOTE_G4,8, NOTE_A4,8, NOTE_G4,8, NOTE_E4,8, NOTE_G4,8,
  NOTE_G4,-2, REST,4
  
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// There are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 2) / time_music;

int divider = 0, noteDuration = 0;


int mode = 0; // Variable to mode store

float distance = 0; // Variable to distance store
#define STOP_DISTANCE 15 // Define stop distance
#define REDUCE_SPEED_DISTANCE 30 // Define reduce speed distance

int flag_safe_direction = 0; // Flag to cahnge the safe moves 
int flag_change_direction = 0; // Flag to change direction moves

int flag_sensor_line_left = 2; // Flag to change direction just one time 
int flag_sensor_line_right = 2; // Flag to change direction just one time 
int right, left; // Variables to store data sensor  

int flag_color_led = 0; // Variables to switch led color

// Modes declaration 
void intro();
void mode_safe_car();
void mode_follow_line();
void mode_fun();

// The setup function runs once when you press reset or power the board
void setup(){
    
    intro(); // Introduction, just changes some tones and colors of the LED

}

// The setup function runs once when you press reset or power the board
void loop (){

    // When button is pressed
    if (robot.read_button() == 1){

        mode++; // Switch mode 

        // When the mode variable is greater than 4
        if (mode >= 4) {
            mode = 0; // erase modes
            robot.led_rgb(255,255,255); // Turn LED WHITE on 
        }

        robot.drive_break();  // Stop the motors
        robot.buzzer(262,600); // Play a small beep

        while (robot.read_button() == 1); // While the button is pressed, it holds the programming
    }


    // Switch the modes
    if (mode == 1){
        mode_safe_car();
    }

    else if(mode == 2){
        mode_follow_line();
    }
    else if(mode == 3){
        mode_fun();
    }

}

// Introduction
void intro (){
    
    robot.read_ultrasonic(); // Initialize the ultrasonic sensor

    robot.led_rgb(255,0,0); // Turn LED RED on 
    robot.buzzer(262,500); // C (Dó) 

    robot.led_rgb(0,255,0); // Turn LED GREEN on 
    robot.buzzer(294,500); // D (Ré) 

    robot.led_rgb(0,0,255); // Turn LED BLUE on 
    robot.buzzer(330,500); // E (Mi)
   
    robot.led_rgb(255,255,255); // Turn LED WHITE on 
    robot.buzzer(392,500); // F (Fá)
}

// Safe Car Mode
void mode_safe_car(){
    
    robot.led_rgb(0,255,0); // Turn LED GREEN on 
    distance = robot.read_ultrasonic(); // Read the sensor data and store in the variable
    

    if (distance <= 5) distance = 0; // When distance is less than 5 cm, erase distance
    if (distance >= 200) distance = 200; // When distance is more than 200 cm, define like 200 cm

    // When the Minibot approaches an obstacle, it reduces its speed
    if ((distance <= REDUCE_SPEED_DISTANCE) &&( distance > STOP_DISTANCE)) {
            robot.drive_forward(100); // Moves Forward
            flag_safe_direction = 1; // Set the flag True     
    }

    // When the Minibot is too  close an obstacle, it stop 
    else if (distance <= STOP_DISTANCE) {
      
        robot.drive_break(); // Stop the motors
        delay(200); // Wait a two hundred milli seconds;
        
        // When flag is 2, change the direction move and reset the flag
        if(flag_change_direction == 2){
          robot.drive_curve_right(255);   // Make a turn to the right 
          delay(500); // Wait a half second
          flag_change_direction = 0; // Set the flag False
        }
      
        else{
          flag_change_direction++; // Increment the flag
          robot.drive_curve_left(255); // Make a turn to the left
          delay(500); // Wait a half second
        }

        flag_safe_direction = 0; // Set the flag False
        
    }
    else {
        if (flag_safe_direction == 0){

            robot.drive_break(); // Stop the motors
            delay(500);
            flag_safe_direction = 1; // Set the flag True
        }
            robot.drive_forward(200);  // Moves Forward
    }
    delay(100); // Wait a 100 ms

    if(robot.read_button())return; // If button is pressed, exit the mode

}

// Follow Line Mode
void mode_follow_line (void){

    // Read the two sensors and store in respective variable your data 
    right = robot.read_line(1);
    left = robot.read_line(2);

    // When the current data is different at past data, is needed change the direction
    if ((flag_sensor_line_left != left)||(flag_sensor_line_right != right)){
        
        robot.led_rgb(0,0,255); // Turn on led Blue

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

    if(robot.read_button())return; // If button is pressed, exit the mode
    
}

// Fun Mode
void mode_fun (void){

    robot.drive_curve_differential_right(150,60); // Make a turn to the LEFT using differential drive
    
    // iterate over the notes of the melody.
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
        
        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {   
            noteDuration = (wholenote) / divider; // regular note, just proceed
        }
        else if (divider < 0) {
            
            noteDuration = (wholenote) / abs(divider); // dotted notes are represented with negative durations!!
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        flag_color_led ++; // Increment the flag for switch color leds

        if (flag_color_led == 1) robot.led_rgb(255,0,0); // Turn LED RED on
        else if (flag_color_led == 2) robot.led_rgb(255,255,0); // Turn LED YELLOW  on
        else if (flag_color_led == 3) robot.led_rgb(0,255,0); // Turn LED GREE on
        else if (flag_color_led == 4) robot.led_rgb(175,255,150); // Turn LED WHITE on
        else if (flag_color_led == 5) robot.led_rgb(0,255,255); // Turn LED CYAN on
        else if (flag_color_led == 6) robot.led_rgb(0,0,255); // Turn LED BLUE on
        else if (flag_color_led == 7) robot.led_rgb(255,0,255); // Turn LED PURPLE on
        else {
            robot.led_rgb(255,255,255); // Turn LED WHITE on
            flag_color_led = 0; // Erase the flag
        }

        robot.buzzer(melody[thisNote],noteDuration); // play a note with the melody duration 
        
        if(robot.read_button())return; // If button is pressed, exit the mode

        distance = robot.read_ultrasonic(); // Read the sensor data and store in the variable
        if (distance <= 5) distance = 0; // When distance is less than 5 cm, erase distance
        if (distance >= 200) distance = 200; // When distance is more than 200 cm, define like 200 cm

        // When the Minibot is too  close an obstacle, it stop 
        if (distance < STOP_DISTANCE) robot.drive_break(); // Stop the motors
        else robot.drive_curve_differential_right(150,60); // Make a turn to the RIGHT using differential drive
    }
}