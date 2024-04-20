void calibrate_IRs () {
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
  }
  
  timer = millis();
  while (millis() - timer < 5000) {
    forward = 0;
    side = 0;
    turn = 0;
    motioneq();
  }
}

bool is_line_front() {
  return (digitalRead(fb1) && !digitalRead(fb2));
}

bool is_line_back() {
  return (!digitalRead(fb1) && digitalRead(fb2));
}

bool is_line_right() {
  return (digitalRead(rl1) && !digitalRead(rl2));
}

bool is_line_left() {
  return (!digitalRead(rl1) && digitalRead(rl2));
}
