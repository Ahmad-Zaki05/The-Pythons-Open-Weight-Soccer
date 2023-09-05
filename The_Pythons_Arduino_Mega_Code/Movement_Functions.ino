// Left Forward --> counter-clock   LOW
// Left Back    --> counter-clock   LOW
// Right Forward --> clock          HIGH
// Right Back    --> clock          HIGH
void moveWheels(char dir){
  switch(dir){
    case 'f': // Forward
      Serial.println("Forward");
      digitalWrite(l_f_dir, LOW);//counter-clock
      analogWrite(l_f_pwm, move_speed);
      digitalWrite(l_b_dir, LOW);//counter-clock
      analogWrite(l_b_pwm, move_speed);
    
      digitalWrite(r_f_dir, HIGH);//clock
      analogWrite(r_f_pwm, move_speed);
      digitalWrite(r_b_dir, HIGH);//clock
      analogWrite(r_b_pwm, move_speed);
      break;
    case 'b': // Backward
      Serial.println("Backward");
      digitalWrite(l_f_dir, HIGH);
      analogWrite(l_f_pwm, move_speed);
      digitalWrite(l_b_dir, HIGH);
      analogWrite(l_b_pwm, move_speed);
    
      digitalWrite(r_f_dir, LOW);
      analogWrite(r_f_pwm, move_speed);
      digitalWrite(r_b_dir, LOW);
      analogWrite(r_b_pwm, move_speed);
      break;
    case 'r': // Right
      Serial.println("Right");
      digitalWrite(l_f_dir, LOW);
      analogWrite(l_f_pwm, move_speed);
      digitalWrite(l_b_dir, HIGH);
      analogWrite(l_b_pwm, move_speed);
    
      digitalWrite(r_f_dir, LOW);
      analogWrite(r_f_pwm, move_speed);
      digitalWrite(r_b_dir, HIGH);
      analogWrite(r_b_pwm, move_speed);
      break;
    case 'l': // Left
      Serial.println("Left");
      digitalWrite(l_f_dir, HIGH);
      analogWrite(l_f_pwm, move_speed);
      digitalWrite(l_b_dir, LOW);
      analogWrite(l_b_pwm, move_speed);
    
      digitalWrite(r_f_dir, HIGH);
      analogWrite(r_f_pwm, move_speed);
      digitalWrite(r_b_dir, LOW);
      analogWrite(r_b_pwm, move_speed);
      break;
    case 'y': // Diagonal Forward Right
      Serial.println("Diagonal Forward Right");
      digitalWrite(l_f_dir, LOW);
      analogWrite(l_f_pwm, move_speed);
      digitalWrite(l_b_dir, HIGH);
      analogWrite(l_b_pwm, 0);
    
      digitalWrite(r_f_dir, LOW);
      analogWrite(r_f_pwm, 0);
      digitalWrite(r_b_dir, HIGH);
      analogWrite(r_b_pwm, move_speed);
      break;
    case 't': // Diagonal Forward Left
      Serial.println("Diagonal Forward Left");
      digitalWrite(l_f_dir, LOW);
      analogWrite(l_f_pwm, 0);
      digitalWrite(l_b_dir, LOW);
      analogWrite(l_b_pwm, move_speed);
    
      digitalWrite(r_f_dir, HIGH);
      analogWrite(r_f_pwm, move_speed);
      digitalWrite(r_b_dir, HIGH);
      analogWrite(r_b_pwm, 0);
      break;
    case 'h': // Diagonal Backward Right
      Serial.println("Diagonal Backward Right");
      digitalWrite(l_f_dir, HIGH);
      analogWrite(l_f_pwm, move_speed);
      digitalWrite(l_b_dir, HIGH);
      analogWrite(l_b_pwm, 0);
    
      digitalWrite(r_f_dir, LOW);
      analogWrite(r_f_pwm, 0);
      digitalWrite(r_b_dir, LOW);
      analogWrite(r_b_pwm, move_speed);
      break;
    case 'g': // Diagonal Backward Left
      Serial.println("Diagonal Backward Left");
      digitalWrite(l_f_dir, LOW);
      analogWrite(l_f_pwm, 0);
      digitalWrite(l_b_dir, HIGH);
      analogWrite(l_b_pwm, move_speed);
    
      digitalWrite(r_f_dir, LOW);
      analogWrite(r_f_pwm, move_speed);
      digitalWrite(r_b_dir, HIGH);
      analogWrite(r_b_pwm, 0);
      break;
    case 'n': // Rotate Left
      Serial.println("Rotate Left");
      digitalWrite(l_f_dir, HIGH);
      analogWrite(l_f_pwm, move_speed);
      digitalWrite(l_b_dir, HIGH);
      analogWrite(l_b_pwm, move_speed);
    
      digitalWrite(r_f_dir, HIGH);
      analogWrite(r_f_pwm, move_speed);
      digitalWrite(r_b_dir, HIGH);
      analogWrite(r_b_pwm, move_speed);
      break;
    case 'm': // Rotate Right
      Serial.println("Rotate Right");
      digitalWrite(l_f_dir, LOW);
      analogWrite(l_f_pwm, move_speed);
      digitalWrite(l_b_dir, LOW);
      analogWrite(l_b_pwm, move_speed);
    
      digitalWrite(r_f_dir, LOW);
      analogWrite(r_f_pwm, move_speed);
      digitalWrite(r_b_dir, LOW);
      analogWrite(r_b_pwm, move_speed);
      break;
    case 's': // Stop
      Serial.println("Stop");
      analogWrite(l_f_pwm, 0);
      analogWrite(l_b_pwm, 0);
      analogWrite(r_f_pwm, 0);
      analogWrite(r_b_pwm, 0);
      break;
  }
}

void angular_Motion(short b_angle, byte spd) {
//  Serial.print("The angle is: ");
//  Serial.println(angle);

  byte r_f_sp, r_b_sp, l_f_sp, l_b_sp;
  bool r_f_d, r_b_d, l_f_d, l_b_d;
  
  if ((b_angle >= 0) && (b_angle <= 90)) {
//    Serial.println("here 1");
    digitalWrite(r_f_dir, HIGH);
    analogWrite(r_f_pwm, spd);
    digitalWrite(l_b_dir, LOW);
    analogWrite(l_b_pwm, spd);
    if (b_angle == 45) {
      analogWrite(l_f_pwm, 0);
      analogWrite(r_b_pwm, 0);
      return;
    }
    byte spd_ang = (spd * abs(b_angle - 45)) / 45;
//    Serial.println(spd_ang);
    analogWrite(l_f_pwm, spd_ang);
    analogWrite(r_b_pwm, spd_ang);
    if (b_angle < 45) {
      digitalWrite(l_f_dir, HIGH);
      digitalWrite(r_b_dir, LOW);
    }
    else {
      digitalWrite(l_f_dir, LOW);
      digitalWrite(r_b_dir, HIGH);
    }
  }
  else if ((b_angle >= 90) && (b_angle <= 180)) {
    // Serial.println("here 2");
    digitalWrite(r_b_dir, HIGH);
    analogWrite(r_b_pwm, spd);
    digitalWrite(l_f_dir, LOW);
    analogWrite(l_f_pwm, spd);
    if (b_angle == 135) {
      analogWrite(r_f_pwm, 0);
      analogWrite(l_b_pwm, 0);
      return;
    }
    byte spd_ang = (spd * abs(b_angle - 135)) / 45;
    analogWrite(r_f_pwm, spd_ang);
    analogWrite(l_b_pwm, spd_ang);
    if (b_angle < 135) {
      digitalWrite(r_f_dir, HIGH);
      digitalWrite(l_b_dir, LOW);
    }
    else {
      digitalWrite(r_f_dir, LOW);
      digitalWrite(l_b_dir, HIGH);
    }
  } 
  else if ((b_angle >= 180) && (b_angle <= 270)) {
    // Serial.println("here 3");
    digitalWrite(r_f_dir, LOW);
    analogWrite(r_f_pwm, spd);
    digitalWrite(l_b_dir, HIGH);
    analogWrite(l_b_pwm, spd);
    if (b_angle == 225) {
      analogWrite(l_f_pwm, 0);
      analogWrite(r_b_pwm, 0);
      return;
    }
    byte spd_ang = (spd * abs(b_angle - 225)) / 45;
    analogWrite(l_f_pwm, spd_ang);
    analogWrite(r_b_pwm, spd_ang);
    if (b_angle < 225) {
      digitalWrite(l_f_dir, LOW);
      digitalWrite(r_b_dir, HIGH);
    }
    else {
      // Serial.println("here 10");
      digitalWrite(l_f_dir, HIGH);
      digitalWrite(r_b_dir, LOW);
    }
  }
  else if ((b_angle >= 270) && (b_angle <= 360)) {
    // Serial.println("here 4");
    digitalWrite(r_b_dir, LOW);
    analogWrite(r_b_pwm, spd);
    digitalWrite(l_f_dir, HIGH);
    analogWrite(l_f_pwm, spd);
    if (b_angle == 315) {
      analogWrite(r_f_pwm, 0);
      analogWrite(l_b_pwm, 0);
      return;
    }
    byte spd_ang = (spd * abs(b_angle - 315)) / 45;
    analogWrite(r_f_pwm, spd_ang);
    analogWrite(l_b_pwm, spd_ang);
    if (b_angle < 315) {
      digitalWrite(r_f_dir, LOW);
      digitalWrite(l_b_dir, HIGH);
    }
    else {
      digitalWrite(r_f_dir, HIGH);
      digitalWrite(l_b_dir, LOW);
    }
  }
}

void maintain_Heading(){
  read_Nano();
  if(robot_heading > 5){
    moveWheels('n');//rotate left
  }
  else if(robot_heading < -5){
    moveWheels('m');//rotate right
  }
//  else
//  {
//    moveWheels('s');//stop
//  }
}



    
