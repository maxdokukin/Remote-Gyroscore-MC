void dataMode();

boolean PMH = false;

void pipeMode()
{
  byte send_pack[32];

  if(modeChanged)
    modeChanged = false;
 
  
  if(Serial.available())
  { 
    if(Serial.peek() == '#')
    {
      mod = 'n';
      return;
    }
    
    delay(10);

    int n = 0; 

    while(Serial.available() && n < 31)
      send_pack[n++] = Serial.read();

    send_pack[n] = ';';
    
    radioWrite(send_pack);
  }

  dataMode();  
}






