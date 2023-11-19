void repMode()
{
  mod = pr_mod;

  if(Serial.read() == 'm')
  {
    Serial.write("$m");
  
    Serial.write(pr_mod);

    Serial.println("Mode rep");

  }

}

