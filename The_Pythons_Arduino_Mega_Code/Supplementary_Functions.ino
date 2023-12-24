int calcPID() {
  read_Nano();
  error = setpoint - robot_heading;
  float proportional = Kp * error;
  integral += Ki * error;
  float derivative = Kd * ((error - previousError) / 0.001616);
  return abs(proportional + integral + derivative);
}

void shoot() {
//  Brushless.writeMicroseconds(1000);
//  delay(100);
//  digitalWrite(Solenoid, HIGH);
//  delay(250);
//  digitalWrite(Solenoid, LOW);
}

void turnDribbler(bool state) {
//  if (state)
//  {
//    Brushless.writeMicroseconds(1300);
//  }
//  else
//  {
//    Brushless.writeMicroseconds(1000);
//  }
}
