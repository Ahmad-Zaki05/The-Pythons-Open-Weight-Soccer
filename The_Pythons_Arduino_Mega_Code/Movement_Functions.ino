// jp2 --> left, jp1 --> right
// Left Forward --> counter-clock   LOW
// Left Back    --> counter-clock   LOW
// Right Forward --> clock          HIGH
// Right Back    --> clock          HIGH
void moveWheels(char dir, byte move_speed) {
  switch (dir) {
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

void angular_Motion(short b_angle, short spd) {
  call_ang = true;

  short r_f_sp, r_b_sp, l_f_sp, l_b_sp, ang_diff;
  bool r_f_d, r_b_d, l_f_d, l_b_d;

  if ((b_angle >= 0) && (b_angle <= 90)) {
    ang_diff = (90 - b_angle);
    r_f_d = HIGH;
    r_f_sp = spd;
    l_b_d = LOW;
    l_b_sp = spd;
    if (b_angle == 45) {
      l_f_sp = 0;
      r_b_sp = 0;
    }
    else {
      byte spd_ang = (spd * abs(b_angle - 45)) / 45;
      l_f_sp = spd_ang;
      r_b_sp = spd_ang;
      if (b_angle < 45) {
        l_f_d = HIGH;
        r_b_d = LOW;
      }
      else {
        l_f_d = LOW;
        r_b_d = HIGH;
      }
    }
  }
  else if ((b_angle >= 90) && (b_angle <= 180)) {
    ang_diff = (b_angle - 90);
    r_b_d = HIGH;
    r_b_sp = spd;
    l_f_d = LOW;
    l_f_sp = spd;
    if (b_angle == 135) {
      r_f_sp = 0;
      l_b_sp = 0;
    }
    else {
      byte spd_ang = (spd * abs(b_angle - 135)) / 45;
      r_f_sp = spd_ang;
      l_b_sp = spd_ang;
      if (b_angle < 135) {
        r_f_d = HIGH;
        l_b_d = LOW;
      }
      else {
        r_f_d = LOW;
        l_b_d = HIGH;
      }
    }
  }
  else if ((b_angle >= 180) && (b_angle <= 270)) {
    ang_diff = (b_angle - 90);
    r_f_d = LOW;
    r_f_sp = spd;
    l_b_d = HIGH;
    l_b_sp = spd;
    if (b_angle == 225) {
      l_f_sp = 0;
      r_b_sp = 0;
    }
    else {
      byte spd_ang = (spd * abs(b_angle - 225)) / 45;
      l_f_sp = spd_ang;
      r_b_sp = spd_ang;
      if (b_angle < 225) {
        l_f_d = LOW;
        r_b_d = HIGH;
      }
      else {
        l_f_d = HIGH;
        r_b_d = LOW;
      }
    }
  }
  else if ((b_angle >= 270) && (b_angle <= 360)) {
    ang_diff = (360 - b_angle + 90);
    r_b_d = LOW;
    r_b_sp = spd;
    l_f_d = HIGH;
    l_f_sp = spd;
    if (b_angle == 315) {
      r_f_sp = 0;
      l_b_sp = 0;
    }
    else {
      byte spd_ang = (spd * abs(b_angle - 315)) / 45;
      r_f_sp = spd_ang;
      l_b_sp = spd_ang;
      if (b_angle < 315) {
        r_f_d = LOW;
        l_b_d = HIGH;
      }
      else {
        r_f_d = HIGH;
        l_b_d = LOW;
      }
    }
  }

  read_Nano();

  float headCorr = abs(setpoint - robot_heading) * 0.02;

  error = setpoint - robot_heading;

  //  if (error < -8) { // 5 degrees right
  //    //    increase the speed of motors turning in the same direction as moving left
  //    if (l_f_d) l_f_sp += (int) (spd / 2);
  //    else l_f_sp -= (int) (spd / 3.2);
  //    if (l_b_d) l_b_sp += (int) (spd / 2);
  //    else l_b_sp -= (int) (spd / 3.2);
  //    if (r_f_d) r_f_sp += (int) (spd / 2);
  //    else r_f_sp -= (int) (spd / 3.2);
  //    if (r_b_d) r_b_sp += (int) (spd / 2);
  //    else r_b_sp -= (int) (spd / 3.2);
  //  }
  //  else if (error > 8) {
  //    if (!l_f_d) l_f_sp += (int) (spd / 2);
  //    else l_f_sp -= (int) (spd / 3.2);
  //    if (!l_b_d) l_b_sp += (int) (spd / 2);
  //    else l_b_sp -= (int) (spd / 3.2);
  //    if (!r_f_d) r_f_sp += (int) (spd / 2);
  //    else r_f_sp -= (int) (spd / 3.2);
  //    if (!r_b_d) r_b_sp += (int) (spd / 2);
  //    else r_b_sp -= (int) (spd / 3.2);
  //  }

  //  if (error < -8) { // 5 degrees right
  //    //    increase the speed of motors turning in the same direction as moving left
  //    if (l_f_d) l_f_sp += (int) (spd * headCorr);
  //    else l_f_sp -= (int) (spd * headCorr);
  //    if (l_b_d) l_b_sp += (int) (spd * headCorr);
  //    else l_b_sp -= (int) (spd * headCorr);
  //    if (r_f_d) r_f_sp += (int) (spd * headCorr);
  //    else r_f_sp -= (int) (spd * headCorr);
  //    if (r_b_d) r_b_sp += (int) (spd * headCorr);
  //    else r_b_sp -= (int) (spd * headCorr);
  //  }
  //  else if (error > 8) {
  //    if (!l_f_d) l_f_sp += (int) (spd * headCorr);
  //    else l_f_sp -= (int) (spd * headCorr);
  //    if (!l_b_d) l_b_sp += (int) (spd * headCorr);
  //    else l_b_sp -= (int) (spd * headCorr);
  //    if (!r_f_d) r_f_sp += (int) (spd * headCorr);
  //    else r_f_sp -= (int) (spd * headCorr);
  //    if (!r_b_d) r_b_sp += (int) (spd * headCorr);
  //    else r_b_sp -= (int) (spd * headCorr);
  //  }


  if (error < -8) { // 5 degrees right
    //    increase the speed of motors turning in the same direction as moving left
    if (l_f_d) l_f_sp += (int) (l_f_sp * headCorr);
    else l_f_sp -= (int) (l_f_sp * headCorr);
    if (l_b_d) l_b_sp += (int) (l_b_sp * headCorr);
    else l_b_sp -= (int) (l_b_sp * headCorr);
    if (r_f_d) r_f_sp += (int) (r_f_sp * headCorr);
    else r_f_sp -= (int) (r_f_sp * headCorr);
    if (r_b_d) r_b_sp += (int) (r_b_sp * headCorr);
    else r_b_sp -= (int) (r_b_sp * headCorr);
  }
  else if (error > 8) {
    if (!l_f_d) l_f_sp += (int) (l_f_sp * headCorr);
    else l_f_sp -= (int) (l_f_sp * headCorr);
    if (!l_b_d) l_b_sp += (int) (l_b_sp * headCorr);
    else l_b_sp -= (int) (l_b_sp * headCorr);
    if (!r_f_d) r_f_sp += (int) (r_f_sp * headCorr);
    else r_f_sp -= (int) (r_f_sp * headCorr);
    if (!r_b_d) r_b_sp += (int) (r_b_sp * headCorr);
    else r_b_sp -= (int) (r_b_sp * headCorr);
  }


  //  Serial.print("l_f_d = ");
  //  Serial.print(l_f_d);
  //  Serial.print("\tl_b_d = ");
  //  Serial.print(l_b_d);
  //  Serial.print("\tr_b_d = ");
  //  Serial.print(r_b_d);
  //  Serial.print("\tr_f_d = ");
  //  Serial.println(r_f_d);
  //
  //  Serial.print("l_f_sp = ");
  //  Serial.print(l_f_sp);
  //  Serial.print("\tl_b_sp = ");
  //  Serial.print(l_b_sp);
  //  Serial.print("\tr_b_sp = ");
  //  Serial.print(r_b_sp);
  //  Serial.print("\tr_f_sp = ");
  //  Serial.println(r_f_sp);

  digitalWrite(l_f_dir, l_f_d);
  analogWrite(l_f_pwm, min(250, max(0, l_f_sp)));
  digitalWrite(l_b_dir, l_b_d);
  analogWrite(l_b_pwm, min(250, max(0, l_b_sp)));
  digitalWrite(r_f_dir, r_f_d);
  analogWrite(r_f_pwm, min(250, max(0, r_f_sp)));
  digitalWrite(r_b_dir, r_b_d);
  analogWrite(r_b_pwm, min(250, max(0, r_b_sp)));
}

void maintain_Heading() {
  read_Nano();
  error = setpoint - robot_heading;
  //  if (!call_ang) {
  if (robot_heading > 8) {
    moveWheels('n', 45);//rotate left
  }
  else if (robot_heading < -8) {
    moveWheels('m', 45);//rotate right
  }
  else
  {
    moveWheels('s', 0);//stop
  }
  //  }

  //  float PID_corr = calcPID();
  //
  //  if(error > 5)
  //    moveWheels('m', max(40,PID_corr+40));//rotate right
  //  else if(error < -5)
  //    moveWheels('n', max(40,PID_corr+40));//rotate left
  //
  //  previousError = error;

}
