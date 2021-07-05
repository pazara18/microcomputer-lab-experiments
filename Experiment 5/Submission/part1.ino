int tens = 0, ones = 0, counter = 0, iterator = 1;
unsigned long time;
void setup()
{
  	DDRB = 255; //PortB data direction is set to output
  	DDRC = 255; //PortC data direction is set to output
  	DDRD = 0; //PortD data direction is set to input
    attachInterrupt(digitalPinToInterrupt(3),reset,RISING);//calls reset subroutine when button 1 is pressed
    attachInterrupt(digitalPinToInterrupt(2),other_way,RISING);//calls other_way subroutine when button 2 is pressed
}


void loop()
{
  if (counter < 0)
  {
    counter = 99; //set counter to 99 if decrementing from zero
  }
  if (counter > 99)
  {
    counter = 0; //set counter to 0 if incrementing from 99
  }
  ones = counter%10;//ones digit of the counter
  tens = counter/10;//tens digit of the counter
  PORTB = ones;//ones digit is sent to PORTB
  PORTC = tens;//tens digit is sent to PORTC
  if(millis() >= time + 1000)//delay of 1000ms
  {
    time = time + 1000;
  	counter = counter + iterator;//increment or decrement counter
  }
}

void reset()
{
    counter = 0;//set counter to 0
    PORTB = counter;//send 0 to PORTB
  	PORTC = counter;//send 0 to PORTC
}

void other_way()
{
    iterator = -iterator;//change counting mode
}