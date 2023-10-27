void read_Camera(){
//  if (Serial3.available()) {
//    camera_char = Serial3.read();
//    Serial.print("Camera serial: ");
//    Serial.println(camera_char);
//  }

  if (Serial3.available()) {
    cam_angle_str = Serial3.readStringUntil('\n');
//    Serial.println(cam_angle_str);
    if(cam_angle_str[0] == 'S'){
        moveWheels('s', 0);
      }
    else if(cam_angle_str[0] == 'B'){
      for (int i = 0; i < cam_angle_str.length() - 1; i++) {
        cam_angle_str[i] = cam_angle_str[i + 1];}
      cam_angle_str.remove(cam_angle_str.length() - 1);
      cam_angle = cam_angle_str.toInt();
      Serial.println("Tracking Ball");
      Serial.println(cam_angle);
      angular_Motion(cam_angle, 120);
    }
    else if(cam_angle_str[0] == 'G'){
      for (int i = 0; i < cam_angle_str.length() - 1; i++) {
        cam_angle_str[i] = cam_angle_str[i + 1];}
      cam_angle_str.remove(cam_angle_str.length() - 1);
      Serial.println("Tracking Opponent Goal");
      //moveWheels(cam_angle_str[0], 0);
    }
    else if(cam_angle_str[0] == 'D'){
      for (int i = 0; i < cam_angle_str.length() - 1; i++) {
        cam_angle_str[i] = cam_angle_str[i + 1];}
      cam_angle_str.remove(cam_angle_str.length() - 1);
      Serial.println("Defending");
      moveWheels(cam_angle_str[0], 120);
      //maintain_Heading();
    }
  }
//  else {
//    digitalWrite(l_f_dir, LOW);
//      analogWrite(l_f_pwm, 0);
//      digitalWrite(l_b_dir, LOW);
//      analogWrite(l_b_pwm, 0);
//    
//      digitalWrite(r_f_dir, LOW);
//      analogWrite(r_f_pwm, 0);
//      digitalWrite(r_b_dir, LOW);
//      analogWrite(r_b_pwm, 0);
//
//      Serial.println("I am in the else");
//  }
}
