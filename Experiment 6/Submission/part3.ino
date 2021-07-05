void triggerEnable();
void initLCD();
void sendChar(unsigned char data);
void sendCMD(unsigned char data);
void waitMillis(unsigned long time);
void waitMicros(unsigned long time);


void setup()
{
  DDRB = 255;//portb is set to output
  DDRD = 255;//portd is set to output
}

void loop()
{
  if(millis()%6000==0)
  {
    initLCD();//initialize lcd display
    //A 
    sendChar(0b0100);
    sendChar(0b0001);

    //B
    sendChar(0b0100);
    sendChar(0b0010);
    //D
    sendChar(0b0100);
    sendChar(0b0100);
    //U
    sendChar(0b0101);
    sendChar(0b0101);

    //L
    sendChar(0b0100);
    sendChar(0b1100);
    //K
    sendChar(0b0100);
    sendChar(0b1011);
    //A
    sendChar(0b0100);
    sendChar(0b0001);
    //D
    sendChar(0b0100);
    sendChar(0b0100);

    //I
    sendChar(0b0100);
    sendChar(0b1001);
    //R
    sendChar(0b0101);
    sendChar(0b0010);

    //newline
    sendCMD(0b1010);
    sendCMD(0b1000);

    //P
    sendChar(0b0101);
    sendChar(0b0000);
    //A
    sendChar(0b0100);
    sendChar(0b0001);
    //Z
    sendChar(0b0101);
    sendChar(0b1010);
    //A
    sendChar(0b0100);
    sendChar(0b0001);
    //R
    sendChar(0b0101);
    sendChar(0b0010);
  }
 else if(millis()%6000==2000)
 {
    initLCD();

    sendChar(0b0100); //E
    sendChar(0b0101);

    sendChar(0b0100); //G
    sendChar(0b0111);

    sendChar(0b0100); //E
    sendChar(0b0101);

    sendChar(0b0100); //M
    sendChar(0b1101);

    sendChar(0b0100); //E
    sendChar(0b0101);

    sendChar(0b0100); //N
    sendChar(0b1110);

    //newline
    sendCMD(0b1010);
    sendCMD(0b1000);

    sendChar(0b0100); //G
    sendChar(0b0111);

    sendChar(0b0101); //U
    sendChar(0b0101);

    sendChar(0b0100); //L
    sendChar(0b1100);

    sendChar(0b0101); //S
    sendChar(0b0011);

    sendChar(0b0100); //E
    sendChar(0b0101);

    sendChar(0b0101); //R
    sendChar(0b0010);

    sendChar(0b0100); //L
    sendChar(0b1100);

    sendChar(0b0100); //I
    sendChar(0b1001);

    sendChar(0b0100); //L
    sendChar(0b1100);

    sendChar(0b0100); //E
    sendChar(0b0101);

    sendChar(0b0101); //R
    sendChar(0b0010);
 }
 else if(millis()%6000==4000)
 {
    initLCD();

    sendChar(0b0101);  // S
    sendChar(0b0011);

    sendChar(0b0100);  // E
    sendChar(0b0101);

    sendChar(0b0100);  // L
    sendChar(0b1100);

    sendChar(0b0100);  // C
    sendChar(0b0011);

    sendChar(0b0101);  // U
    sendChar(0b0101);

    sendChar(0b0100);  // K
    sendChar(0b1011);

    //newline
    sendCMD(0b1010);
    sendCMD(0b1000);

    sendChar(0b0101);  // T
    sendChar(0b0100);

    sendChar(0b0101);  // U
    sendChar(0b0101);

    sendChar(0b0100);  // N
    sendChar(0b1110);

    sendChar(0b0100);  // C
    sendChar(0b0011);

    sendChar(0b0100);  // E
    sendChar(0b0101);

    sendChar(0b0101);  // R
    sendChar(0b0010);
 }
}

void initLCD()
{
  PORTD = PORTD & B11110011;//clear RS and R/W
  waitMillis(100);//100 ms wait
  
  PORTD = (PORTD & B00001111) | B00110000;//special case of function set
  triggerEnable();//send enable signal
  waitMillis(5);//5 ms wait
  
  PORTD = (PORTD & B00001111) | B00110000;//special case of function set
  triggerEnable();//send enable signal
  waitMicros(150);//150 us wait
 
  PORTD = (PORTD & B00001111) | B00110000;//function set interface is 8 bit long
  triggerEnable();//send enable signal
  waitMicros(150);//150 us wait
  
  PORTD = (PORTD & B00001111) | B00100000;//initial function set to change interface
  triggerEnable();//send enable signal
  waitMicros(150);//150 us wait
  
  PORTD = (PORTD & B00001111) | B00100000;//function set DL = 0 (dataline 8 bits)
  triggerEnable();//send enable signal
  PORTD = (PORTD & B00001111) | B10000000;//function set N = 1 (2 lines) F = 0 (5x8 grid)

  triggerEnable();//send enable signal
  waitMicros(55);//55 us wait
  
  PORTD = PORTD & B00001111;//display on off control
  triggerEnable();//send enable signal
  PORTD = (PORTD & B00001111) | B10000000;
  triggerEnable();//send enable signal
  waitMicros(55);//55 us wait
  
  PORTD = PORTD & B00001111;//clear display
  triggerEnable();//send enable signal
  PORTD = (PORTD & B00001111) | B00010000;
  triggerEnable();//send enable signal
  waitMillis(5);//5 ms wait
  
  PORTD = PORTD & B00001111;//entry mode set
  triggerEnable();//send enable signal
  PORTD = (PORTD & B00001111) | B01100000;//increment, no ds
  triggerEnable();//send enable signal
  waitMicros(55);//55 us wait
  
  PORTD = PORTD & B00001111;//display on off control
  triggerEnable();//send enable signal
  PORTD = (PORTD & B00001111) | B11100000;//display 1 cursor 1 no blink
  
  triggerEnable();//send enable signal
  waitMicros(55);//55 us wait
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

void waitMicros(unsigned long time)//produce delay of x microseconds
{
  unsigned long start_time = micros();//time before entering the loop
  while(true)
  {
    if(time < micros() - start_time)
      break;//stay in loop until time has passed
  }
}

void waitMillis(unsigned long time)//produce delay of x miliseconds
{
  unsigned long start_time = millis();//time before entering the loop
  while(true)
  {
    if(time < millis() - start_time)
      break;//stay in loop until time has passed
  }
}

void triggerEnable()//enable wait then disable lcd
{
  PORTB = 1;
  waitMicros(50);
  PORTB = 0;
} 