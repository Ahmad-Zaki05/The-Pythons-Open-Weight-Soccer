void read_Camera(){
//  if (Serial3.available()) {
//    camera_char = Serial3.read();
//    Serial.print("Camera serial: ");
//    Serial.println(camera_char);
//  }

  if (Serial3.available()) {
    cam_angle_str = Serial3.readStringUntil('\n');
//    Serial.println(cam_angle_str);
    if (cam_angle_str == "S") {
      
      moveWheels('s');//stop
    }
    else {
      cam_angle = cam_angle_str.toInt();
      Serial.print("cam_angle: ");
      Serial.println(cam_angle);
      angular_Motion(cam_angle, 120);
//      if ((cam_angle >= 105) && (cam_angle <= 270)) {
//        byte rot_spd = min(254, 63.119 * exp((log(3.64285714) / 170) * (cam_angle - 90)));
////        Serial.print("cam_angle_1: ");
////        Serial.println(cam_angle);
//        digitalWrite(l_f_dir, LOW);
//        analogWrite(l_f_pwm, rot_spd);
//        digitalWrite(l_b_dir, LOW);
//        analogWrite(l_b_pwm, rot_spd);
//      
//        digitalWrite(r_f_dir, LOW);
//        analogWrite(r_f_pwm, rot_spd);
//        digitalWrite(r_b_dir, LOW);
//        analogWrite(r_b_pwm, rot_spd);
//      }
//      else if ((cam_angle <= 75) || (cam_angle > 270)) {
//        byte rot_spd;
//        Serial.println("here1");
//        if ((cam_angle >= 0) && (cam_angle <= 75)) {
//          Serial.println("here_if");
////          Serial.print("cam_angle_2: ");
////          Serial.println(cam_angle);
//          rot_spd = min(254, 63.119 * exp((log(3.64285714) / 170) * (90 - cam_angle)));
////          rot_spd = min(move_speed, 40 * (90 - cam_angle) / 10);
//        }
//        else {
//          Serial.println("here_else");
////          Serial.print("cam_angle_3: ");
////          Serial.println(cam_angle);
//          rot_spd = min(254, 63.119 * exp((log(3.64285714) / 170) * (90 + 360 - cam_angle)));
//          Serial.print("rot_spd: ");
//          Serial.println(rot_spd);
////          rot_spd = min(move_speed, 40 * (90 + 360 - cam_angle) / 10);
//        }
//        digitalWrite(l_f_dir, HIGH);
//        analogWrite(l_f_pwm, rot_spd);
//        digitalWrite(l_b_dir, HIGH);
//        analogWrite(l_b_pwm, rot_spd);
//      
//        digitalWrite(r_f_dir, HIGH);
//        analogWrite(r_f_pwm, rot_spd);
//        digitalWrite(r_b_dir, HIGH);
//        analogWrite(r_b_pwm, rot_spd);
//      }
//      else {
//        angular_Motion(cam_angle, 120);
//      }
    }
  }
}
