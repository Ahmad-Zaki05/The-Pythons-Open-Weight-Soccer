/*** Cytron pins ***/
byte l_f_dir = 4;
byte l_f_pwm = 5; 
byte l_b_dir = 2; 
byte l_b_pwm = 3; 

byte r_b_dir = 8; 
byte r_b_pwm = 9; 
byte r_f_dir = 10; 
byte r_f_pwm = 11; 
/*******************/

#define move_speed 60

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
String cam_angle_str;
int cam_angle;
/************************/

/*** Nano variables ***/
String received_imu_angle;
int robot_heading = 0;
/**********************/

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
  delay(3000);
  
}

void loop() {
  
  read_Camera();
//  read_IR();
  maintain_Heading();


/***Tracking Ball (Angle)***/
//  for (short i = 0; i < 360; i += 90) {
//    angular_Motion(i, 100); 
//    delay(1000);   
//  }
/***************************/

/***Tracking Ball (Regions)***/
//moveWheels(camera_char);
/*****************************/

/***Testing Motion***/
//  delay(5000);
//  digitalWrite(l_f_dir, LOW);//counter-clock
//  analogWrite(l_f_pwm, move_speed);
//  digitalWrite(l_b_dir, LOW);//counter-clock
//  analogWrite(l_b_pwm, move_speed);
//
//  digitalWrite(r_f_dir, HIGH);//clock
//  analogWrite(r_f_pwm, move_speed);
//  digitalWrite(r_b_dir, HIGH);//clock
//  analogWrite(r_b_pwm, move_speed);
//  moveWheels('f');//forward
//  delay(2000);
//  moveWheels('b');//backward
//  delay(2000);
//  moveWheels('r');//right
//  delay(2000);
//  moveWheels('l');//back
//  delay(2000);
//  moveWheels('y');//diagonal forward right
//  delay(2000);
//  moveWheels('h');//diagonal backward right
//  delay(2000);
//  moveWheels('t');//diagonal forward left
//  delay(2000);
//  moveWheels('g');//diagonal backward left
//  delay(2000);
//  moveWheels('m');//rotate right
//  delay(2000);
//  moveWheels('n');//rotate left
//  delay(2000);
//  moveWheels('s');//stop
//  delay(2000);
/********************/
}
