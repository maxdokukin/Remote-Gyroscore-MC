void getCommand()
{ 
  if(data[0] != '$')
  {
    newCmd = false;
    return;
  }
  
  delay(5);
  
  switch(data[1])
  {
    case 'd':
      setDelay();
    break;
    
    case 'c':
      changeChannel();
    break;

    case 'u':
      testConnection();
    break;

    case 't':
      setTime();
    break;

    case 's':
    {
      radioPrintln("Transmission started");
      TSD = true;
    }
    break;

    case 'z':
    {
      radioPrintln("Transmission stopped");
      TSD = false;
    }
    break;
    
    default:
      newCmd = false;
    break; 
  }  
}


int getNumber(char* data, int nSize)  //GET NUMBER FROM DATA 
{
  int numb = 0;
  
  for(int i = 0; i < nSize; i++)
    numb += (data[i] - 48) * pow(10, nSize - i - 1) + 0.1;

  return numb;
}
  
