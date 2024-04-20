void read_Camera() {
  while (Serial2.available()) {
    //Serial.println("Receiving from camera");
    cam_angle_str = Serial2.readStringUntil('\n');
  }
  //cam_angle_str = "B90";
  Serial.println(cam_angle_str);

  if (cam_angle_str[0] == 'S') { // Searching for ball

    //Serial.print("Stopppp");

    if (seeking) {
      forward = 55;
      side = 0;
    }
    else {
      forward = -50;
      side = 0;
    }
    if (is_line_front()) {
      //seeking = 0;
      ir_counter_b = 0;
      ir_counter_f ++;
    }
    else
    {
      ir_counter_f = 0;
    }
    if (is_line_back()) {
      //seeking = 1;
      ir_counter_f = 0;
      ir_counter_b ++;
    }
    else {
      ir_counter_b = 0;
    }
    if(ir_counter_b > 24)
    {
      seeking = 1;
    }
    if(ir_counter_f > 24)
    {
      seeking = 0;
    }

    //    maintain_Heading();
    //      moveWheels('s', 0);
  }
  else if (cam_angle_str[0] == 'B') { // Tracking Ball --- Sample data received "B115"
    seeking = 1;
    ir_counter_b = 0;
    ir_counter_f = 0;
    byte sz = cam_angle_str.length();
    cam_angle = 0;
    for (byte i = 1; i < sz; i ++) {
      cam_angle = cam_angle * 10 + (cam_angle_str[i] - '0');
    }
    //    Serial.println("Tracking Ball");
    //Serial.println(cam_angle);
    forward = 60 * sin((float)cam_angle * M_PI / 180);
    side = -60 * cos((float)cam_angle * M_PI / 180);
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
