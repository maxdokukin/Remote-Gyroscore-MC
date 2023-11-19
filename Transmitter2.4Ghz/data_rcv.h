void getRFdata()
{
    byte buf[32];

    for(int i = 0; i < 32; i++)
      buf[i] = 0;
      
    delay(5);
    radio.read(&buf, 32);  
    
    if(buf[0] == '$')
    {
      for(int i = 0; i < 32; i++)
      {
        data[i] = buf[i];

        if(buf[i] == ';')
          break;
      }
      newCmd = true;
    }
    else
      printNewData(&buf);
}
