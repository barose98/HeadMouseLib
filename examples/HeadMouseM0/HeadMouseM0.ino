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
//HeadMouse headmouse;
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

    //      mpu.setIntDMPEnabled(false);
    delay(1000);
  } 
/*  else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
        digitalWrite(LEDPIN, HIGH);        
        delay(10000);             
        digitalWrite(LEDPIN, LOW);  
  }
*/

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



