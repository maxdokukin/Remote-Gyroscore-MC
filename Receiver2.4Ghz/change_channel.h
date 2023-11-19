byte radioRead();

void changeChannel()
{
  int ch;
  if(!DS)
    radioSetup();
    
  mod = pr_mod;

  byte swReq [5] = {"$c?.;"};
  byte resp [3];
  byte pipe, bu;

  swReq[3] = ch;
  
  radio.stopListening();
  radio.write(swReq, 5);
  radio.startListening();

  long t = millis();
  boolean wait_flag = true;
  
  while(millis() - t < 500 && wait_flag)
    if(radio.available(&pipe) >= 5 && radioRead() == '$')
    {
      for(int i = 0; radio.available(&pipe) && i < 3; i++)
        radio.read(&resp[i], 1);
        
      wait_flag= false;
    }

    
  if(wait_flag)
  {
    Serial.println("RX : Timeout!");
    printMode();
    return;
  }
  
  Serial.print("RX : Got responce : ");
  for(int i = 0; i < 3; i++)
    Serial.print(resp[i]);
    
  Serial.println();

  if(resp[0] != 'c' || resp[1] != '!' || resp[2] != ch)
  {
    Serial.println("Wrong responce from transmitter!");
    printMode();
    return;
  }
  


}
