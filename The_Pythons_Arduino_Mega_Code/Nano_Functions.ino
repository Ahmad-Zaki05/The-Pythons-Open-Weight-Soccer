void read_Nano() {
  //  robot_heading = 0;
  if (Serial1.available())
  {
    received_imu_angle = Serial1.readStringUntil('\n');
    robot_heading = received_imu_angle.toInt();
    Serial.print("Robot heading: ");
    Serial.println(robot_heading);
    float headCorr = abs(setpoint - robot_heading) * 0.02 * 100;
    if (robot_heading < 8 && robot_heading > -8) {
//      digitalWrite(13, HIGH);
      //      Serial.println("LED ON");
      turn = 0;
    }
    else {
      if (robot_heading < -8)
        turn = -headCorr;//-30
      else
        turn = headCorr;//30
//      digitalWrite(13, LOW);
      //      Serial.println("LED OFF");
    }


  }
}
void new_read_Nano() {
  //  robot_heading = 0;
  //Serial.println(Serial1.available());
  if (Serial1.available() > 0)
  {
    //received_imu_angle = Serial1.readStringUntil('\n');
    //robot_heading = received_imu_angle.toInt();
    robot_heading = Serial1.parseInt();
    //Serial.println("fsbkfsbf");
  }
    Serial.print("Robot heading: ");
    Serial.println(robot_heading);
    float headCorr = abs(setpoint - robot_heading) * 0.02 * 100;
    if (robot_heading < 8 && robot_heading > -8) {
//      digitalWrite(13, HIGH);
      //      Serial.println("LED ON");
      turn = 0;
    }
    else {
      if (robot_heading < -8)
        turn = -headCorr;//-30
      else
        turn = headCorr;//30
//      digitalWrite(13, LOW);
      //      Serial.println("LED OFF");
    }


}

void new_read_nano()
{
  if(digitalRead(20))
    turn = 30;
  if(digitalRead(21))
    turn = -30;
  if((digitalRead(21) == 0 && digitalRead(20) == 0) || (digitalRead(21) == 1 && digitalRead(20) == 1))
    turn = 0;
//  Serial.print(digitalRead(21));
//  Serial.print(" ");
//  Serial.println(digitalRead(20));
}
