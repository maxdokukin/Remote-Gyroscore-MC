void printf_begin();
void listenAirSetup();
void printNoises();
int serial_putc(char c, FILE * );
void printf_begin(void);

const uint8_t num_channels = 128;
uint8_t values[num_channels];
const int num_reps = 100;

void listenAir()
{
  radio.stopListening();
  
  if(!LAS)
    listenAirSetup();

  printNoises();
}



void listenAirSetup()
{
  DS = false;
  LAS = true;
  
  printf_begin();
  radio.setDataRate (RF24_1MBPS);

  radio.printDetails();  
  delay(1000); 
  
  int i = 0;   
  
  while ( i < num_channels )  
  {
    printf("%x",i>>4);
    ++i;
  }
  
  printf("\n\r");
  
  i = 0;
  
  while ( i < num_channels ) 
  {
    printf("%x",i&0xf);
    ++i;
  }
  
  printf("\n\r");
}



void printNoises()
{
  memset(values,0,sizeof(values));
  
  int rep_counter = num_reps;
  
  while (rep_counter--) 
  {
    int i = num_channels;
    
    while (i--) 
    {
      radio.setChannel(i);
      radio.startListening();
      delayMicroseconds(128);
      radio.stopListening();
      
      if ( radio.testCarrier() )
        ++values[i];
    }
  }
  
  int i = 0;
  
  while ( i < num_channels ) 
  {
    printf("%x",min(0xf,values[i]&0xf));
    ++i;
  }
  
  printf("\n");
}



int serial_putc( char c, FILE * ) 
{
  Serial.write( c );
  return c;
}



void printf_begin(void) 
{
  fdevopen( &serial_putc, 0 );
}


