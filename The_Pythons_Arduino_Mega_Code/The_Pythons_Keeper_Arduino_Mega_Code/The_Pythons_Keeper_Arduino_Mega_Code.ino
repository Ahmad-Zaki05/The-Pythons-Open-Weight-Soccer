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

//// Striker (new motors)
//#define Down_Left_Direction 8
//#define Down_Right_Direction 2
//#define Upper_Left_Direction 6
//#define Upper_Right_Direction 4
//#define Down_Left_PWM 9
//#define Down_Right_PWM 3
//#define Upper_Left_PWM 7
//#define Upper_Right_PWM 5

// Keeper (old motors)
#define Down_Left_Direction 6
#define Down_Right_Direction 2
#define Upper_Left_Direction 8
#define Upper_Right_Direction 4
#define Down_Left_PWM 7
#define Down_Right_PWM 3
#define Upper_Left_PWM 9
#define Upper_Right_PWM 5

#define start_motors 23

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
//#define ir_0 A2 ////right back
//#define ir_1 A1 ////right front
//#define ir_2 A5 ////back right
//#define ir_3 A6 ////back left
//#define ir_4 A9 //// left back
//#define ir_5 A10 //// left front//
//#define ir_6 A11 ////front right
//#define ir_7 A12 ////front left

//// Keeper (old motors)
//#define ir_0 A9 ////right back
//#define ir_1 A10 ////right front
//#define ir_2 A5 ////back right//
//#define ir_3 A6 ////back left
//#define ir_4 A12 //// left back
//#define ir_5 A11 //// left front
//#define ir_6 A15 ////front right 
//#define ir_7 A1 ////front left

// Keeper (old motors)
#define ir_0 A9 ////right back
#define ir_1 A10 ////right front
#define ir_2 A6 ////back right//
#define ir_3 A11 ////back left
#define ir_4 A12 //// left back
#define ir_5 A13 //// left front
#define ir_6 A15 ////front right 
#define ir_7 A1 ////front left

int ir_offsets[8][2];

short ir_calibration_offset = 4;

bool seeking = 0;
byte ir_counter_f = 0, ir_counter_b = 0;

#define ir_calib_button 41

/***************************/

/*** Camera variables ***/
char camera_char;
String cam_angle_str = "Dss";
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
short rb_last = 500;

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

  dribbler.attach(11, 1000, 2000);  // attaches the servo on pin 10 to the servo object
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

  pinMode(start_motors, INPUT_PULLUP);

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
  ir_offsets[0][1] = readInt(16);
  ir_offsets[1][0] = readInt(2);
  ir_offsets[1][1] = readInt(18);
  ir_offsets[2][0] = readInt(4);
  ir_offsets[2][1] = readInt(20);
  ir_offsets[3][0] = readInt(6);
  ir_offsets[3][1] = readInt(22);
  ir_offsets[4][0] = readInt(8);
  ir_offsets[4][1] = readInt(24);
  ir_offsets[5][0] = readInt(10);
  ir_offsets[5][1] = readInt(26);
  ir_offsets[6][0] = readInt(12);
  ir_offsets[6][1] = readInt(28);
  ir_offsets[7][0] = readInt(14);
  ir_offsets[7][1] = readInt(30);
  //
  //  Serial.print("RB min: ");
  //  Serial.print(ir_offsets[0][0]);
  //  Serial.print(" max: ");
  //  Serial.print(ir_offsets[0][1]);
  //  Serial.print(" offset: ");
  //  Serial.print(ir_offsets[0][0] + (ir_offsets[0][1] - ir_offsets[0][0]) / ir_calibration_offset);
  //  Serial.print("\nRF: min: ");
  //  Serial.print(ir_offsets[1][0]);
  //  Serial.print(" max: ");
  //  Serial.print(ir_offsets[1][1]);
  //  Serial.print(" offset: ");
  //  Serial.print(ir_offsets[1][0] + (ir_offsets[1][1] - ir_offsets[1][0]) / ir_calibration_offset);
  //  Serial.print("\nBR: min: ");
  //  Serial.print(ir_offsets[2][0]);
  //  Serial.print(" max: ");
  //  Serial.print(ir_offsets[2][1]);
  //  Serial.print(" offset: ");
  //  Serial.print(ir_offsets[2][0] + (ir_offsets[2][1] - ir_offsets[2][0]) / ir_calibration_offset);
  //  Serial.print("\nBL: min: ");
  //  Serial.print(ir_offsets[3][0]);
  //  Serial.print(" max: ");
  //  Serial.print(ir_offsets[3][1]);
  //  Serial.print(" offset: ");
  //  Serial.print(ir_offsets[3][0] + (ir_offsets[3][1] - ir_offsets[3][0]) / ir_calibration_offset);
  //  Serial.print("\nLB: min: ");
  //  Serial.print(ir_offsets[4][0]);
  //  Serial.print(" max: ");
  //  Serial.print(ir_offsets[4][1]);
  //  Serial.print(" offset: ");
  //  Serial.print(ir_offsets[4][0] + (ir_offsets[4][1] - ir_offsets[4][0]) / ir_calibration_offset);
  //  Serial.print("\nLF: min: ");
  //  Serial.print(ir_offsets[5][0]);
  //  Serial.print(" max: ");
  //  Serial.print(ir_offsets[5][1]);
  //  Serial.print(" offset: ");
  //  Serial.print(ir_offsets[5][0] + (ir_offsets[5][1] - ir_offsets[5][0]) / ir_calibration_offset);
  //  Serial.print("\nFR: min: ");
  //  Serial.print(ir_offsets[6][0]);
  //  Serial.print(" max: ");
  //  Serial.print(ir_offsets[6][1]);
  //  Serial.print(" offset: ");
  //  Serial.print(ir_offsets[6][0] + (ir_offsets[6][1] - ir_offsets[6][0]) / ir_calibration_offset);
  //  Serial.print("\nFL: min: ");
  //  Serial.print(ir_offsets[7][0]);
  //  Serial.print(" max: ");
  //  Serial.print(ir_offsets[7][1]);
  //  Serial.print(" offset: ");
  //  Serial.print(ir_offsets[7][0] + (ir_offsets[7][1] - ir_offsets[7][0]) / ir_calibration_offset);
  //  Serial.println();

  forward = 0;
  side = 0;
  turn = 0;

}
void loop() {
  //    Serial.print("IR Calibration Button: ");
  //    Serial.println(digitalRead(ir_calib_button));
  //  Serial.print("Front: ");
  //  Serial.println(is_line_front());
  //  Serial.print("front counter: ");
  //  Serial.print(ir_counter_f);
  //  Serial.print("\tback counter: ");
  //  Serial.println(ir_counter_b);
  if (digitalRead(ir_calib_button))
    calibrate_IRs();
  // forward = 50;
  // side = 50;
//  turn = 50;
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
  //  new_out_line();//
  //  new_new_out_line();
    out_line();
  //Serial.print("start motors Button: ");
  //    Serial.println(digitalRead(start_motors));

  if (digitalRead(start_motors))
    motioneq();
  else {
    forward = 0;
    side = 0;
    turn = 0;
    motioneq();
  }

  //  timer = millis();
  //  while(millis() - timer < 1000){
  //    forward = 60;
  //    side = 0;
  //    motioneq();//
  //    read_Nano();
  //  }
  //  timer = millis();
  //  while(millis() - timer < 1000){
  //    forward = 0;
  //    side = 60;
  //    motioneq();//
  //    read_Nano();
  //  }
  //  timer = millis();
  //  while(millis() - timer < 1000){
  //    forward = -60;
  //    side = 0;
  //    motioneq();//
  //    read_Nano();
  //  }
  //  timer = millis();
  //  while(millis() - timer < 1000){
  //    forward = 0;
  //    side = -60;
  //    motioneq();//
  //    read_Nano();
  //  }
  //  rb_last = analogRead(ir_0);
  //read_Camera();
  //  for (short i = 0; i < 360; i += 45) {
  //    angular_Motion(i, 120);
  //    delay(500);
  //  }
  //  maintain_Heading();
  //read_Nano();
  //  angular_Motion(90, 120);
}
