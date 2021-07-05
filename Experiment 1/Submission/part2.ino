int counter = 1;
bool left_or_right = true;

void setup()
{
  DDRD = B11111111;
}

void loop()
{
  PORTD = counter;
  delay(1000);
  if(left_or_right)
  {
    counter = counter*2;
  }
  else
  {
    counter = counter/2;
  }
  if(counter==128 || counter==1)
  {
    left_or_right = !left_or_right;
  }
}