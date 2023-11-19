void radioWrite(byte *a)
{
  radio.stopListening();
  radio.write(a, 32);
  radio.startListening();
}
