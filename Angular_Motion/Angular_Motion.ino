byte f_r_dir = 10;
byte f_r_pwm = 11;
byte f_l_dir = 4;
byte f_l_pwm = 5;
byte b_r_dir = 8;
byte b_r_pwm = 9;
byte b_l_dir = 2;
byte b_l_pwm = 3;
//byte angle;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  
  pinMode(f_r_dir, OUTPUT);
  pinMode(f_r_pwm, OUTPUT);
  pinMode(f_l_dir, OUTPUT);
  pinMode(f_l_pwm, OUTPUT);
  pinMode(b_r_dir, OUTPUT);
  pinMode(b_r_pwm, OUTPUT);
  pinMode(b_l_dir, OUTPUT);
  pinMode(b_l_pwm, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  angular_Motion(0, 0);
  delay(10000);
//  angular_Motion(30, 180);
//  delay(1000);
  for (short i = 0; i < 360; i += 5) {
    angular_Motion(i, 40); 
    delay(1000);   
  }
}
