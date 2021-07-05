int counter = 0;

void setup()
{
  DDRD = B11111111;
}

void loop()
{
  PORTD = counter;
  delay(1000);
  counter++;
}