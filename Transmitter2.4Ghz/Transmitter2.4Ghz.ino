#include <SPI.h>    
#include "nRF24L01.h"     
#include "RF24.h"

#include "I2Cdev.h"
#include "Wire.h"

void radioPrintln(char s[63]);
void radioSetup();
void mpuSetup();

RF24 radio(9, 10);

byte data[32];

boolean newCmd = false, newGyroData = false, TSD = false;

void setup() 
{
  Serial.begin(9600); 
  radio.begin(); 
  Wire.begin();
  
  delay(3000);
  
  radioSetup();
  mpuSetup();
  radioPrintln("Transmitter ready");
}

#include "gyro.h"
#include "system_fnc.h"

#include "data_rcv.h"
#include "data_prc.h"
#include "data_send.h"

void loop() 
{
  byte pipe;

  checkGyro();
  
  if(radio.available(&pipe)) 
    getRFdata(); 

  if(newCmd)
  {
    getCommand();
    printRcdCmd(data);
  }

  if(Serial.available()) 
  {
    if(Serial.peek() == '$')
      radioPrint("$abc;");    
    else if(Serial.peek() == '%')
      radioPrint("%abc;");  
    else
      radioPrintln("abc");  

    Serial.read();
  }
    
}









