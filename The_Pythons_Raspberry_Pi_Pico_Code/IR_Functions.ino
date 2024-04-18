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
