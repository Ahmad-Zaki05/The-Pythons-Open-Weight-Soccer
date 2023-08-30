void angular_Motion(short angle, byte spd) {
  Serial.print("The angle is: ");
  Serial.println(angle);
  if ((angle >= 0) && (angle <= 90)) {
    Serial.println("here 1");
    digitalWrite(f_r_dir, HIGH);
    analogWrite(f_r_pwm, spd);
    digitalWrite(b_l_dir, LOW);
    analogWrite(b_l_pwm, spd);
    if (angle == 45) {
      analogWrite(f_l_pwm, 0);
      analogWrite(b_r_pwm, 0);
      return;
    }
    byte spd_ang = (spd * abs(angle - 45)) / 45;
    Serial.println(spd_ang);
    analogWrite(f_l_pwm, spd_ang);
    analogWrite(b_r_pwm, spd_ang);
    if (angle < 45) {
      digitalWrite(f_l_dir, HIGH);
      digitalWrite(b_r_dir, LOW);
    }
    else {
      digitalWrite(f_l_dir, LOW);
      digitalWrite(b_r_dir, HIGH);
    }
  }
  else if ((angle >= 90) && (angle <= 180)) {
    Serial.println("here 2");
    digitalWrite(b_r_dir, HIGH);
    analogWrite(b_r_pwm, spd);
    digitalWrite(f_l_dir, LOW);
    analogWrite(f_l_pwm, spd);
    if (angle == 135) {
      analogWrite(f_r_pwm, 0);
      analogWrite(b_l_pwm, 0);
      return;
    }
    byte spd_ang = (spd * abs(angle - 135)) / 45;
    analogWrite(f_r_pwm, spd_ang);
    analogWrite(b_l_pwm, spd_ang);
    if (angle < 135) {
      digitalWrite(f_r_dir, HIGH);
      digitalWrite(b_l_dir, LOW);
    }
    else {
      digitalWrite(f_r_dir, LOW);
      digitalWrite(b_l_dir, HIGH);
    }
  } 
  else if ((angle >= 180) && (angle <= 270)) {
    Serial.println("here 3");
    digitalWrite(f_r_dir, LOW);
    analogWrite(f_r_pwm, spd);
    digitalWrite(b_l_dir, HIGH);
    analogWrite(b_l_pwm, spd);
    if (angle == 225) {
      analogWrite(f_l_pwm, 0);
      analogWrite(b_r_pwm, 0);
      return;
    }
    byte spd_ang = (spd * abs(angle - 225)) / 45;
    analogWrite(f_l_pwm, spd_ang);
    analogWrite(b_r_pwm, spd_ang);
    if (angle < 225) {
      digitalWrite(f_l_dir, LOW);
      digitalWrite(b_r_dir, HIGH);
    }
    else {
      Serial.println("here 10");
      digitalWrite(f_l_dir, HIGH);
      digitalWrite(b_r_dir, LOW);
    }
  }
  else if ((angle >= 270) && (angle <= 360)) {
    Serial.println("here 4");
    digitalWrite(b_r_dir, LOW);
    analogWrite(b_r_pwm, spd);
    digitalWrite(f_l_dir, HIGH);
    analogWrite(f_l_pwm, spd);
    if (angle == 315) {
      analogWrite(f_r_pwm, 0);
      analogWrite(b_l_pwm, 0);
      return;
    }
    byte spd_ang = (spd * abs(angle - 315)) / 45;
    analogWrite(f_r_pwm, spd_ang);
    analogWrite(b_l_pwm, spd_ang);
    if (angle < 315) {
      digitalWrite(f_r_dir, LOW);
      digitalWrite(b_l_dir, HIGH);
    }
    else {
      digitalWrite(f_r_dir, HIGH);
      digitalWrite(b_l_dir, LOW);
    }
  }
}
/*
 * void angular_Motion(byte angle, byte spd) {
  if ((angle >= 0) && (angle <= 90)) {
    digitalWrite(f_l_dir, LOW);
    analogWrite(f_l_pwm, spd);
    digitalWrite(b_r_dir, HIGH);
    analogWrite(b_r_pwm, spd);
    if (angle == 45) {
      analogWrite(f_r_pwm, 0);
      analogWrite(b_l_pwm, 0);
      return ;
    }
    byte spd_ang = (spd * abs(angle - 45)) / 45;
    analogWrite(f_r_pwm, spd_ang);
    analogWrite(b_l_pwm, spd_ang);
    if (angle < 45) {
      digitalWrite(f_r_dir, LOW);  
      digitalWrite(b_l_dir, HIGH);
    }
    else {
      digitalWrite(f_r_dir, HIGH);  
      digitalWrite(b_l_dir, LOW);
    }
  }
  else if ((angle >= 90) && (angle <= 180)) {
    digitalWrite(b_l_dir, LOW);
    analogWrite(b_l_pwm, spd);
    digitalWrite(f_r_dir, HIGH);
    analogWrite(f_r_pwm, spd);
    if (angle == 135) {
      analogWrite(b_r_pwm, 0);
      analogWrite(f_l_pwm, 0);
      return ;
    }
    byte spd_ang = (spd * abs(angle - 135)) / 45;
    analogWrite(b_r_pwm, spd_ang);
    analogWrite(f_l_pwm, spd_ang);
    if (angle < 135) {
      digitalWrite(f_l_dir, LOW);  
      digitalWrite(b_r_dir, HIGH);
    }
    else {
      digitalWrite(f_l_dir, HIGH);  
      digitalWrite(b_r_dir, LOW);
    }
  } 
  else if ((angle >= 180) && (angle <= 270)) {
    digitalWrite(f_l_dir, HIGH);
    analogWrite(f_l_pwm, spd);
    digitalWrite(b_r_dir, LOW);
    analogWrite(b_r_pwm, spd);
    if (angle == 225) {
      analogWrite(f_r_pwm, 0);
      analogWrite(b_l_pwm, 0);
      return ;
    }
    byte spd_ang = (spd * abs(angle - 225)) / 45;
    analogWrite(f_r_pwm, spd_ang);
    analogWrite(b_l_pwm, spd_ang);
    if (angle < 225) {
      digitalWrite(f_r_dir, HIGH);  
      digitalWrite(b_l_dir, LOW);
    }
    else {
      digitalWrite(f_r_dir, LOW);  
      digitalWrite(b_l_dir, HIGH);
    }
  }
  else if ((angle >= 270) && (angle <= 360)) {
     digitalWrite(b_l_dir, HIGH);
    analogWrite(b_l_pwm, spd);
    digitalWrite(f_r_dir, LOW);
    analogWrite(f_r_pwm, spd);
    if (angle == 135) {
      analogWrite(b_r_pwm, 0);
      analogWrite(f_l_pwm, 0);
      return ;
    }
    byte spd_ang = (spd * abs(angle - 315)) / 45;
    analogWrite(b_r_pwm, spd_ang);
    analogWrite(f_l_pwm, spd_ang);
    if (angle < 135) {
      digitalWrite(f_l_dir, HIGH);  
      digitalWrite(b_r_dir, LOW);
    }
    else {
      digitalWrite(f_l_dir, LOW);  
      digitalWrite(b_r_dir, HIGH);
    }
  }
}
 */
