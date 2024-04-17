#include <EEPROM.h>

#define ir_0 A0 // front_right
#define ir_1 A1 // front_left
#define ir_2 A2 // near_right
#define ir_3 A3 // far_right
#define ir_4 A4 // near_left
#define ir_5 A5 // far_left
#define ir_6 A6 // near_back
#define ir_7 A7 // far_back
// Digital Pins to send signals to Raspberry Pi Pico
#define fb1 4
#define fb2 5
#define rl1 6
#define rl2 7

char fb = 0, rl = 0;
short ir_calibration_offset = 4;

#define ir_calib_button 8

int ir_offsets[8][2];

long long timer = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ir_0, INPUT);
  pinMode(ir_1, INPUT);
  pinMode(ir_2, INPUT);
  pinMode(ir_3, INPUT);
  pinMode(ir_4, INPUT);
  pinMode(ir_5, INPUT);
  pinMode(ir_6, INPUT);
  pinMode(ir_7, INPUT);

  pinMode(fb1, OUTPUT);
  pinMode(fb2, OUTPUT);
  pinMode(rl1, OUTPUT);
  pinMode(rl2, OUTPUT);

  pinMode(ir_calib_button, INPUT);

  digitalWrite(fb1, LOW);
  digitalWrite(fb2, LOW);
  digitalWrite(rl1, LOW);
  digitalWrite(rl2, LOW);

  ir_offsets[0][0] = readInt(0);
  ir_offsets[0][1] = readInt(16);
  ir_offsets[1][0] = readInt(2);
  ir_offsets[1][1] = readInt(18);
  ir_offsets[2][0] = readInt(4);
  ir_offsets[2][1] = readInt(20);
  ir_offsets[3][0] = readInt(6);
  ir_offsets[3][1] = readInt(22);
  ir_offsets[4][0] = readInt(8);
  ir_offsets[4][1] = readInt(24);
  ir_offsets[5][0] = readInt(10);
  ir_offsets[5][1] = readInt(26);
  ir_offsets[6][0] = readInt(12);
  ir_offsets[6][1] = readInt(28);
  ir_offsets[7][0] = readInt(14);
  ir_offsets[7][1] = readInt(30);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(ir_calib_button)) {
    calibrate_IRs();
  }

  is_line_right();
  is_line_left();

  if (rl == 1) {
    digitalWrite(rl1, HIGH);
    digitalWrite(rl2, LOW);
  }
  else if (rl == -1) {
    digitalWrite(rl1, LOW);
    digitalWrite(rl2, HIGH);
  }
  else {
    digitalWrite(rl1, LOW);
    digitalWrite(rl2, LOW);
  }

  is_line_front();
  is_line_back();

  if (fb == 1) {
    digitalWrite(fb1, HIGH);
    digitalWrite(fb2, LOW);
  }
  else if (fb == -1) {
    digitalWrite(fb1, LOW);
    digitalWrite(fb2, HIGH);
  }
  else {
    digitalWrite(fb1, LOW);
    digitalWrite(fb2, LOW);
  }
}
