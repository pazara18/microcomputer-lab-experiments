int counter = 9;//counter variable

void initLCD();
void sendChar(unsigned char data);
void sendCMD(unsigned char data);
void waitMicros(int time);
void waitMillis(int time);
void triggerEnable();
void display_time();
void display_number(unsigned char num);

void setup()
{
  DDRB = 255;//direction of b port is output
  DDRD = 255;//direction of d port is output
  
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
}

void loop()
{
  if(millis()%500==0)
  {
    initLCD();
    //COUNTDOWN TIMER:
    //C
    sendChar(0b0100);
    sendChar(0b0011);
    //O
    sendChar(0b0100);
    sendChar(0b1111);
    //U
    sendChar(0b0101);
    sendChar(0b0101);
    //N
    sendChar(0b0100);
    sendChar(0b1110);
    //T
    sendChar(0b0101);
    sendChar(0b0100);
    //D
    sendChar(0b0100);
    sendChar(0b0100);
    //O
    sendChar(0b0100);
    sendChar(0b1111);
    //W
    sendChar(0b0101);
    sendChar(0b0111);
    //N
    sendChar(0b0100);
    sendChar(0b1110);
    //space
    sendChar(0b0010);
    sendChar(0b0000);
    //T
    sendChar(0b0101);
    sendChar(0b0100);
    //I
    sendChar(0b0100);
    sendChar(0b1001);
    //M
    sendChar(0b0100);
    sendChar(0b1101);
    //E
    sendChar(0b0100);
    sendChar(0b0101);
    //R
    sendChar(0b0101);
    sendChar(0b0010);
    //:
    sendChar(0b0011);
    sendChar(0b1010);

    //newline
    sendCMD(0b1010);
    sendCMD(0b1000);

    display_time();//display time on lcd display
  }
  
  if(!counter)//send signal to piezo when counter = 0
  {
    PORTB = 8;
  }
}

void initLCD()
{
  PORTD= PORTD&B11110011; //Clear RS and R/W
  waitMillis(100);  //Wait 100 ms
  
  PORTD= (PORTD&B00001111)|B00110000; //Special case of 'Function Set'
  triggerEnable();		//Send Enable Signal
  waitMillis(5);   //Wait 5ms
  
  PORTD= (PORTD&B00001111)|B00110000; //Special case of 'Function Set'
  triggerEnable();		//Send Enable Signal
  waitMicros(150);
  
  PORTD= (PORTD&B00001111)|B00110000; //Function set, Interface is 8 bit longs
  triggerEnable();		//Send Enable Signal
  waitMicros(150);
  
  PORTD= (PORTD&B00001111)|B00100000; //Initial 'Function Set' to change interface
  triggerEnable();		//Send Enable Signal
  waitMicros(150);
  
  PORTD= (PORTD&B00001111)|B00100000; //'Function Set' DL=0 // Dataline 8bits
  triggerEnable();		//Send Enable Signal
  PORTD= (PORTD&B00001111)|B10000000; //'Function Set' N=1 //2 lines
 									  // F =0 5x8 dots
  triggerEnable();		//Send Enable Signal
  waitMicros(55);
  
  PORTD= (PORTD&B00001111); //Dısplay On Of control
  triggerEnable();		//Send Enable Signal
  PORTD= (PORTD&B00001111)|B10000000; 
  triggerEnable();		//Send Enable Signal
  waitMicros(55);
  
  PORTD= (PORTD&B00001111); //Clear display
  triggerEnable();		//Send Enable Signal
  PORTD= (PORTD&B00001111)|B00010000; 
  triggerEnable();		//Send Enable Signal
  waitMillis(5);
  
  PORTD= (PORTD&B00001111); //Entry mode set
  triggerEnable();		//Send Enable Signal
  PORTD= (PORTD&B00001111)|B01100000; //ID=1 Increment, S=0
  triggerEnable();		//Send Enable Signal
  waitMicros(55);
  
  PORTD= (PORTD&B00001111); //Dısplay On Of control
  triggerEnable();		//Send Enable Signal
  PORTD= (PORTD&B00001111)|B11100000; //Display =1
  								      //Cursor =1
  									  //Blink cursor=0
  triggerEnable();		//Send Enable Signal
  waitMicros(55);
}


void sendChar(unsigned char data)
{
  PORTD = 0b00000100 | (data << 4);//rs = 1 and data is shifted 4 bits because of db4-db7 pins of lcd
  triggerEnable();//enable lcd
  waitMicros(55);//55 us delay
}

void sendCMD(unsigned char data)
{
  PORTD = 0b00000000 | (data << 4);//rs = 1 and data is shifted 4 bits because of db4-db7 pins of lcd
  triggerEnable();//enable lcd
  waitMicros(55);//55 us delay
}

void waitMicros(int time)
{
  long start_time=micros();
  while(micros()-start_time < time);
}

void waitMillis(int time)
{
  long start_time=millis();
  while(millis()-start_time < time);
}

void triggerEnable()//enable wait then disable lcd
{
  PORTB = 1;
  waitMicros(50);
  PORTB = 0;
}

ISR(TIMER1_COMPA_vect)//decrement counter once per second
{
  if(counter)//decrement if countdown hasnt ended
    counter--;
}

void display_time()//display time in hh:mm:ss
{
  int hour = counter / 3600;//hour of counter 
  int minute = (counter % 3600) / 60;//minute of counter
  int second = counter % 60;//second of counter
  
  display_number(hour/10);//tens digit of hour
  display_number(hour%10);//ones digit of hour
  
  sendChar(0b0011);//':' character
  sendChar(0b1010);
  
  display_number(minute/10);//tens digit of minute
  display_number(minute%10);//ones digit of minute
  
  sendChar(0b0011);//':' character
  sendChar(0b1010);
  
  display_number(second/10);//tens digit of second
  display_number(second%10);//ones digit of second
}

void display_number(unsigned char num)//display digits 0-9
{
  sendChar(0b0011);//upper 4 bits are same for digits
  sendChar(num);//lower 4 bits are number in binary
}