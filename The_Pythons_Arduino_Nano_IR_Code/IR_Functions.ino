void display_IRs () {
  Serial.print(analogRead(ir_0));
  Serial.print("\t");
  Serial.print(analogRead(ir_1));
  Serial.print("\t");
  Serial.print(analogRead(ir_2));
  Serial.print("\t");
  Serial.print(analogRead(ir_3));
  Serial.print("\t");
  Serial.print(analogRead(ir_4));
  Serial.print("\t");
  Serial.print(analogRead(ir_5));
  Serial.print("\t");
  Serial.print(analogRead(ir_6));
  Serial.print("\t");
  Serial.print(analogRead(ir_7));
  Serial.print("\n");
}

void calibrate_IRs() {
  Serial.println("Starting IR Calibration");
  // This is the signal for starting calibration
  digitalWrite(fb1, HIGH);
  digitalWrite(fb2, HIGH);
  digitalWrite(rl1, HIGH);
  digitalWrite(rl2, HIGH);

  timer = millis();
  while (millis() - timer < 2000) {

  }
  // initial readings
  ir_offsets[0][0] = analogRead(ir_0); ir_offsets[0][1] = analogRead(ir_0);
  ir_offsets[1][0] = analogRead(ir_1); ir_offsets[1][1] = analogRead(ir_1);
  ir_offsets[2][0] = analogRead(ir_2); ir_offsets[2][1] = analogRead(ir_2);
  ir_offsets[3][0] = analogRead(ir_3); ir_offsets[3][1] = analogRead(ir_3);
  ir_offsets[4][0] = analogRead(ir_4); ir_offsets[4][1] = analogRead(ir_4);
  ir_offsets[5][0] = analogRead(ir_5); ir_offsets[5][1] = analogRead(ir_5);
  ir_offsets[6][0] = analogRead(ir_6); ir_offsets[6][1] = analogRead(ir_6);
  ir_offsets[7][0] = analogRead(ir_7); ir_offsets[7][1] = analogRead(ir_7);

  timer = millis();
  while (millis() - timer < 20000) {
    //Serial.print("Here");
    display_IRs();
    if (ir_offsets[0][0] > analogRead(ir_0))
      ir_offsets[0][0] = analogRead(ir_0);
    if (ir_offsets[0][1] < analogRead(ir_0))
      ir_offsets[0][1] = analogRead(ir_0);

    if (ir_offsets[1][0] > analogRead(ir_1))
      ir_offsets[1][0] = analogRead(ir_1);
    if (ir_offsets[1][1] < analogRead(ir_1))
      ir_offsets[1][1] = analogRead(ir_1);

    if (ir_offsets[2][0] > analogRead(ir_2))
      ir_offsets[2][0] = analogRead(ir_2);
    if (ir_offsets[2][1] < analogRead(ir_2))
      ir_offsets[2][1] = analogRead(ir_2);

    if (ir_offsets[3][0] > analogRead(ir_3))
      ir_offsets[3][0] = analogRead(ir_3);
    if (ir_offsets[3][1] < analogRead(ir_3))
      ir_offsets[3][1] = analogRead(ir_3);

    if (ir_offsets[4][0] > analogRead(ir_4))
      ir_offsets[4][0] = analogRead(ir_4);
    if (ir_offsets[4][1] < analogRead(ir_4))
      ir_offsets[4][1] = analogRead(ir_4);

    if (ir_offsets[5][0] > analogRead(ir_5))
      ir_offsets[5][0] = analogRead(ir_5);
    if (ir_offsets[5][1] < analogRead(ir_5))
      ir_offsets[5][1] = analogRead(ir_5);

    if (ir_offsets[6][0] > analogRead(ir_6))
      ir_offsets[6][0] = analogRead(ir_6);
    if (ir_offsets[6][1] < analogRead(ir_6))
      ir_offsets[6][1] = analogRead(ir_6);

    if (ir_offsets[7][0] > analogRead(ir_7))
      ir_offsets[7][0] = analogRead(ir_7);
    if (ir_offsets[7][1] < analogRead(ir_7))
      ir_offsets[7][1] = analogRead(ir_7);

    //        if(ir_offsets[i][0] > analogRead("ir_" + i))
    //          ir_offsets[i][0] = analogRead("ir_" + i);
    //        if(ir_offsets[i][1] < analogRead("ir_" + i))
    //          ir_offsets[i][1] = analogRead("ir_" + i);
  }

  Serial.print("Front Right min: ");
  Serial.print(ir_offsets[0][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[0][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[0][0] + (ir_offsets[0][1] - ir_offsets[0][0]) / ir_calibration_offset);
  Serial.print("\nFront Left: min: ");
  Serial.print(ir_offsets[1][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[1][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[1][0] + (ir_offsets[1][1] - ir_offsets[1][0]) / ir_calibration_offset);
  Serial.print("\nNear Right: min: ");
  Serial.print(ir_offsets[2][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[2][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[2][0] + (ir_offsets[2][1] - ir_offsets[2][0]) / ir_calibration_offset);
  Serial.print("\nFar Right: min: ");
  Serial.print(ir_offsets[3][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[3][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[3][0] + (ir_offsets[3][1] - ir_offsets[3][0]) / ir_calibration_offset);
  Serial.print("\nNear Left: min: ");
  Serial.print(ir_offsets[4][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[4][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[4][0] + (ir_offsets[4][1] - ir_offsets[4][0]) / ir_calibration_offset);
  Serial.print("\nFar Left: min: ");
  Serial.print(ir_offsets[5][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[5][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[5][0] + (ir_offsets[5][1] - ir_offsets[5][0]) / ir_calibration_offset);
  Serial.print("\nNear Back: min: ");
  Serial.print(ir_offsets[6][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[6][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[6][0] + (ir_offsets[6][1] - ir_offsets[6][0]) / ir_calibration_offset);
  Serial.print("\nFar Back: min: ");
  Serial.print(ir_offsets[7][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[7][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[7][0] + (ir_offsets[7][1] - ir_offsets[7][0]) / ir_calibration_offset);
  Serial.print("\n");
  //  writeInt(0, ir_offsets[0][0]);
  //  writeInt(1, ir_offsets[0][1]);
  //  writeInt(2, ir_offsets[1]u[0]);
  //  writeInt(3, ir_offsets[1][1]);
  //  writeInt(4, ir_offsets[2][0]);
  //  writeInt(5, ir_offsets[2][1]);
  //  writeInt(6, ir_offsets[3][0]);
  //  writeInt(7, ir_offsets[3][1]);
  //  writeInt(8, ir_offsets[4][0]);
  //  writeInt(9, ir_offsets[4][1]);
  //  writeInt(10, ir_offsets[5][0]);
  //  writeInt(11, ir_offsets[5][1]);
  //  writeInt(12, ir_offsets[6][0]);
  //  writeInt(13, ir_offsets[6][1]);
  //  writeInt(14, ir_offsets[7][0]);
  //  writeInt(15, ir_offsets[7][1]);

  writeInt(0, ir_offsets[0][0]);
  writeInt(16, ir_offsets[0][1]);
  writeInt(2, ir_offsets[1][0]);
  writeInt(18, ir_offsets[1][1]);
  writeInt(4, ir_offsets[2][0]);
  writeInt(20, ir_offsets[2][1]);
  writeInt(6, ir_offsets[3][0]);
  writeInt(22, ir_offsets[3][1]);
  writeInt(8, ir_offsets[4][0]);
  writeInt(24, ir_offsets[4][1]);
  writeInt(10, ir_offsets[5][0]);
  writeInt(26, ir_offsets[5][1]);
  writeInt(12, ir_offsets[6][0]);
  writeInt(28, ir_offsets[6][1]);
  writeInt(14, ir_offsets[7][0]);
  writeInt(30, ir_offsets[7][1]);

  timer = millis();
  while (millis() - timer < 5000) {

  }

  digitalWrite(fb1, LOW);
  digitalWrite(fb2, LOW);
  digitalWrite(rl1, LOW);
  digitalWrite(rl2, LOW);
}

bool isWhite(int ir_sensor) {

  //Serial.println(ir_offsets[ir_sensor][0]);
  switch (ir_sensor) {
    case 0:
      if (ir_offsets[ir_sensor][0] + (ir_offsets[ir_sensor][1] - ir_offsets[ir_sensor][0]) / ir_calibration_offset > analogRead(ir_0))
        return 1;
      else
        return 0;
    case 1:
      if (ir_offsets[ir_sensor][0] + (ir_offsets[ir_sensor][1] - ir_offsets[ir_sensor][0]) / ir_calibration_offset > analogRead(ir_1))
        return 1;
      else
        return 0;
    case 2:
      if (ir_offsets[ir_sensor][0] + (ir_offsets[ir_sensor][1] - ir_offsets[ir_sensor][0]) / ir_calibration_offset > analogRead(ir_2))
        return 1;
      else
        return 0;
    case 3:
      if (ir_offsets[ir_sensor][0] + (ir_offsets[ir_sensor][1] - ir_offsets[ir_sensor][0]) / ir_calibration_offset > analogRead(ir_3))
        return 1;
      else
        return 0;
    case 4:
      if (ir_offsets[ir_sensor][0] + (ir_offsets[ir_sensor][1] - ir_offsets[ir_sensor][0]) / ir_calibration_offset > analogRead(ir_4))
        return 1;
      else
        return 0;
    case 5:
      if (ir_offsets[ir_sensor][0] + (ir_offsets[ir_sensor][1] - ir_offsets[ir_sensor][0]) / ir_calibration_offset > analogRead(ir_5))
        return 1;
      else
        return 0;
    case 6:
      if (ir_offsets[ir_sensor][0] + (ir_offsets[ir_sensor][1] - ir_offsets[ir_sensor][0]) / ir_calibration_offset > analogRead(ir_6))
        return 1;
      else
        return 0;
    case 7:
      if (ir_offsets[ir_sensor][0] + (ir_offsets[ir_sensor][1] - ir_offsets[ir_sensor][0]) / ir_calibration_offset > analogRead(ir_7))
        return 1;
      else
        return 0;

  }
}

void is_line_right() {
  if (isWhite(2) || isWhite(3)) rl = 1;
  else rl = 0;
}

void is_line_left() {
  if (isWhite(4) || isWhite(5)) rl = -1;
}

void is_line_front() {
  if (isWhite(0) || isWhite(1)) fb = 1;
  else fb = 0;
}

void is_line_back() {
  if (isWhite(6) || isWhite(7)) fb = -1;
}
