void printMode();
void radioWrite(byte *a);

void sendCommand()
{
  mod = pr_mod;
  
  byte command [32];

  int p = 0;
  
  command[p++] = '$';

  long t = millis();
  
  while(Serial.peek() != ';' && p < 31 && millis() - t < 35)
    if(Serial.available())
      command[p++] = Serial.read();

  command[p++] = ';';

  radioWrite(command);
 
  printMode();
}
