/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2020 Barrett Rose

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/
/**
This sketch uses Jeff Rowberg's I2CDevLib and relies heavily on his DMP6 example sketch. Please see: 
https://github.com/jrowberg/i2cdevlib/blob/master/Arduino/MPU6050/examples/MPU6050_DMP6/MPU6050_DMP6.ino
 
*/
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "HeadMouse.h"

#define ACCELOFFSET_X -3352
#define ACCELOFFSET_Y -2937
#define ACCELOFFSET_Z 1268
#define GYROOFFSET_X -18
#define GYROOFFSET_Y -31
#define GYROOFFSET_Z 3

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  #include "Wire.h"
#endif

MPU6050 mpu;
#define OUTPUT_READABLE_YAWPITCHROLL

bool dmpReady = false;  // set true if DMP init was successful
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
bool  done=false;
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
 
void setup() {
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
  #endif

  mpu.initialize();  
  delay(1000);
  devStatus = mpu.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXAccelOffset(ACCELOFFSET_X);
  mpu.setYAccelOffset(ACCELOFFSET_Y);
  mpu.setZAccelOffset(ACCELOFFSET_Z);
  mpu.setXGyroOffset(GYROOFFSET_X);
  mpu.setYGyroOffset(GYROOFFSET_Y);
  mpu.setZGyroOffset(GYROOFFSET_Z);

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready

    mpu.setDMPEnabled(true);
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
    mpu.setZeroMotionDetectionThreshold(0 );
    mpu.setZeroMotionDetectionDuration(640000);

    delay(1000);
  } 


}

void loop() {
  // if programming failed, don't try to do anything
  if (!dmpReady) return;

  fifoCount = mpu.getFIFOCount();
  if (  fifoCount==1024){
    mpu.resetFIFO();
  } 
  else  {
    // wait for correct available data length, should be a VERY short wait
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

    // read a packet from FIFO
    mpu.getFIFOBytes(fifoBuffer, packetSize);

    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;

    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    
    HeadMouse::process(ypr);

  }

}



