#include <Wire.h>

#define MPU6050_ADDR 0x68

#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48


int16_t ax, ay, az, gx, gy, gz;
float yaw;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  delay(100);
}

void loop() {
  
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(ACCEL_XOUT_H);
  Wire.write(GYRO_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 6 * 2,true); 

  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();
  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();


  Serial.print("accel X: "); Serial.print(ax); Serial.print(" ");
  Serial.print("accel Y: "); Serial.print(ay); Serial.print(" ");
  Serial.print("accel Z: "); Serial.println(az); Serial.print(" ");
  Serial.print("Gyro X: "); Serial.print(gx); Serial.print(" ");
  Serial.print("Gyro Y: "); Serial.print(gy); Serial.print(" ");
  Serial.print("Gyro Z: "); Serial.println(gz);



  const float alpha = 0.98;
  yaw = alpha * (yaw + gx * 0.017) + (1 - alpha) * atan2(ay, az) * 180 / PI;

  Serial.print("Yaw: ");Serial.println(yaw);

  delay(10);
}
