#include <math.h>
#include<Servo.h>
#include <EEPROM.h>

/*** Cytron pins ***/
byte l_f_dir = 6;
byte l_f_pwm = 7;
byte l_b_dir = 8;
byte l_b_pwm = 9;

byte r_b_dir = 2;
byte r_b_pwm = 3;
byte r_f_dir = 4;
byte r_f_pwm = 5;


#define Down_Left_Direction 8
#define Down_Right_Direction 2
#define Upper_Left_Direction 6
#define Upper_Right_Direction 4
#define Down_Left_PWM 9
#define Down_Right_PWM 3
#define Upper_Left_PWM 7
#define Upper_Right_PWM 5

long counter = 0;

int side = 0 , forward = 0, turn = 0;

int speeda, speedb, speedc, speedd, temp;
int flag = 0 , flag2 = 0 , Speed2 = 0;

/*******************/

unsigned long long int timer;

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

//// Striker (new motors)
#define ir_0 A1 ////right back
#define ir_1 A2 ////right front
#define ir_2 A5 ////back right
#define ir_3 A6 ////back left
#define ir_4 A9 //// left back
#define ir_5 A10 //// left front//
#define ir_6 A11 ////front right 
#define ir_7 A12 ////front left

// Keeper (old motors)
//#define ir_0 A10 ////right back
//#define ir_1 A9 ////right front
//#define ir_2 A12 ////back right//
//#define ir_3 A5 ////back left
//#define ir_4 A6 //// left back
//#define ir_5 A1 //// left front
//#define ir_6 A11 ////front right 
//#define ir_7 A2 ////front left

short ir_offsets[8][2];

short ir_calibration_offset = 70;

#define ir_calib_button 41

/***************************/

/*** Camera variables ***/
char camera_char;
String cam_angle_str = "S";
int cam_angle;
/************************/

/*** Nano variables ***/
String received_imu_angle;
int robot_heading = 0;
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
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);


  pinMode(Down_Left_Direction, OUTPUT);
  pinMode(Down_Right_Direction, OUTPUT);
  pinMode(Upper_Left_Direction, OUTPUT);
  pinMode(Upper_Right_Direction, OUTPUT);
  pinMode(Down_Left_PWM, OUTPUT);
  pinMode(Down_Right_PWM, OUTPUT);
  pinMode(Upper_Left_PWM, OUTPUT);
  pinMode(Upper_Right_PWM, OUTPUT);

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
  //turnDribbler(1);

  //  pinMode(Solenoid,OUTPUT);
  //
  //  Brushless.attach(12);
  //  Brushless.writeMicroseconds(2000);
  //  Brushless.writeMicroseconds(1000);
  /*
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
  */

  pinMode(ir_0, INPUT);
  pinMode(ir_1, INPUT);
  pinMode(ir_2, INPUT);
  pinMode(ir_3, INPUT);
  pinMode(ir_4, INPUT);
  pinMode(ir_5, INPUT);
  pinMode(ir_6, INPUT);
  pinMode(ir_7, INPUT);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);


  ir_offsets[0][0] = readInt(0);
  ir_offsets[0][1] = readInt(1);
  ir_offsets[1][0] = readInt(2);
  ir_offsets[1][1] = readInt(3);
  ir_offsets[2][0] = readInt(4);
  ir_offsets[2][1] = readInt(5);
  ir_offsets[3][0] = readInt(6);
  ir_offsets[3][1] = readInt(7);
  ir_offsets[4][0] = readInt(8);
  ir_offsets[4][1] = readInt(9);
  ir_offsets[5][0] = readInt(10);
  ir_offsets[5][1] = readInt(11);
  ir_offsets[6][0] = readInt(12);
  ir_offsets[6][1] = readInt(13);
  ir_offsets[7][0] = readInt(14);
  ir_offsets[7][1] = readInt(15);
  forward = 0;
  side = 0;
  turn = 0;

}
void loop() {
  //  Serial.print("IR Calibration Button: ");
  //  Serial.println(digitalRead(ir_calib_button));
  if (digitalRead(ir_calib_button))
    calibrate_IRs();
// forward = 0;
// side = 0;
  read_Nano();//
  new_new_read_Camera(); //

//  read_IR();
  //   if(is_line_front()){
  //    forward = 0;
  //    side = 30;
  //   }
  //   if(is_line_right()){
  //    forward = -30;
  //    side = 0;
  //   }
  //   if(is_line_back()){
  //    forward = 0;
  //    side = -30;
  //   }
  //  side = 50;
  //  if (is_line_right()) {
  //    side = 0;
  //    motioneq();
  //    delay(300);
  //    side = -70;
  //  }

  //Serial1.flush();
  //Serial.print(cam_angle);
  //Serial.println(".");
  //Serial.println(robot_heading);
  out_line();//
  motioneq();//
  //read_Camera();
  //  for (short i = 0; i < 360; i += 45) {
  //    angular_Motion(i, 120);
  //    delay(500);
  //  }
  //  maintain_Heading();
  //read_Nano();
  //  angular_Motion(90, 120);
}
