#include <math.h>
#include<Servo.h>
#include <SerialUART.h>

#define Down_Left_Direction 2
#define Down_Right_Direction 3
#define Upper_Left_Direction 6
#define Upper_Right_Direction 7
#define Down_Left_PWM 10
#define Down_Right_PWM 11
#define Upper_Left_PWM 14
#define Upper_Right_PWM 15

long counter = 0;

int side = 0 , forward = 0, turn = 0;

int speeda, speedb, speedc, speedd, temp;
int Speed2 = 0;

unsigned long long int timer;

Servo dribbler;
#define dribbler_pin 18

#define solenoid 19

#define fb1 20
#define fb2 21
#define rl1 22
#define rl2 26

char camera_char;
String cam_angle_str = "Dss";
int cam_angle;

String received_imu_angle;
int robot_heading = 0;

float setpoint = 0.0; // Setpoint for the heading

bool seeking = 0;
byte ir_counter_f = 0, ir_counter_b = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
 
  Serial1.setTX(0);
  Serial1.setRX(1);
  Serial1.begin(115200);
 
  Serial2.setTX(4);
  Serial2.setRX(5);
  Serial2.begin(115200);

  pinMode(Down_Left_Direction, OUTPUT);
  pinMode(Down_Right_Direction, OUTPUT);
  pinMode(Upper_Left_Direction, OUTPUT);
  pinMode(Upper_Right_Direction, OUTPUT);
  pinMode(Down_Left_PWM, OUTPUT);
  pinMode(Down_Right_PWM, OUTPUT);
  pinMode(Upper_Left_PWM, OUTPUT);
  pinMode(Upper_Right_PWM, OUTPUT);

  dribbler.attach(dribbler_pin, 1000, 2000);  // attaches the servo on pin 10 to the servo object
  dribbler.write(180);

  pinMode(solenoid, OUTPUT);

  pinMode(fb1, INPUT);
  pinMode(fb2, INPUT);
  pinMode(rl1, INPUT);
  pinMode(rl2, INPUT);

  forward = 0;
  side = 0;
  turn = 0;
  motioneq();
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
