void read_Camera() {
  if (Serial3.available()) {
    Serial.println("Receiving from camera");
    cam_angle_str = Serial3.readStringUntil('\n');
  }
  //cam_angle_str = "B90";
  //    Serial.println(cam_angle_str);
  if (cam_angle_str[0] == 'S') {
    Serial.print("Stopppp");
    maintain_Heading();
    //      moveWheels('s', 0);
  }
  else if (cam_angle_str[0] == 'B') {
    byte sz = cam_angle_str.length();
    cam_angle = 0;
    for (byte i = 1; i < sz; i ++) {
      cam_angle = cam_angle * 10 + (cam_angle_str[i] - '0');
    }
    Serial.println("Tracking Ball");
    Serial.println(cam_angle);
    angular_Motion(cam_angle, 80);//80
  }
  else if (cam_angle_str[0] == 'G') {
    byte sz = cam_angle_str.length();
    cam_angle = 0;
    for (byte i = 1; i < sz; i ++) {
      cam_angle = cam_angle * 10 + (cam_angle_str[i] - '0');
    }
    Serial.println(cam_angle);
    angular_Motion(cam_angle, 80);
    Serial.println("Tracking Opponent Goal");
    //moveWheels(cam_angle_str[0], 0);
  }
  else if (cam_angle_str[0] == 'D') {
    for (byte i = 0, lengthh = cam_angle_str.length(); i < lengthh - 1; i++) {
      cam_angle_str[i] = cam_angle_str[i + 1];
    }
    cam_angle_str.remove(cam_angle_str.length() - 1);
    Serial.println("Defending");
    moveWheels(cam_angle_str[0], 120);
    //maintain_Heading();
  }
  else if (cam_angle_str[0] == 'H') {
    Serial.println("Shoot");
    moveWheels('s', 0);//stop
  }
}
