int seed[2] = {31,63};//numbers are taken from wiki
int random_number = 0;
//mapping arrays for seven segment display
int dout[16] = {192,128,192,192,128,64,64,192,192,192,192,0,64,128,64,64};
int bout[16] = {15,1,22,19,25,27,31,1,31,25,29,31,14,23,30,28};
void setup()
{
  DDRD = 192;//7th and 6th pins of d is set to output
  DDRB = 255;//all pins of b is set to output
  attachInterrupt(digitalPinToInterrupt(3),generate,RISING);//call generate when button is pressed
}

void loop()
{
  // void loop must stay empty
}

void generate()
{
  random_number = (seed[0] + seed[1]) % 32767;//add seeds and take mod(2^15 - 1) to prevent overflow
  seed[0] = seed[1];//seed[1] is moved to seed[0]
  seed[1] = random_number;//newly generated number is moved to seed[1]
  random_number = random_number % 16;//take mod 16 to display on ssd
  PORTB = bout[random_number];//send portb part of the number to ssd
  PORTD = dout[random_number];//send portd part of the number to ssd
}