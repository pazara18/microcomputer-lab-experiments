int counter = 1;
int player = 1, player_pick = 0;
bool game_over = false;
int bout[16] = {0,4,1,0,4,2,2,0,0,0,0,6,3,4,3,3};//mapping array for PortB
int dout[16] = {16,240,32,96,192,64,0,240,0,64,128,0,16,32,0,128};//mapping array for PortD
unsigned long time = 0;
void setup()
{
  	DDRB = 255; //Data direction of PortB is output
  	DDRD = 0b11110000; //Data direction of PortD bits used for displays are output 
  	DDRC = 255; //Data direction of PortC is output
    attachInterrupt(digitalPinToInterrupt(2),pick1,RISING);//calls pick1 subroutine if first button is clicked 
  	attachInterrupt(digitalPinToInterrupt(3),pick2,RISING);//calls pick2 subroutine if second button is clicked
}


// main loop
void loop()
{
  if (!game_over)//enter as long as game continues
  {
		if((player==1)&&(!player_pick))//display logic for first move of the first player
		{
			if(millis()%40 == 19)
			{
				PORTC = 44;//second display
				PORTB = bout[counter%10];//ones digit of the counter
				PORTD = dout[counter%10];
			}
			if((millis()%40) == 39)
			{
				PORTC = 28;//first display
				PORTB = bout[counter/10];//tens digit of the counter
				PORTD = dout[counter/10];
			}
			if(millis()>=time+200)//increment counter every 200ms
			{
				time = time+200;
				counter++;
				counter = counter%21;//keep counter between 1-20
				if(!counter)
					counter++;
			}
		}
		if(player==2)//display logic for all moves of second player
		{
			if(millis()%40 == 9)
			{
				PORTC = 56;//fourth display
				PORTB = bout[counter%10];//ones digit of the counter
				PORTD = dout[counter%10];
			}
			if((millis()%40) == 19)
			{
				PORTC = 52;//third display
				PORTB = bout[counter/10];//tens digit of the counter
				PORTD = dout[counter/10];
			}
			if((millis()%40) == 29)
			{
				PORTC = 44;//second display
				PORTB = bout[player_pick%10];//ones digit of first players pick
				PORTD = dout[player_pick%10];
			}
			if((millis()%40) == 39)
			{
				PORTC = 28;//first display
				PORTB = bout[player_pick/10];//tens digit of first players pick
				PORTD = dout[player_pick/10];
			}
			if(millis()>=time+200)//increment counter every 200ms
			{
				time = time+200;
				counter++;
				counter = counter%21;//counter is kept between 1-20
				if(!counter)
					counter++;
			}
		}
		if((player==1)&&(player_pick))//display logic for all moves of first player expect first move
		{
			if(millis()%40 == 9)
			{
			PORTC = 44;//second display
			PORTB = bout[counter%10];//ones digit of the counter
			PORTD = dout[counter%10];
			}
			if((millis()%40) == 19)
			{
				PORTC = 28;//first display
				PORTB = bout[counter/10];//tens digit of the counter
				PORTD = dout[counter/10];
			}
			if((millis()%40) == 29)
			{
				PORTC = 56;//fourth display
				PORTB = bout[player_pick%10];//ones digit of second players pick
				PORTD = dout[player_pick%10];
			}
			if((millis()%40) == 39)
			{
				PORTC = 52;//third display
				PORTB = bout[player_pick/10];//tens digit of second players pick
				PORTD = dout[player_pick/10];
			}
			if(millis()>=time + 200)//increment counter every 200ms
			{
				time = time+200;
				counter++;
				counter = counter%21;//counter is kept between 1-20
				if(!counter)
					counter++;
			}
		}
    
  	}
  else//display winners number on all displays if game is over
  {
	if(millis()%40 == 9)
	{
		PORTC = 28;
		PORTB = bout[player];
		PORTD = dout[player];
	}
	if((millis()%40) == 19)
	{
		PORTC = 44;
		PORTB = bout[player];
		PORTD = dout[player];
	}
	if((millis()%40) == 29)
	{
		PORTC = 52;
		PORTB = bout[player];
		PORTD = dout[player];
	}
	if((millis()%40) == 39)
	{
		PORTC = 56;
		PORTB = bout[player];
		PORTD = dout[player];
	}
  }
}

void pick1()
{
  if((player==1)&&(!game_over))//to make sure nothing happens if player 2 presses button 1
  {
    if(player_pick!=counter)
    {
      player_pick = counter;//set player pick to counter
      player = 2;//change player
      counter = 1;//reset counter
    }
    else//if player 1 catches player 2
    {
      game_over = true;
    }
  }
}
  
void pick2()
{
  if((player == 2) && (!game_over))//to make sure nothing happens if player 1 presses button 2
  {
    if(player_pick!=counter)
    {
      player_pick = counter;//set player pick to counter
      player = 1;//change player
      counter = 1;//reset counter
    }
    else//if player 2 catches player 1
    {
      game_over = true;
    }
  }
}