// Left Forward --> counter-clock   LOW
// Left Back    --> counter-clock   LOW
// Right Forward --> clock          HIGH
// Right Back    --> clock          LOW
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
      digitalWrite(r_b_dir, LOW);//clock
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
      digitalWrite(r_b_dir, HIGH);
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
      digitalWrite(r_b_dir, LOW);
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
      digitalWrite(r_b_dir, HIGH);
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
      digitalWrite(r_b_dir, LOW);
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
      digitalWrite(r_b_dir, LOW);
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
      digitalWrite(r_b_dir, HIGH);
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
      digitalWrite(r_b_dir, LOW);
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
      digitalWrite(r_b_dir, LOW);
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
      digitalWrite(r_b_dir, HIGH);
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

    
