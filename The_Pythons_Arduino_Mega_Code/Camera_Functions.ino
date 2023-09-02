void read_Camera(){
//  if (Serial3.available()) {
//    camera_char = Serial3.read();
//    Serial.print("Camera serial: ");
//    Serial.println(camera_char);
//  }

  if (Serial3.available()) {
    cam_angle_str = Serial3.readStringUntil('\n');
    Serial.println(cam_angle_str);
    if (cam_angle_str == "S") {
      
      angular_Motion(0, 0);
    }
    else {
      cam_angle = cam_angle_str.toInt();
      angular_Motion(cam_angle, 50);
    }
  }
}
