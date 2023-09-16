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

  byte r_f_sp, r_b_sp, l_f_sp, l_b_sp, ang_diff;
  bool r_f_d, r_b_d, l_f_d, l_b_d;
  
  if ((b_angle >= 0) && (b_angle <= 90)) {
//    Serial.println("here 1");
    ang_diff = (90 - b_angle);
    r_f_d = HIGH;
    r_f_sp = spd;
    l_b_d = LOW;
    l_b_sp = spd;
//    digitalWrite(r_f_dir, HIGH);
//    analogWrite(r_f_pwm, spd);
//    digitalWrite(l_b_dir, LOW);
//    analogWrite(l_b_pwm, spd);
    if (b_angle == 45) {
//      analogWrite(l_f_pwm, 0);
//      analogWrite(r_b_pwm, 0);
      l_f_sp = 0;
      r_b_sp = 0;
    }
    else {
      byte spd_ang = (spd * abs(b_angle - 45)) / 45;
  //    Serial.println(spd_ang);
//      analogWrite(l_f_pwm, spd_ang);
//      analogWrite(r_b_pwm, spd_ang);
      l_f_sp = spd_ang;
      r_b_sp = spd_ang;
      if (b_angle < 45) {
//        digitalWrite(l_f_dir, HIGH);
//        digitalWrite(r_b_dir, LOW);
        l_f_d = HIGH;
        r_b_d = LOW;
      }
      else {
//        digitalWrite(l_f_dir, LOW);
//        digitalWrite(r_b_dir, HIGH);
        l_f_d = LOW;
        r_b_d = HIGH;
      }
    }
  }
  else if ((b_angle >= 90) && (b_angle <= 180)) {
    // Serial.println("here 2");
    ang_diff = (b_angle - 90);
//    digitalWrite(r_b_dir, HIGH);
//    analogWrite(r_b_pwm, spd);
//    digitalWrite(l_f_dir, LOW);
//    analogWrite(l_f_pwm, spd);
    r_b_d = HIGH;
    r_b_sp = spd;
    l_f_d = LOW;
    l_f_sp = spd;
    if (b_angle == 135) {
//      analogWrite(r_f_pwm, 0);
//      analogWrite(l_b_pwm, 0);
      r_f_sp = 0;
      l_b_sp = 0;
    }
    else {
      byte spd_ang = (spd * abs(b_angle - 135)) / 45;
//      analogWrite(r_f_pwm, spd_ang);
//      analogWrite(l_b_pwm, spd_ang);
      r_f_sp = spd_ang;
      l_b_sp = spd_ang;
      if (b_angle < 135) {
//        digitalWrite(r_f_dir, HIGH);
//        digitalWrite(l_b_dir, LOW);
        r_f_d = HIGH;
        l_b_d = LOW;
      }
      else {
//        digitalWrite(r_f_dir, LOW);
//        digitalWrite(l_b_dir, HIGH);
        r_f_d = LOW;
        l_b_d = HIGH;
      }
    }
  } 
  else if ((b_angle >= 180) && (b_angle <= 270)) {
    // Serial.println("here 3");
    ang_diff = (b_angle - 90);
//    digitalWrite(r_f_dir, LOW);
//    analogWrite(r_f_pwm, spd);
//    digitalWrite(l_b_dir, HIGH);
//    analogWrite(l_b_pwm, spd);
    r_f_d = LOW;
    r_f_sp = spd;
    l_b_d = HIGH;
    l_b_sp = spd;
    if (b_angle == 225) {
//      analogWrite(l_f_pwm, 0);
//      analogWrite(r_b_pwm, 0);
      l_f_sp = 0;
      r_b_sp = 0;
    }
    else {
      byte spd_ang = (spd * abs(b_angle - 225)) / 45;
//      analogWrite(l_f_pwm, spd_ang);
//      analogWrite(r_b_pwm, spd_ang);
      l_f_sp = spd_ang;
      r_b_sp = spd_ang;
      if (b_angle < 225) {
//        digitalWrite(l_f_dir, LOW);
//        digitalWrite(r_b_dir, HIGH);
        l_f_d = LOW;
        r_b_d = HIGH;
      }
      else {
        // Serial.println("here 10");
//        digitalWrite(l_f_dir, HIGH);
//        digitalWrite(r_b_dir, LOW);
        l_f_d = HIGH;
        r_b_d = LOW;
      }
    }
  }
  else if ((b_angle >= 270) && (b_angle <= 360)) {
    // Serial.println("here 4");
    ang_diff = (360 - b_angle + 90);
//    digitalWrite(r_b_dir, LOW);
//    analogWrite(r_b_pwm, spd);
//    digitalWrite(l_f_dir, HIGH);
//    analogWrite(l_f_pwm, spd);
    r_b_d = LOW;
    r_b_sp = spd;
    l_f_d = HIGH;
    l_f_sp = spd;
    if (b_angle == 315) {
//      analogWrite(r_f_pwm, 0);
//      analogWrite(l_b_pwm, 0);
      r_f_sp = 0;
      l_b_sp = 0;
    }
    else {
      byte spd_ang = (spd * abs(b_angle - 315)) / 45;
//      analogWrite(r_f_pwm, spd_ang);
//      analogWrite(l_b_pwm, spd_ang);
      r_f_sp = spd_ang;
      l_b_sp = spd_ang;
      if (b_angle < 315) {
//        digitalWrite(r_f_dir, LOW);
//        digitalWrite(l_b_dir, HIGH);
        r_f_d = LOW;
        l_b_d = HIGH;
      }
      else {
//        digitalWrite(r_f_dir, HIGH);
//        digitalWrite(l_b_dir, LOW);
        r_f_d = HIGH;
        l_b_d = LOW;
      }
    }
  }
  if ((cam_angle >= 105) && (cam_angle <= 270)) {
    if (l_f_d == LOW) l_f_sp = min(254, (l_f_sp + (l_f_sp * (ang_diff * 0.02))));
    else l_f_sp = max(40, (l_f_sp - (l_f_sp * (ang_diff * 0.02))));

    if (l_b_d == LOW) l_b_sp = min(254, (l_b_sp + (l_b_sp * (ang_diff * 0.02))));
    else l_b_sp = max(40, (l_b_sp - (l_b_sp * (ang_diff * 0.02))));

    if (r_f_d == LOW) r_f_sp = min(254, (r_f_sp + (r_f_sp * (ang_diff * 0.02))));
    else r_f_sp = max(40, (r_f_sp - (r_f_sp * (ang_diff * 0.02))));

    if (r_b_d == LOW) r_b_sp = min(254, (r_b_sp + (r_b_sp * (ang_diff * 0.02))));
    else r_b_sp = max(40, (r_b_sp - (r_b_sp * (ang_diff * 0.02))));
  }
  else if ((cam_angle <= 75) || (cam_angle > 270)) {
    if (l_f_d == HIGH) l_f_sp = min(254, (l_f_sp + (l_f_sp * (ang_diff * 0.02))));
    else l_f_sp = max(40, (l_f_sp - (l_f_sp * (ang_diff * 0.02))));

    if (l_b_d == HIGH) l_b_sp = min(254, (l_b_sp + (l_b_sp * (ang_diff * 0.02))));
    else l_b_sp = max(40, (l_b_sp - (l_b_sp * (ang_diff * 0.02))));

    if (r_f_d == HIGH) r_f_sp = min(254, (r_f_sp + (r_f_sp * (ang_diff * 0.02))));
    else r_f_sp = max(40, (r_f_sp - (r_f_sp * (ang_diff * 0.02))));

    if (r_b_d == HIGH) r_b_sp = min(254, (r_b_sp + (r_b_sp * (ang_diff * 0.02))));
    else r_b_sp = max(40, (r_b_sp - (r_b_sp * (ang_diff * 0.02))));
  }
  Serial.print("l_f_d = ");
  Serial.print(l_f_d);
  Serial.print("\tl_b_d = ");
  Serial.print(l_b_d);
  Serial.print("\tr_b_d = ");
  Serial.print(r_b_d);
  Serial.print("\tr_f_d = ");
  Serial.println(r_f_d);
  
  Serial.print("l_f_sp = ");
  Serial.print(l_f_sp);
  Serial.print("\tl_b_sp = ");
  Serial.print(l_b_sp);
  Serial.print("\tr_b_sp = ");
  Serial.print(r_b_sp);
  Serial.print("\tr_f_sp = ");
  Serial.println(r_f_sp);
  
  digitalWrite(l_f_dir, l_f_d);
  analogWrite(l_f_pwm, l_f_sp);
  digitalWrite(l_b_dir, l_b_d);
  analogWrite(l_b_pwm, l_b_sp);
  digitalWrite(r_f_dir, r_f_d);
  analogWrite(r_f_pwm, r_f_sp);
  digitalWrite(r_b_dir, r_b_d);
  analogWrite(r_b_pwm, r_b_sp);
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



    
