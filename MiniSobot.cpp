/****************************************************************************
   
MiniSobot Library - MiniSobot.C
MiniSobot Library
Created By   : Rodrigo L. de Carvalho
Version      : 1.1
Company: Solis Tecnologia

****************************************************************************/
#include "Arduino.h"
#include "MiniSobot.h"

MiniSobot::MiniSobot(int led_blue_pin = 3, int led_red_pin = 5, int led_green_pin = 6,
    int motor1_in1_pin = 7, int motor1_in2_pin = 8, int motor1_pwm_pin = 9, int buzzer_pin = 10,
    int motor2_pwm_pin = 11,int motor2_in1_pin = 12,int motor2_in2_pin = 13,int foto_e2_pin = 14,
    int foto_e1_pin = 15, int sonar_echo_pin = 16, int sonar_trigger_pin = 17, int button_pin = 18)
  {

  led_blue = led_blue_pin;
  led_red = led_red_pin;
  led_green = led_green_pin;
  motor2_in1 = motor2_in1_pin;
  motor2_in2 = motor2_in2_pin;
  motor2_pwm = motor2_pwm_pin;
  _buzzer = buzzer_pin;
  motor1_in1 = motor1_in1_pin;
  motor1_in2 = motor1_in2_pin;
  motor1_pwm = motor1_pwm_pin;
  foto_e2 = foto_e2_pin;
  foto_e1 = foto_e1_pin;
  sonar_echo = sonar_echo_pin;
  sonar_trigger = sonar_trigger_pin;
  button = button_pin;


  pinMode( led_blue, OUTPUT);
  pinMode( led_red, OUTPUT);
  pinMode( led_green, OUTPUT);
  pinMode( motor2_in1, OUTPUT);
  pinMode( motor2_in2, OUTPUT);
  pinMode( motor2_pwm, OUTPUT);
  pinMode( _buzzer, OUTPUT);
  pinMode( motor1_in1, OUTPUT);
  pinMode( motor1_in2, OUTPUT);
  pinMode( motor1_pwm, OUTPUT);
  pinMode( foto_e2, INPUT);
  pinMode( foto_e1, INPUT);
  pinMode( sonar_echo, INPUT);
  pinMode( sonar_trigger, OUTPUT);
  pinMode( button, INPUT);


  
  }

  void MiniSobot::led_rgb (int R, int G, int B, int disable = 0){

  if (!(disable)){
    analogWrite(led_red, R);
    analogWrite(led_green, G);
    analogWrite(led_blue, B);
  }
  else{
      analogWrite(led_red, 0);
      analogWrite(led_green, 0);
      analogWrite(led_blue, 0);
  }
}


void MiniSobot::buzzer(int frequency = 262, int duration = 0){
   noTone(_buzzer);
  if (duration > 0){
   tone(_buzzer, frequency, duration);
   delay(duration);
   noTone(_buzzer);
  }  
  else tone(_buzzer, frequency);
}

void MiniSobot::stop_buzzer(){
   noTone(_buzzer);
}

int MiniSobot::read_button(){

return digitalRead(button);

}

float MiniSobot::read_ultrasonic(){

    digitalWrite(sonar_trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(sonar_trigger, HIGH);
    delayMicroseconds(10);
    
    float temp = (pulseIn(sonar_echo,HIGH) /29.4 / 2.0 );
    return temp;
}

int MiniSobot::read_line(int sensor){

  int temp = 0;

  if( sensor == 1)temp = digitalRead(foto_e1);
  else if (sensor == 2) temp = digitalRead(foto_e2); 

  return temp;
}

void MiniSobot::drive_forward(int speed = 150){

fwd_motor1(speed);
fwd_motor2(speed);

}

void MiniSobot::drive_backward(int speed = 150){

bwd_motor1(speed);
bwd_motor2(speed);

}

void MiniSobot::drive_break(){
digitalWrite(motor1_in1, HIGH);
digitalWrite(motor1_in2, HIGH);

digitalWrite(motor2_in1, HIGH);
digitalWrite(motor2_in2, HIGH);
analogWrite(motor1_pwm, 0); 
analogWrite(motor2_pwm, 0);
}


void  MiniSobot::drive_curve_right(int speed = 150){
fwd_motor1(speed);
bwd_motor2(speed);
}


void  MiniSobot::drive_curve_left(int speed = 150){
bwd_motor1(speed);
fwd_motor2(speed);
}


void  MiniSobot::drive_curve_differential_right(int speed = 150, int percent = 70){

fwd_motor1(speed);
fwd_motor2(speed*(percent/100.0));
}



void  MiniSobot::drive_curve_differential_left(int speed = 150,  int percent = 70){
fwd_motor2(speed);
fwd_motor1(speed*(percent/100.0));
}



void MiniSobot::fwd_motor1(int speed){
digitalWrite(motor1_in1, HIGH);
digitalWrite(motor1_in2, LOW);
analogWrite(motor1_pwm, speed);
}


void MiniSobot::fwd_motor2(int speed){
digitalWrite(motor2_in1, LOW);
digitalWrite(motor2_in2, HIGH);
analogWrite(motor2_pwm, speed);
}



void MiniSobot::bwd_motor1(int speed){
digitalWrite(motor1_in1, LOW);
digitalWrite(motor1_in2, HIGH);
analogWrite(motor1_pwm, speed);
}

void MiniSobot::bwd_motor2(int speed){
digitalWrite(motor2_in1, HIGH);
digitalWrite(motor2_in2, LOW);
analogWrite(motor2_pwm, speed);
}


