/****************************************************************************
   
MiniSobot Library - MiniSobot.h
MiniSobot Library
Created By   : Rodrigo L. de Carvalho
Version      : 1.1
Company: Solis Tecnologia

****************************************************************************/

#ifndef MINISOBOT_H
#define MINISOBOT_H

#include "Arduino.h"

class MiniSobot
{
  public:
    // Constructor. Mainly sets up pins.
    MiniSobot(int led_blue_pin = 3, int led_red_pin = 5, int led_green_pin = 6,
    int motor1_in1_pin = 7, int motor1_in2_pin = 8, int motor1_pwm_pin = 9, int buzzer_pin = 10,
    int motor2_pwm_pin = 11,int motor2_in1_pin = 12,int motor2_in2_pin = 13,int foto_e2_pin = 14,
    int foto_e1_pin = 15, int sonar_echo_pin = 16, int sonar_trigger_pin = 17, int button_pin = 18);      

   // Turn Led RGB on in different colors. The colors are set by parameters
   // RED, GREEN BLUE with range 0 at 255 and have optional parameter to turn led off
    void led_rgb (int R, int G, int B,  int disable = 0);

    // Play a note in buzzer, frequency and duration are defined by parameters.
    // If not set duration, the buzzer play forever. use the stop_buzzer() function if you want to stop manually
    void buzzer (int frequency = 262, int duration = 0);

    // Stop Buzzer manually
    void stop_buzzer ();

    // Read data from  push-button, are returned a int data. 
    // The button has a pull_up, then when the button are 
    // pressed the values returned is 1
    int read_button();

    // Read data from sensor ultrasonic, are returned a float data.   
    // The distance are measured in Centimeter(CM)
    // Datas below 2 cm and upper 400 cm not are confiables
    float read_ultrasonic();

    // Read data from sensor photoelectric, defined which sensor with parameter "Sensor"
    // 1 - Sensor Left or 2 - Sensor Right, are returned a float data.   
    int read_line(int sensor);

    // Drive in forward, at speed defined by parameter
    // The range of values go 0 to 255, but values below 100 not are recommended
    void drive_forward(int speed = 150);

    // Drive in backward, at speed defined by parameter
    // The range of values go 0 to 255, but values below 100 not are recommended
    void drive_backward(int speed = 150);

    // Stops motors by setting both input pins high
    void drive_break();

    // Make a turn to the RIGHT, in the same axis, speed is defined by parameter
    // The range of values go 0 to 255, but values below 100 not are recommended
    void drive_curve_right(int speed = 150);

    // Make a turn to the LEFT, in the same axis, speed is defined by parameter
    // The range of values go 0 to 255, but values below 100 not are recommended
    void drive_curve_left(int speed = 150);

    // Make a turn to the RIGHT, use differential drive, speed is defined by parameter
    // Also have "percent" parameter this defined a speed percent referent a motor1
    // Eg: drive_curve_differential_right(255, 50)  ->  Motor1 Speed: 255 | Motor2 Speed: 255*50% = 127
    void drive_curve_differential_right(int speed = 150,  int percent = 70);

    // Make a turn to the LEFT, use differential drive, speed is defined by parameter
    // Also have "percent" parameter this defined a speed percent referent a motor2
    // Eg: drive_curve_differential_left(255, 50)  ->  Motor2 Speed: 255 | Motor1 Speed: 255*50% = 127
    void drive_curve_differential_left(int speed = 150,  int percent = 70);


    private:
    // Variables for the all pins connected in MiniSobot
    int led_blue, led_red, led_green, motor2_in1, motor2_in2, motor2_pwm, _buzzer, motor1_in1, motor1_in2, motor1_pwm, foto_e2, foto_e1, sonar_echo, sonar_trigger, button, gain_left, gain_right;
	
    // Private functions that spin the motors in CC 
    void fwd_motor1(int speed);
    void fwd_motor2(int speed);

	  // Private functions that spin the motors in CCW
    void bwd_motor1(int speed);
    void bwd_motor2(int speed);

};


#endif