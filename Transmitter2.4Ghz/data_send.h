void radioPrint(char s[63]);



void sendData() //DATA SEND TO PC
{    
  byte sendPack [32];

  sendPack[0] = '%';
/*
  Serial.print("z : "); 
  Serial.println(ypr[0]);
  
  Serial.print("y : "); 
  Serial.println(ypr[1]);
  
  Serial.print("x : "); 
  Serial.println(ypr[2]);
*/
  int packN = 1;
  
  for(int i = 0; i < 3; i++)
  {
    long cn = long(ypr[i] * 1000000000);

    sendPack[packN++] = cn >> 24;
    sendPack[packN++] = cn >> 16;
    sendPack[packN++] = cn >> 8;
    sendPack[packN++] = cn;
  }

  sendPack[packN++] = analogRead(7) >> 8;
  sendPack[packN++] = analogRead(7);

  sendPack[packN] = ';';
  
  radioPrint(sendPack);
}



void radioWrite(byte *a)
{    
  radio.stopListening();  
  radio.write(a, 32);
  radio.startListening();   
}



void radioPrint(char s[63])
{
  byte d[2][32];

  byte p = 0;
  
  for(int c = 0; c < 2; c++)
    for(int e = 0; e < 32 && s[p]; e++)
      d[c][e] = s[p++];

  if(p > 31)
  {
    if(p <= 63)
      d[1][p - 32] = ';';
      
    radioWrite(d[0]);
    radioWrite(d[1]);
  }
  else
  {
    d[0][p] = ';';
    
    radioWrite(d[0]);
  }
}


void radioPrintln(char s[63])
{
  radioPrint(s);

  byte a[2];
  
  a[0] = '\n';
  a[1] = ';';

  radioPrint(a);
}

