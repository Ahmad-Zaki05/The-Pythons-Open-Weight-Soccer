void read_IR()
{
  ir_read_FR = analogRead(ir_FR);
  ir_read_RL = analogRead(ir_RL);
  ir_read_LR = analogRead(ir_LR);
  ir_read_LL = analogRead(ir_LL);
  ir_read_BL = analogRead(ir_BL);
  ir_read_BR = analogRead(ir_BR);
  ir_read_RR = analogRead(ir_RR);
  ir_read_FL = analogRead(ir_FL);

  Serial.print("IR_FR: ");
  Serial.print(ir_read_FR);
  Serial.print("\tIR_RL: ");
  Serial.print(ir_read_RL);
  Serial.print("\tIR_LR: ");
  Serial.print(ir_read_LR);
  Serial.print("\tIR_LL: ");
  Serial.print(ir_read_LL);
  Serial.print("\tIR_BL: ");
  Serial.print(ir_read_BL);
  Serial.print("\tIR_BR: ");
  Serial.print(ir_read_BR);
  Serial.print("\tIR_RR: ");
  Serial.print(ir_read_RR);
  Serial.print("\tIR_FL: ");
  Serial.println(ir_read_FL);
}
