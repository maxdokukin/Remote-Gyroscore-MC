int getNumber(char* data, int nSize);

void setDelay()
{
  radioPrintln("Setting delay...");

  int n = 0; 

  while(data[n++] != ';' && n < 32);

  n -= 3;
  
  s_del = getNumber(data + 2, n);

  radioPrintln("Delay set!");
}

void changeChannel()
{
  radioPrintln("Changing channel...");
  
}

void testConnection()
{
  radioPrintln("Testing connection...");
}

void setTime()
{
  radioPrintln("Setting time...");
}

int getChannel()
{
  return(0x60);
  //add eeprom read
}



void printNewData(byte b[][32])
{
  Serial.print("New data : ");

  for(int i = 0; (*b)[i] != ';' && i < 32; i++)
    Serial.print(char((*b)[i]));

  Serial.println();
}


void printRcdCmd(byte b[32])
{
  Serial.print("New cmd : ");

  for(int i = 0; b[i] != ';' && i < 32; i++)
    Serial.print(char(b[i]));

  Serial.println();

  newCmd = false;
}



void radioSetup()
{
  byte address[6] = {"1Node"};

  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах

  radio.openWritingPipe(address);   //мы - труба 0, открываем канал для передачи данных
  radio.openReadingPipe(1, &address);      //хотим слушать трубу 0

  radio.setChannel(getChannel());
  radio.setPALevel (RF24_PA_MAX);
  radio.setDataRate (RF24_250KBPS);

  radio.powerUp();
  radio.startListening();
}


