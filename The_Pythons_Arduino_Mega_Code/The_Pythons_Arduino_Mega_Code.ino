#define l_f_dir 4 
#define l_f_pwm 5 
#define l_b_dir 2 
#define l_b_pwm 3 


#define r_b_dir 8 
#define r_b_pwm 9 
#define r_f_dir 10 
#define r_f_pwm 11 


#define move_speed 50

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
  
}

void loop() {
//  digitalWrite(l_f_dir, LOW);//counter-clock//left back
//  analogWrite(l_f_pwm, move_speed);
//  digitalWrite(l_b_dir, LOW);//counter-clock//left front
//  analogWrite(l_b_pwm, move_speed);
//
//  digitalWrite(r_f_dir, HIGH);//clock//right front
//  analogWrite(r_f_pwm, move_speed);
//  digitalWrite(r_b_dir, HIGH);//clock//right back
//  analogWrite(r_b_pwm, move_speed);
  delay(5000);
  moveWheels('f');//forward
  delay(2000);
  moveWheels('b');//backward
  delay(2000);
  moveWheels('r');//right
  delay(2000);
  moveWheels('l');//back
  delay(2000);
  moveWheels('y');//diagonal forward right
  delay(2000);
  moveWheels('h');//diagonal backward right
  delay(2000);
  moveWheels('t');//diagonal forward left
  delay(2000);
  moveWheels('g');//diagonal backward left
  delay(2000);
  moveWheels('m');//rotate right
  delay(2000);
  moveWheels('n');//rotate left
  delay(2000);
  moveWheels('s');//stop
  delay(2000);
}
