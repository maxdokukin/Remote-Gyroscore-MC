#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 10);

boolean LAS = false;
boolean DS = false; 

boolean newData = false, newCmd = false, modeChanged = false;

char pr_mod, mod = 'n';
byte data[64];

int channel = 0x60;

#include "system_cmd.h"
#include "listen_air.h"
#include "data_receive.h"
#include "data_prc.h"
#include "data_send.h"
#include "send_command.h"
#include "change_channel.h"
#include "pipe_mode.h"
#include "serial.h"


void setup() 
{
  Serial.begin(9600); //открываем порт для связи с ПК
  radio.begin(); //активировать модуль
  
  delay(3000);
  Serial.println("\nRX : Receiver ready");
  
}

void loop() 
{
  switch(mod)
  {
    case 'l':
      listenAir();
    break;
    
    case 'd':
      dataMode();
    break;

    case 'p':
      pipeMode();
    break;

    case '$':
      sendCommand();
    break;

    case 'c':
      changeChannel();
    break; 
    
    case 'r':
      NRFreboot();
    break;    

    case 'R':
      systemReboot();
    break;  
    
    case 'i':
      repMode();
    break;  

    case 'n':
    break;

    default:
      mod = pr_mod;
      Serial.println("Wrong mode !");
      printMode();
    break;
      
  }

  if(Serial.available() > 1)
    if(Serial.peek() == '$')
    {
      Serial.read();
      
      pr_mod = mod;
      mod = Serial.read();

      modeChanged = true;

      if(mod != 'i')
        printMode();
    }   
    else if(mod == 'p' && Serial.peek() == '#')
      Serial.read();   
    
    else if(mod != 'p')
      Serial.read();

}


void dataMode()
{
  byte pipe = 0;

  if(!DS)
    radioSetup();
  
  if(radio.available(&pipe))
    getRFdata();  

  if(newData)
    processData();

  if(newCmd)
    processCmd();
  
}











