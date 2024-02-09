void read_Camera() {
  if (Serial2.available()) {
    //Serial.println("Receiving from camera");
    cam_angle_str = Serial2.readStringUntil('\n');
  }
  //cam_angle_str = "B90";
  //    Serial.println(cam_angle_str);
  if (cam_angle_str[0] == 'S') {
    //Serial.print("Stopppp");
    maintain_Heading();
    //      moveWheels('s', 0);
  }
  else if (cam_angle_str[0] == 'B') {
    byte sz = cam_angle_str.length();
    cam_angle = 0;
    for (byte i = 1; i < sz; i ++) {
      cam_angle = cam_angle * 10 + (cam_angle_str[i] - '0');
    }
    //Serial.println("Tracking Ball");
    //Serial.println(cam_angle);
    angular_Motion(cam_angle, 80);//80
  }
  else if (cam_angle_str[0] == 'G') {
    byte sz = cam_angle_str.length();
    cam_angle = 0;
    for (byte i = 1; i < sz; i ++) {
      cam_angle = cam_angle * 10 + (cam_angle_str[i] - '0');
    }
    //Serial.println(cam_angle);
    angular_Motion(cam_angle, 80);
    //Serial.println("Tracking Opponent Goal");
    //moveWheels(cam_angle_str[0], 0);
  }
  else if (cam_angle_str[0] == 'D') {
    for (byte i = 0, lengthh = cam_angle_str.length(); i < lengthh - 1; i++) {
      cam_angle_str[i] = cam_angle_str[i + 1];
    }
    cam_angle_str.remove(cam_angle_str.length() - 1);
    //Serial.println("Defending");
    moveWheels(cam_angle_str[0], 120);
    //maintain_Heading();
  }
  else if (cam_angle_str[0] == 'H') {
    //Serial.println("Shoot");
    moveWheels('s', 0);//stop
  }
}

void new_read_Camera() {
  if (Serial2.available()) {
    //Serial.println("Receiving from camera");
    cam_angle_str = Serial2.readStringUntil('\n');
  }
  //cam_angle_str = "B90";
  //Serial.println(cam_angle_str);
  if (cam_angle_str[0] == 'S') {

    //Serial.print("Stopppp");
    forward = 30;
    side = 0;
    //    maintain_Heading();
    //      moveWheels('s', 0);
  }
  else if (cam_angle_str[0] == 'B') {
    byte sz = cam_angle_str.length();
    cam_angle = 0;
    for (byte i = 1; i < sz; i ++) {
      cam_angle = cam_angle * 10 + (cam_angle_str[i] - '0');
    }
    //    Serial.println("Tracking Ball");
    //Serial.println(cam_angle);
    if ((cam_angle >= 0 && cam_angle <= 20) || (cam_angle <= 360 && cam_angle >= 340)) {
      side = -30;
      forward = 0;
      Serial.print("Left\n");
    }
    else if (cam_angle > 20 && cam_angle < 70) {
      side = -30;
      forward = 30;
      Serial.print("Left Forward\n");
    }
    else if (cam_angle >= 70 && cam_angle < 110) {
      forward = 30;
      side = 0;
      Serial.print("Forward\n");
    }
    else if (cam_angle >= 110 && cam_angle < 160) {
      side = 30;
      forward = 30;
      Serial.print("Right Forward\n");
    }
    else if (cam_angle >= 160 && cam_angle < 200) {
      side = 30;
      forward = 0;
      Serial.print("Right\n");
    }
    else if (cam_angle >= 200 && cam_angle < 250) {
      side = 30;
      forward = -30;
      Serial.print("Right Back\n");
    }
    else if (cam_angle >= 250 && cam_angle < 290) {
      side = 0;
      forward = -30;
      Serial.print("Back\n");
    }
    else if (cam_angle >= 290 && cam_angle < 340) {
      side = -30;
      forward = -30;
      Serial.print("Left Back\n");
    }
  }

}

void new_new_read_Camera() {
  while (Serial3.available()) {
    //Serial.println("Receiving from camera");
    cam_angle_str = Serial3.readStringUntil('\n');
  }
  //cam_angle_str = "B90";
  Serial.println(cam_angle_str);
  if (cam_angle_str[0] == 'S') { // Searching for ball

    //Serial.print("Stopppp");
    forward = 30;
    side = 0;
    //    maintain_Heading();
    //      moveWheels('s', 0);
  }
  else if (cam_angle_str[0] == 'B') { // Tracking Ball --- Sample data received "B115"
    byte sz = cam_angle_str.length();
    cam_angle = 0;
    for (byte i = 1; i < sz; i ++) {
      cam_angle = cam_angle * 10 + (cam_angle_str[i] - '0');
    }
    //    Serial.println("Tracking Ball");
    //Serial.println(cam_angle);
    forward = 50 * sin((float)cam_angle * M_PI / 180);
    side = -50 * cos((float)cam_angle * M_PI / 180);
    //Serial.print(forward);
    //Serial.print("\t");
    //Serial.println(side);
  }
  else if (cam_angle_str[0] == 'D') { // Defending goal --- Sample data received "Dss", "Ds115", "Df115", "Db115"
    byte sz = cam_angle_str.length();
    cam_angle = 0;
    side = 0;
    if (cam_angle_str[2] != 's') {
      for (byte i = 2; i < sz; i ++) {
        cam_angle = cam_angle * 10 + (cam_angle_str[i] - '0');
      }
      if (cos((float)cam_angle * M_PI / 180) < -0.1) side = 80;
      else if (cos((float)cam_angle * M_PI / 180) > 0.1) side = -80;
    }
    //    Serial.println("Tracking Ball");
    //Serial.println(cam_angle);
    //    side = -50 * cos((float)cam_angle * M_PI / 180);



    if (cam_angle_str[1] == 'f') forward = 30;
    else if (cam_angle_str[1] == 'b') forward = -30;
    else forward = 0;

    //Serial.print(forward);
    //Serial.print("\t");
    //Serial.println(side);
  }
}

void Final_read_Camera() {
  if (Serial3.available()) {
      //Serial.println("Receiving from camera");
      cam_angle = Serial3.parseInt();
      new_read_Nano();
  
      //Serial.print("Tracking Ball");
      //Serial.println(cam_angle);
      forward = 50 * sin((float)cam_angle * M_PI / 180);
      side = -50 * cos((float)cam_angle * M_PI / 180);
      //Serial.print(forward);
      //Serial.print("\t");
      //Serial.println(side);
  }
}
