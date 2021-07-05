int counter = 0, lap_counter = 0, lap_number = 0;//globals to keep counter lap counter and lap number
int bout[16] = {0,4,1,0,4,2,2,0,0,0,0,6,3,4,3,3};//mapping array for PortB
int dout[16] = {16,240,32,96,192,64,0,240,0,64,128,0,16,32,0,128};//mapping array for PortD
bool started = false;//doesnt start until first button is pressed
int B = 0;//used for reset
void reset();
void start();
void lap();
void setup()
{
  DDRB = 0b000111;//lower 3 pins of portb is output because of ssd
  DDRD = 0b11110000;//upper 4 pins of portd is output because of ssd
  DDRC = 255;//portc is set to output
  // TIMER 1 for interrupt frequency 100 Hz:
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 100 Hz increments
  OCR1A = 19999; // = 16000000 / (8 * 100) - 1 
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 8 prescaler
  TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts
  attachInterrupt(digitalPinToInterrupt(2),start,RISING);//start function is called when 1st button is pressed
  attachInterrupt(digitalPinToInterrupt(3),lap,RISING);//lap function is called when 2nd button is pressed
  Serial.begin(9600);//to print lap times to serial monitor
}

void loop()
{
  if(millis()%40 == 9)
  {
    PORTC = 28;//first display
    PORTB = bout[counter/1000];//display thousands digit of centiseconds
    PORTD = dout[counter/1000];
  }
  if(millis()%40 == 19)
  {
    PORTC = 44;//second display
    PORTB = bout[(counter/100)%10];//display hundreds digit of centiseconds
    PORTD = dout[(counter/100)%10];
  }
  if(millis()%40 == 29)
  {
    PORTC = 52;//third display
    PORTB = bout[(counter/10)%10];//display tens digit of centiseconds
    PORTD = dout[(counter/10)%10];
  }
  if(millis()%40 == 39)
  {
    PORTC = 56;//fourth display
    PORTB = bout[counter%10];//display ones digit of centiseconds
    PORTD = dout[counter%10];
  }
  B = PINB&32;//to check 3rd button press
  if(B)
  {
    reset();//reset if 3rd button is pressed
  }
}

ISR(TIMER1_COMPA_vect)//timer interrupt
{
  if(started)//increment counters when started
  {
  	counter++;
    lap_counter++;
  }
}

void start()//start counter
{
  started = true;
}

void reset()//reset function set globals to default values
{
  counter = 0;
  started = false;
  lap_counter = 0;
  lap_number = 0;
}

void lap()
{
  if(started)
  {
  	lap_number++;//increment lap number
    Serial.print("lap number: ");
    Serial.println(lap_number);//print lap number
    Serial.print("lap time: ");
    Serial.println(lap_counter);//print lap time
    Serial.print("total time: ");
    Serial.println(counter);//print total time
    lap_counter = 0;//start counting next lap time
  }
}