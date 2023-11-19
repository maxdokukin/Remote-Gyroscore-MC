void radioSetup()
{
  byte address[6] = {"1Node"};

  DS = true;
  LAS = false;

  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах

  radio.openWritingPipe(address);   //мы - труба 0, открываем канал для передачи данных
  radio.openReadingPipe(1, &address);      //хотим слушать трубу 0

  radio.setChannel(channel);
  radio.setPALevel (RF24_PA_MAX);
  radio.setDataRate (RF24_250KBPS);
  //radio.printDetails();  

  radio.powerUp();
  radio.startListening();

  Serial.println("RX : NRF configured");
}



void printNewData()
{
  if(data[0] == '\n' || data[0] == '\0')
    return;

  Serial.print("TX : ");
  
  for(int i = 0; data[i] && i < 64; i++)
  {
    Serial.print(char(data[i]));
  }

  Serial.println();

  newData = false;
}



void printMode()
{
  Serial.print("RX : Mode changed to : ");
  Serial.println(mod);
}



void NRFreboot()
{
  mod = pr_mod;

  DS = false;
  LAS = false;
  
  radio.stopListening();
  radio.powerDown();

  Serial.print("RX : NRF rebooting");
  delay(333);
  Serial.print('.');  
  delay(333);
  Serial.print('.');  
  delay(333);
  Serial.println('.');
  
  //softwareReboot();
  
  radio.powerUp();
  radio.startListening();
  
  Serial.println("RX : Done!");

  printMode();
}



void(* softwareReboot) (void) = 0;



void systemReboot()
{
  Serial.print("RX : Rebooting system...");
  delay(200);
  softwareReboot();
}


