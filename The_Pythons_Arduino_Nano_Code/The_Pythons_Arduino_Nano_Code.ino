#include "MPU9250.h"
//#include <Adafruit_SensorLab.h>
#include <math.h>
#include <Wire.h>
//#include <Adafruit_Sensor.h>


#define calib_button A2

float yaw = 0.0, gyro_yaw = 0.0, mag_heading, init_mag_heading = 0.0, init_gz = 0.0, prev_yaw = 0.0;
unsigned long long int timer;
byte read_count = 0;
//float gyroBias = 0.0;
//const float biasAlpha = 0.95;  // Bias estimation coefficient // small alpha --> more responsive // 0.65


//#define left 2
//#define right 3

MPU9250 mpu;

#define Offset 0, 0, 0, 0, 0, 0

//Adafruit_SensorLab lab;
/*
  // Hard-iron calibration settings
  const float hard_iron[3] = {
  -114.62,  129.94,  38.92
  };

  // Soft-iron calibration settings
  const float soft_iron[3][3] = {
  {  1.247,  0.060, 0.228  },
  {  0.060,  0.853, 0.178  },
  {  0.228,  0.178, 1.018  }
  };
*/

/*
  // Hard-iron calibration settings
  const float hard_iron[3] = {
  411.74,  628.58,  -633.14
  };

  // Soft-iron calibration settings
  const float soft_iron[3][3] = {
  {  1.219, -0.422, 0.376  },
  {  -0.422,  1.153, -0.178  },
  {  0.376,  -0.178, 0.933  }
  };
*/

// Hard-iron calibration settings
const float hard_iron[3] = {
  9.665,  947.2,  -1113.815
};

// Soft-iron calibration settings
const float soft_iron[3][3] = {
  {  1.00,  0.00, 0.00  },
  {  0.00,  1.00, 0.00  },
  {  0.00,  0.00, 1.00  }
};
// Magnetic declination from magnetic-declination.com
// East is positive ( ), west is negative (-)
// mag_decl = ( /-)(deg   min/60   sec/3600)
// Set to 0 to get magnetic heading instead of geo heading
const float mag_decl = 4.883; // sidi gaber

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
//  pinMode(left, OUTPUT);
//  pinMode(right, OUTPUT);

  MPU9250Setting setting;
  setting.accel_fs_sel = ACCEL_FS_SEL::A16G;//2 4 8 16
  setting.gyro_fs_sel = GYRO_FS_SEL::G2000DPS;//250 500 1000 2000
  setting.mag_output_bits = MAG_OUTPUT_BITS::M16BITS;
  setting.fifo_sample_rate = FIFO_SAMPLE_RATE::SMPL_1000HZ;//125 143 167 200 250 333 500 1000
  setting.gyro_fchoice = 0x03;
  setting.gyro_dlpf_cfg = GYRO_DLPF_CFG::DLPF_41HZ;//3600 5 10 20 41 92 184 250
  setting.accel_fchoice = 0x01;
  setting.accel_dlpf_cfg = ACCEL_DLPF_CFG::DLPF_45HZ;//420 5 10 21 45 99 218HZ_0 218HZ_1

  if (!mpu.setup(0x68, setting)) {  // change to your own address
    while (1) {
      //Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
      delay(5000);
    }
  }
  
  mpu.setGyroBias(-1.78, -0.67, -1.19);
  //  if (!mpu.setup(0x68)) {  // change to your own address
  //    while (1) {
  //      Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
  //      delay(5000);
  //    }
  //  }

  //mpu.setMagneticDeclination(4.883);//sidi gaber

  delay(1500);
  timer = millis();
  pinMode(LED_BUILTIN, OUTPUT);
//  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {


  static float hi_cal[3];

  if (read_count < 50)
    read_count += 1;

  if (mpu.update()) {

    //    // Read raw gyroscope data from MPU9250
    //    int16_t gyroX = readSensorData(GYRO_XOUT_H)
    //    // Convert raw gyroscope data to degrees per second
    //    float gyroRateX = gyroX / 131.0; // Sensitivity for full scale range of +/- 250 degrees/s




    float gyroRateZ = mpu.getGyroZ();

    // Estimate and compensate for gyro bias using EMA
    //    gyroBias = biasAlpha * gyroBias + (1 - biasAlpha) * gyroRateZ;
    //    gyroRateZ -= gyroBias;
    if (read_count >= 10 && read_count < 20)
      if (mpu.update())
        init_gz += gyroRateZ;

    if (read_count == 20) {
      init_gz /= 10;
      //Serial.print("/////////////// Initial Gyro Rate Z: ");
      //Serial.println(init_gz);
    }

    //    if (read_count == 20) {
    //      init_gz /= 10;
    //      if (mpu.update()) {
    //        init_gz = gyroRateZ;
    //        Serial.print("/////////////// Initial Gyro Rate Z: ");
    //        Serial.println(init_gz);
    //      }
    //    }

    // Subtract initial error
    if (read_count > 20)
      gyroRateZ -= init_gz;

    //    Serial.print("gyroRateZ: ");
    //    Serial.println(gyroRateZ);

    // Integrate the gyroscope readings to estimate yaw angle
    gyro_yaw += gyroRateZ * 0.01; // Integration time

    //    Serial.print("gyro_yaw: ");
    //    Serial.println(gyro_yaw);

    // Put raw magnetometer readings into an array
    float mag_data[] = {mpu.getMagX(),
                        mpu.getMagY(),
                        mpu.getMagZ()
                       };

    // Apply hard-iron offsets
    for (byte i = 0; i < 3; i++ ) {
      hi_cal[i] = mag_data[i] - hard_iron[i];
    }
    // Apply soft-iron scaling
    for (byte i = 0; i < 3; i++ ) {
      mag_data[i] = (soft_iron[i][0] * hi_cal[0]) +
                    (soft_iron[i][1] * hi_cal[1]) +
                    (soft_iron[i][2] * hi_cal[2]);
    }

    // Calculate angle for heading, assuming board is parallel to
    // the ground and  Y points toward heading.
    mag_heading = -1 * (atan2(mag_data[0], mag_data[1]) * 180) / M_PI;

    // Apply magnetic declination to convert magnetic heading
    // to geographic heading
    mag_heading += mag_decl;


    if (read_count == 20) {
      if (mpu.update()) {
        //Serial.print("/////////////// Initial mag_heading: ");
        //Serial.println(mag_heading);
        init_mag_heading = mag_heading;
      }
    }
    // Subtract initial error
    mag_heading -= init_mag_heading;



    //  // Convert heading to 0..360 degrees
    //  if (heading < 0) {
    //    heading += 360;
    //  }

    //    Serial.print("mag_heading: ");
    //    Serial.println(mag_heading);
    //Serial.print("\xC2\xB0"); //Print degree symbol


    // Apply complementary filter to combine gyroscope and magnetometer readings

    
    
    float alpha = 0.975; // Complementary filter coefficient // 0.985
    yaw = alpha * gyro_yaw + (1 - alpha) * mag_heading;

//    Serial.print(gyro_yaw);
//    Serial.print("\t");
//    Serial.print(mag_heading);
//    Serial.print("\t");
//    Serial.print(mpu.getYaw());
//    Serial.print("\t");
//    Serial.println(yaw);

    //    if(millis() - timer > 10000 && yaw > -5 && yaw < 5){
    //      timer = millis();
    //      init_mag_heading = mag_heading;
    //    }

    //    yaw += 360;
    //    yaw = (int)yaw % 360;
   

//    if(yaw > -8 && yaw < 8)
//    {
//      digitalWrite(left, LOW);
//      digitalWrite(right, LOW);
//    }
//    else
//    {
//      if(yaw < -8)
//      {
//        digitalWrite(left, HIGH);
//        digitalWrite(right, LOW);
//      }
//      else
//      {   
//        digitalWrite(left, LOW);
//        digitalWrite(right, HIGH);
//      }
//    }
    
    String yaw_str = String(yaw);
//    for (byte i = 0; i < yaw_str.length(); i++)
//    {
//      Serial.write(yaw_str.charAt(i));
//    }
//    Serial.write('\n');
    Serial.println((int)yaw);

    
    //    Serial.print("Robot_heading: ");
    //    Serial.println(yaw);

  }

  //  if (mpu.update()) {
  //    // 'Raw' values to match expectation of MOtionCal
  //    Serial.print("Raw:");
  //    Serial.print(int(0)); Serial.print(",");
  //    Serial.print(int(0)); Serial.print(",");
  //    Serial.print(int(0)); Serial.print(",");
  //    Serial.print(int(0)); Serial.print(",");
  //    Serial.print(int(0)); Serial.print(",");
  //    Serial.print(int(0)); Serial.print(",");
  //    Serial.print(int(mpu.getMagX()*10)); Serial.print(",");
  //    Serial.print(int(mpu.getMagY()*10)); Serial.print(",");
  //    Serial.print(int(mpu.getMagZ()*10)); Serial.println("");
  //
  //    // unified data
  //    Serial.print("Uni:");
  //    Serial.print(0); Serial.print(",");
  //    Serial.print(0); Serial.print(",");
  //    Serial.print(0); Serial.print(",");
  //    Serial.print(0, 4); Serial.print(",");
  //    Serial.print(0, 4); Serial.print(",");
  //    Serial.print(0, 4); Serial.print(",");
  //    Serial.print(mpu.getMagX()); Serial.print(",");
  //    Serial.print(mpu.getMagY()); Serial.print(",");
  //    Serial.print(mpu.getMagZ()); Serial.println("");
  ////     // 'Raw' values to match expectation of MOtionCal
  ////    Serial.print("Raw:");
  ////    Serial.print(int(mpu.getAccX()*8192/9.8)); Serial.print(",");
  ////    Serial.print(int(mpu.getAccY()*8192/9.8)); Serial.print(",");
  ////    Serial.print(int(mpu.getAccZ()*8192/9.8)); Serial.print(",");
  ////    Serial.print(int(mpu.getGyroX()*Adafruit_SensorLab::DEGREES_PER_RADIAN*16)); Serial.print(",");
  ////    Serial.print(int(mpu.getGyroY()*Adafruit_SensorLab::DEGREES_PER_RADIAN*16)); Serial.print(",");
  ////    Serial.print(int(mpu.getGyroZ()*Adafruit_SensorLab::DEGREES_PER_RADIAN*16)); Serial.print(",");
  ////    Serial.print(int(mpu.getMagX()*10)); Serial.print(",");
  ////    Serial.print(int(mpu.getMagY()*10)); Serial.print(",");
  ////    Serial.print(int(mpu.getMagZ()*10)); Serial.println("");
  ////
  ////    // unified data
  ////    Serial.print("Uni:");
  ////    Serial.print(mpu.getAccX()); Serial.print(",");
  ////    Serial.print(mpu.getAccY()); Serial.print(",");
  ////    Serial.print(mpu.getAccZ()); Serial.print(",");
  ////    Serial.print(mpu.getGyroX(), 4); Serial.print(",");
  ////    Serial.print(mpu.getGyroY(), 4); Serial.print(",");
  ////    Serial.print(mpu.getGyroZ(), 4); Serial.print(",");
  ////    Serial.print(mpu.getMagX()); Serial.print(",");
  ////    Serial.print(mpu.getMagY()); Serial.print(",");
  ////    Serial.print(mpu.getMagZ()); Serial.println("");
  //  }

//  if (digitalRead(calib_button)) {
//    init_mag_heading = mag_heading;
//    digitalWrite(LED_BUILTIN, HIGH);
//    //gyroRateZ
//  }
//  else {
//    digitalWrite(LED_BUILTIN, LOW);
//  }

}
