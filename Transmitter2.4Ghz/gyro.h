#include <MPU6050_6Axis_MotionApps20.h>
#include "I2Cdev.h"
#include "Wire.h"

void mpuProcess();
void sendData();

MPU6050 mpu;

//system vars
long oldSendTime;
int rPackSize = 0;
int s_del = 1000;

//MPU vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high

void dmpDataReady() 
{
    mpuInterrupt = true;
}


void checkGyro()
{
  if (!dmpReady) // if programming failed, don't try to do anything
  {
    radioPrintln("Gyro ERROR!");
    return;
  }

  if(mpuInterrupt || fifoCount > packetSize) //NEW DATA FROM MPU
    mpuProcess();

  if(fifoCount > 800)
    mpu.resetFIFO();
    

  
  if(millis() - oldSendTime >= s_del && TSD) //IF IT'S TIME TO SEND DATA
  {
    Serial.println("Data sent");
    oldSendTime = millis();
    sendData();
  }
 
}





void mpuSetup()
{
  radioPrintln("MPU setup...");

  mpu.initialize();// initialize MPU

  devStatus = mpu.dmpInitialize(); // load and configure the DMP

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(0);
  mpu.setYGyroOffset(0);
  mpu.setZGyroOffset(0);
  mpu.setZAccelOffset(1012); // 1688 factory default for my test chip

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) 
  {
      mpu.setDMPEnabled(true); // turn on the DMP, now that it's ready

      attachInterrupt(0, dmpDataReady, RISING); // enable Arduino interrupt detection
      
      mpuIntStatus = mpu.getIntStatus();

      dmpReady = true; // set our DMP Ready flag so the main loop() function knows it's okay to use it

      packetSize = mpu.dmpGetFIFOPacketSize(); // get expected DMP packet size for later comparison

      radioPrintln("Gyro is ready");
  } 
}



void mpuProcess()
{  
  // reset interrupt flag and get INT_STATUS byte
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  // get current FIFO count
  fifoCount = mpu.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) 
  {
      // reset so we can continue cleanly
      mpu.resetFIFO();
      radioPrintln("FIFO overflow!");

  // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } 
  else if (mpuIntStatus & 0x02) 
  {
      // wait for correct available data length, should be a VERY short wait
      while (fifoCount < packetSize) 
        fifoCount = mpu.getFIFOCount();

      // read a packet from FIFO
      mpu.getFIFOBytes(fifoBuffer, packetSize);
      
      // track FIFO count here in case there is > 1 packet available
      // (this lets us immediately read more without waiting for an interrupt)
      fifoCount -= packetSize;

      // display Euler angles in degrees
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
   }
}

