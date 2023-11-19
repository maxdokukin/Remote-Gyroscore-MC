void processData()
{
  Serial.println("RX : New data :");

  for(int i = 0; i < 32; i++)
    if(data[i] == '%' || data[i] == ';')
      Serial.write(char(data[i]));
    else
      Serial.write(byte(data[i]));

  
  Serial.println();
  
  newData = false;
}


void processCmd()
{
  Serial.println("RX : New cmd");

  newCmd = false;
}

