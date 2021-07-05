void setup()
{
  DDRD = B11111111;

}

void loop()
{
  PORTD = B01000001;
  delay(1000);
  PORTD = B01000101;
  delay(1000);
  PORTD = B01010011;
  delay(1000);
}