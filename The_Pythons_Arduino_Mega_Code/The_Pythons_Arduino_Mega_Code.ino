#include <math.h>
#include<Servo.h>

/*** Cytron pins ***/
byte l_f_dir = 6;
byte l_f_pwm = 7;
byte l_b_dir = 8;
byte l_b_pwm = 9;

byte r_b_dir = 2;
byte r_b_pwm = 3;
byte r_f_dir = 4;
byte r_f_pwm = 5;
/*******************/

#define move_s 80

/*** IR pins & variables ***/
#define ir_FR A0
#define ir_RR A1
#define ir_LR A2
#define ir_LL A3
#define ir_BL A4
#define ir_BR A5
#define ir_RL A6
#define ir_FL A7
int ir_read_FR = 0;
int ir_read_RL = 0;
int ir_read_LR = 0;
int ir_read_LL = 0;
int ir_read_BL = 0;
int ir_read_BR = 0;
int ir_read_RR = 0;
int ir_read_FL = 0;
/***************************/

/*** Camera variables ***/
char camera_char;
String cam_angle_str = "S";
short cam_angle;
/************************/

/*** Nano variables ***/
String received_imu_angle;
short robot_heading = 0;
/**********************/

/*** PID variables ***/
float error = 0.0;
float previousError = 0.0;
float integral = 0.0;

float Kp = 0.65;  // Proportional gain // 0.96  // kpc = 1.6
float Ki = 0.0;  // Integral gain    // 0.002
float Kd = 0.01; // Derivative gain    // 0.08

float setpoint = 0.0; // Setpoint for the heading
/*********************/

bool call_ang = false;

//#define Solenoid 25

//Servo Brushless;
Servo dribbler;

void setup() {
  Serial.begin(115200);
  //Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  pinMode(l_f_pwm, OUTPUT);
  pinMode(l_b_pwm, OUTPUT);
  pinMode(l_f_dir, OUTPUT);
  pinMode(l_b_dir, OUTPUT);

  pinMode(r_f_pwm, OUTPUT);
  pinMode(r_b_pwm, OUTPUT);
  pinMode(r_f_dir, OUTPUT);
  pinMode(r_b_dir, OUTPUT);

  pinMode(ir_FR, INPUT);
  pinMode(ir_RL, INPUT);
  pinMode(ir_LR, INPUT);
  pinMode(ir_LL, INPUT);
  pinMode(ir_BL, INPUT);
  pinMode(ir_BR, INPUT);
  pinMode(ir_RR, INPUT);
  pinMode(ir_FL, INPUT);
  delay(2000);

  dribbler.attach(10, 1000, 2000);  // attaches the servo on pin 9 to the servo object
  dribbler.write(180);
  delay(2000);
  dribbler.write(0);
  delay(2000);

  dribbler.write(40);

  //  pinMode(Solenoid,OUTPUT);
  //
  //  Brushless.attach(12);
  //  Brushless.writeMicroseconds(2000);
  //  Brushless.writeMicroseconds(1000);

  for (byte i = 0; i < 50;) {
    if (Serial3.available()) {
      i++;
      //Serial.print("in for 1\n");
    }
  }
  for (byte i = 0; i < 50;) {
    if (Serial2.available()) {
      i++;
      //Serial.print("in for 2\n");
    }
  }
}
void loop() {
  read_Camera();
  //  maintain_Heading();
  //  read_Nano();
  //  angular_Motion(90, 120);
}
