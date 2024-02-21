void read_IR()
{
  //  ir_read_FR = analogRead(ir_FR);
  //  ir_read_RL = analogRead(ir_RL);
  //  ir_read_LR = analogRead(ir_LR);
  //  ir_read_LL = analogRead(ir_LL);
  //  ir_read_BL = analogRead(ir_BL);
  //  ir_read_BR = analogRead(ir_BR);
  //  ir_read_RR = analogRead(ir_RR);
  //  ir_read_FL = analogRead(ir_FL);
  //
  ////  if (ir_read_FR > 900 || ir_read_LL) {
  ////    forward *= -1;
  ////  }
  ////  if (ir_read_RL > 900 || ir_read_LL) {
  ////    forward *= -1;
  ////  }
  //
  //  Serial.print("IR_FR: ");
  //  Serial.print(ir_read_FR);
  //  Serial.print("\tIR_RL: ");
  //  Serial.print(ir_read_RL);
  //  Serial.print("\tIR_LR: ");
  //  Serial.print(ir_read_LR);
  //  Serial.print("\tIR_LL: ");
  //  Serial.print(ir_read_LL);
  //  Serial.print("\tIR_BL: ");
  //  Serial.print(ir_read_BL);
  //  Serial.print("\tIR_BR: ");
  //  Serial.print(ir_read_BR);
  //  Serial.print("\tIR_RR: ");
  //  Serial.print(ir_read_RR);
  //  Serial.print("\tIR_FL: ");
  //  Serial.println(ir_read_FL);

  Serial.print("RB: ");
  Serial.print(analogRead(ir_0));
//  Serial.print("\tRF: ");
//  Serial.print(analogRead(ir_1));
  Serial.print("\tBR: ");
  Serial.print(analogRead(ir_2));
//  Serial.print("\tBL: ");
//  Serial.print(analogRead(ir_3));
//  Serial.print("\tLB: ");
//  Serial.print(analogRead(ir_4));
  Serial.print("\tLF: ");
  Serial.print(analogRead(ir_5));
  Serial.print("\tFR: ");
  Serial.print(analogRead(ir_6));
//  Serial.print("\tFL: ");
//  Serial.print(analogRead(ir_7));
  Serial.println();

//    Serial.print("RB: ");
//    Serial.print(isWhite(0));
//    Serial.print("\tRF: ");
//    Serial.print(isWhite(1));
//    Serial.print("\tBR: ");
//    Serial.print(isWhite(2));
//    Serial.print("\tBL: ");
//    Serial.print(isWhite(3));
//    Serial.print("\tLB: ");
//    Serial.print(isWhite(4));
//    Serial.print("\tLF: ");
//    Serial.print(isWhite(5));
////    Serial.print("\tFR: ");
////    Serial.print(isWhite(6));
//    Serial.print("\tFL: ");
//    Serial.print(isWhite(7));
//    Serial.println();

}
//void read_IR()
//{
//  int r = analogRead(right);
//  int l = analogRead(left);
//  int f = analogRead(forwardd);
//  int b = analogRead(back);
//
//  if (f > 900 || b > 900) {
//    forward *= -1;
//  }
//  if (r > 900 || l > 900) {
//    side *= -1;
//  }
//
//  Serial.print("r: ");
//  Serial.print(r);
//  Serial.print("\tf: ");
//  Serial.print(f);
//  Serial.print("\tl: ");
//  Serial.print(l);
//  Serial.print("\tb: ");
//  Serial.println(b);
//}
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

//bool isWhite(int ir_sensor) {
//
//  //Serial.println(ir_offsets[ir_sensor][0]);
//  switch (ir_sensor) {
//    case 0:
//      if (200 > analogRead(ir_0))
//        return 1;
//      else
//        return 0;
//    case 1:
//      if (150 > analogRead(ir_1))
//        return 1;
//      else
//        return 0;
//    case 2:
//      if (100 > analogRead(ir_2))
//        return 1;
//      else
//        return 0;
//    case 3:
//      if (150 > analogRead(ir_3))
//        return 1;
//      else
//        return 0;
//    case 4:
//      if (120 > analogRead(ir_4))
//        return 1;
//      else
//        return 0;
//    case 5:
//      if (120 > analogRead(ir_5))
//        return 1;
//      else
//        return 0;
//    case 6:
//      if (150 > analogRead(ir_6))
//        return 1;
//      else
//        return 0;
//    case 7:
//      if (150 > analogRead(ir_7))
//        return 1;
//      else
//        return 0;
//
//  }
//}

void calibrate_IRs() {
  Serial.println("Starting IR Calibration");
  //  for(byte i = 0; i < 8; i++)
  //    for(byte j = 0; j < 2; j++){
  //      ir_offsets[i][j] = analogRead("ir_" + i);
  //      Serial.print("Reading: ");
  //      Serial.println(ir_offsets[i][j]);
  //    }
  ir_offsets[0][0] = analogRead(ir_0); ir_offsets[0][1] = analogRead(ir_0);
  ir_offsets[1][0] = analogRead(ir_1); ir_offsets[1][1] = analogRead(ir_1);
  ir_offsets[2][0] = analogRead(ir_2); ir_offsets[2][1] = analogRead(ir_2);
  ir_offsets[3][0] = analogRead(ir_3); ir_offsets[3][1] = analogRead(ir_3);
  ir_offsets[4][0] = analogRead(ir_4); ir_offsets[4][1] = analogRead(ir_4);
  ir_offsets[5][0] = analogRead(ir_5); ir_offsets[5][1] = analogRead(ir_5);
  ir_offsets[6][0] = analogRead(ir_6); ir_offsets[6][1] = analogRead(ir_6);
  ir_offsets[7][0] = analogRead(ir_7); ir_offsets[7][1] = analogRead(ir_7);


  timer = millis();
  while (millis() - timer < 2000) {
    forward = 0;
    side = 0;
    turn = 0;
    motioneq();
  }
  timer = millis();
  while (millis() - timer < 20000) {
    //Serial.print("Here");
    read_IR();
    forward = 0;
    side = 0;
    turn = 50;
    motioneq();
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
  Serial.print("RB min: ");
  Serial.print(ir_offsets[0][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[0][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[0][0] + (ir_offsets[0][1] - ir_offsets[0][0]) / ir_calibration_offset);
  Serial.print("\nRF: min: ");
  Serial.print(ir_offsets[1][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[1][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[1][0] + (ir_offsets[1][1] - ir_offsets[1][0]) / ir_calibration_offset);
  Serial.print("\nBR: min: ");
  Serial.print(ir_offsets[2][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[2][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[2][0] + (ir_offsets[2][1] - ir_offsets[2][0]) / ir_calibration_offset);
  Serial.print("\nBL: min: ");
  Serial.print(ir_offsets[3][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[3][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[3][0] + (ir_offsets[3][1] - ir_offsets[3][0]) / ir_calibration_offset);
  Serial.print("\nLB: min: ");
  Serial.print(ir_offsets[4][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[4][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[4][0] + (ir_offsets[4][1] - ir_offsets[4][0]) / ir_calibration_offset);
  Serial.print("\nLF: min: ");
  Serial.print(ir_offsets[5][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[5][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[5][0] + (ir_offsets[5][1] - ir_offsets[5][0]) / ir_calibration_offset);
  Serial.print("\nFR: min: ");
  Serial.print(ir_offsets[6][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[6][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[6][0] + (ir_offsets[6][1] - ir_offsets[6][0]) / ir_calibration_offset);
  Serial.print("\nFL: min: ");
  Serial.print(ir_offsets[7][0]);
  Serial.print(" max: ");
  Serial.print(ir_offsets[7][1]);
  Serial.print(" offset: ");
  Serial.print(ir_offsets[7][0] + (ir_offsets[7][1] - ir_offsets[7][0]) / ir_calibration_offset);
  Serial.println();
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
    forward = 0;
    side = 0;
    turn = 0;
    motioneq();
  }
}

bool is_line_right() {
//    Serial.print("RB: ");
//    Serial.println(analogRead(ir_0));
//    Serial.print("\tRF: ");
//    Serial.println(analogRead(ir_1));
  //  Serial.print("\tBR: ");
  //  Serial.print(isWhite(2));
  if (isWhite(0)) // || isWhite(1)
    return 1;
  else
    return 0;

}

bool is_line_left() {

  //  Serial.print("\tBL: ");
  //  Serial.print(isWhite(3));
  //  Serial.print("\tLB: ");
  //  Serial.print(isWhite(4));
  //  Serial.print("\tLF: ");
  //  Serial.print(isWhite(5));
  //  Serial.print("\tFL: ");
  //  Serial.print(isWhite(7));

  if (isWhite(5) ) //|| isWhite(5) //  || isWhite(3) || isWhite(7)
    return 1;
  else
    return 0;

}

bool is_line_front() {

  //  Serial.print("\tRF: ");
  //  Serial.print(isWhite(1));
  //  Serial.print("\tLF: ");
  //  Serial.print(isWhite(5));
  //  Serial.print("\tFR: ");
  //  Serial.print(isWhite(6));
  //  Serial.print("\tFL: ");
  //  Serial.print(isWhite(7));

  if (isWhite(6)) // isWhite(1) || isWhite(5) ||
    return 1;
  else
    return 0;

}

bool is_line_back() {
  //  Serial.print("RB: ");
  //  Serial.print(isWhite(0));
  //  Serial.print("\tBR: ");
  //  Serial.print(isWhite(2));
  //  Serial.print("\tBL: ");
  //  Serial.print(isWhite(3));
  //  Serial.print("\tLB: ");
  //  Serial.print(isWhite(4));

  if (isWhite(2)) //  || isWhite(3) //   || isWhite(0) || isWhite(4)
    return 1;
  else
    return 0;

}

void out_line() {
  if (is_line_left() && ((cam_angle >= 0 && cam_angle <= 90) || (cam_angle >= 270 && cam_angle <= 360))) {
    forward = 0;
    side = 30;//-1*side
  }
    if ((is_line_front() || (is_line_right() && is_line_left())) && (cam_angle >= 0 && cam_angle <= 180)) {
      forward = -30;
      side = 0;
    }
    if (is_line_right() && (cam_angle >= 90 && cam_angle <= 270)) {
//      timer = millis();
//      while(millis() - timer < 2000)
//      {
//        Serial.println("IN WHILE");
//         forward = 0;
//         side = -30;
//         read_Nano();
//         new_new_read_Camera();
//         motioneq();
//      }
      forward = 0;
         side = -30;
    }
  if (is_line_back() && (cam_angle >= 180 && cam_angle <= 360)) {
    forward = 30;
    side = 0;
  }
}

void new_out_line() {
  if (is_line_left() || is_line_front() || is_line_right() || is_line_back()) {
    forward = -1 * forward;
    side = -1 * side;//-1*side
  }
}

void new_new_out_line() {
  if (abs(analogRead(ir_0) - rb_last) > 70 ) {
    timer = millis();
    while(millis() - timer < 350)
    {
       forward = 0;
       side = -50;
       read_Nano();
       new_new_read_Camera();
       motioneq();
    }
  }
}
