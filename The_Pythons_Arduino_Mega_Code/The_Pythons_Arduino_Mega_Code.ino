#define l_f_dir 4 
#define l_f_pwm 5 
#define l_b_dir 2 
#define l_b_pwm 3 


#define r_b_dir 8 
#define r_b_pwm 9 
#define r_f_dir 10 
#define r_f_pwm 11 

#define move_speed 50

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

void setup() {
  Serial.begin(115200);
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
  
//  delay(5000);
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
}
