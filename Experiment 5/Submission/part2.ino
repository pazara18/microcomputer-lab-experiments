int number = 0x321; //number we want player to guess
int counter = 0;
int lmost = -1, mid = -1, rmost = -1;//used to keep values of displays
bool game_over = false;
int bout[16] = {0,4,1,0,4,2,2,0,0,0,0,6,3,4,3,3};//mapping array for PortB
int dout[16] = {16,240,32,96,192,64,0,240,0,64,128,0,16,32,0,128};//mapping array for PortD
unsigned long time;
void setup()
{
  	DDRB = 255; //Data direction of PortB is output
  	DDRD = 0b11110000; //Data direction of PortD bits used for displays are output 
  	DDRC = 255; //Data direction of PortC is output
    attachInterrupt(digitalPinToInterrupt(2),pick,RISING); //calls pick subroutine if button is clicked 
}
void loop()
{
  if (!game_over)//enter as long as game continues
  {
      if(millis()%40 == 9)
      {
      	PORTC = 28;//first display
      	PORTB = bout[counter];//display counter
      	PORTD = dout[counter];
      }
      if((lmost != -1)&&((millis()%40) == 19))
      {
      	PORTC = 44;//second display
      	PORTB = bout[lmost];//display lmost value
      	PORTD = dout[lmost];
      }
      if((mid != -1)&&((millis()%40) == 29))
      {
      	PORTC = 52;//third display
      	PORTB = bout[mid];//display mid value
      	PORTD = dout[mid];
      }
      if((rmost != -1)&&((millis()%40) == 39))
      {
      	PORTC = 56;//fourth display
      	PORTB = bout[rmost];//display rmost value
      	PORTD = dout[rmost];
      }
      if (millis() >= time + 1000)//increment counter every 1000ms
      {
        counter++;
        counter = counter%16;//keep counter between 0-f
        time = time+1000;
      }
  }
  else//game is over target number is displayed
  {
      if((lmost != -1)&&((millis()%40) == 19))
      {
      	PORTC = 44;//second display
      	PORTB = bout[lmost];
      	PORTD = dout[lmost];
      }
      if((mid != -1)&&((millis()%40) == 29))
      {
      	PORTC = 52;//third display
      	PORTB = bout[mid];
      	PORTD = dout[mid];
      }
      if((rmost != -1)&&((millis()%40) == 39))
      {
      	PORTC = 56;//fourth display
      	PORTB = bout[rmost];
      	PORTD = dout[rmost];
      }
    
  }
}

void pick()
{
  int guessed;
  if(!game_over)//to make sure nothing happens when button is pressed after game is over
  {
  	if(lmost == -1)//first button click
  	{
    	lmost = counter;//counter value is shifted to second display
  	}
  	else if(mid == -1)//second button click
  	{
    	mid = lmost;//second display value is shifted to third display
    	lmost = counter;//counter value is shifted to second display
  	}
  	else//every other button click
  	{
    	rmost = mid;//third display value is shifted to fourth display
    	mid = lmost;//second display value is shifted to third display
    	lmost = counter;//counter value is shifted to second display
  	}
  	guessed = (lmost*256)+(mid*16)+rmost;//hexadecimal value of the players guess
  }
  if (number == guessed)//compare guess with target
  {
    game_over = true;
  }
}