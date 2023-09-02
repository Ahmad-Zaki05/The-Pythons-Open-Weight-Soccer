#include "MPU9250.h"

MPU9250 mpu;

float yaw, pitch, roll, init_yaw, init_pitch, init_roll;
unsigned long long int timer;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

    if (!mpu.setup(0x68)) {  // change address
        while (1) {
            Serial.println("MPU connection failed.");
            delay(5000);
        }
    }

    timer = millis();
    while (millis() - timer <= 3000) {
      if (mpu.update()) {
        yaw = mpu.getYaw();
        pitch = mpu.getPitch();
        roll = mpu.getRoll();
      }
    }
    
    if (mpu.update()) {
        yaw = mpu.getYaw();
        pitch = mpu.getPitch();
        roll = mpu.getRoll();
        init_yaw = yaw;
        init_pitch = pitch;
        init_roll = roll;
//        Serial.print("Initial YAW: ");
//        Serial.print(yaw);
//        Serial.print("\tInitial PITCH: ");
//        Serial.print(pitch);
//        Serial.print("\tInitial ROLL: ");
//        Serial.print(roll);  
//        Serial.println("////////////////////");
    }
    
}

void loop() {
    if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 25) {
            get_roll_pitch_yaw();
            prev_ms = millis();
        }
    }
    String yaw_str = String(yaw);
    for (int i = 0; i < yaw_str.length(); i++)
    {
      Serial.write(yaw_str.charAt(i));
    }
    Serial.write('\n');
    
}

void get_roll_pitch_yaw() {
    yaw = mpu.getYaw();
    pitch = mpu.getPitch();
    roll = mpu.getRoll();
//    Serial.print("Yaw, Pitch, Roll: ");
//    Serial.print(mpu.getYaw(), 2);
//    Serial.print(", ");
//    Serial.print(mpu.getPitch(), 2);
//    Serial.print(", ");
//    Serial.println(mpu.getRoll(), 2);

    yaw -= init_yaw;
    pitch -= init_pitch;
    roll -= init_roll;
//    Serial.print("Yaw, Pitch, Roll: ");
//    Serial.print(yaw);
//    Serial.print(", ");
//    Serial.print(pitch);
//    Serial.print(", ");
//    Serial.println(roll);
    
}
