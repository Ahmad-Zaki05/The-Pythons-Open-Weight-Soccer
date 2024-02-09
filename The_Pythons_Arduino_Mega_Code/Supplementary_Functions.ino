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
  turnDribbler(0);
  delay(100);
  //digitalWrite(Solenoid, HIGH);
  delay(250);
  //digitalWrite(Solenoid, LOW);
  turnDribbler(1);
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
  if (state)
  {
    dribbler.write(40);
  }
  else
  {
    dribbler.write(0);
  }
}

void writeInt(int address, int value) {
  EEPROM.update(address+sizeof(int), value);
}

int readInt(int address) {
  int valueIn = 0;
  //EEPROM.get(address+sizeof(int), valueIn);
  valueIn = EEPROM.read(address+sizeof(int));
  return valueIn;
}
