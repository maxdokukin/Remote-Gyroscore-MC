void radioWrite(byte *a);
void getRFdata();
void printNewData();
boolean writeBuf(int *a);





void getRFdata()
{
  int n = 0;
  
  delay(10);
  
  if(!writeBuf(&n))
  {
    delay(50);
    writeBuf(&n);
  }

  if(data[0] == '%')
    newData = true;
  else if(data[0] == '$')
    newCmd = true;
  else
    printNewData();
}



void flushBuf(char *b)
{
  for(int i = 0; i < 32; i++)
    b[i] = 0;
}



boolean writeBuf(int *a)
{
  byte buf[32];

  boolean eof = false;
  
  flushBuf(buf);

  radio.read(buf, 32);  
  
  for(int i = 0; i < 32 && !eof; i++)
  {
    data[(*a)++] = buf[i];

    if(buf[i] == ';')
    {
      eof = true;
      data[(*a) - 1] = '\0';
    }
  }
  
  return eof;
}







byte radioRead()
{
  byte a;
  radio.read(&a, 1);
  return a;
}


