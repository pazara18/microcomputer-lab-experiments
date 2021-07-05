int seq1 = 16, seq2 = 8, seq3 = 128, seq4 = 1, display =0;//default values to produce given patterns
bool first_one = true, which_way = true;//booleans to select pattern and change direction of the shift
int csl(int a);
int csr(int a);
void setup()
{
  DDRB = 255;//B port is set to output
  DDRD = 0b11110000;//pins connected to ssd in port d is set to output
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
  
  attachInterrupt(digitalPinToInterrupt(3),swap,RISING);//call swap function on button press
}

void loop()
{

}

ISR(TIMER1_COMPA_vect)
{
 if(first_one)//for first pattern
 {
    display = seq1+seq2;//add seq1 and seq2 to produce pattern
    PORTD = (display%4)*64;//lower 2 bits of the number is sent to portd 
    PORTB = display/4;//send upper 6 bits to portb
    seq3 = 128;//set values for other pattern to default
    seq4 = 1;//set values for other pattern to default
    which_way = true;//set values for other pattern to default
    seq1 = csl(seq1);//shift seq1 to left 
    seq2 = csr(seq2);//shift seq2 to right
 }
 else
 {
    display = seq3+seq4;//add seq3 and seq4 to produce pattern
    PORTD = (display%4)*64;//lower 2 bits of the number is sent to portd 
    PORTB = display/4;//send upper 6 bits to portb
    seq3 = (seq3+128)%256;//turn on 7th led when time is even
    if(which_way)//seq4 moves left
    {
      seq4 = csl(seq4);//shift left
      if(seq4==128)//change direction
        which_way = !which_way;
    }
    else
    {
      seq4 = csr(seq4);//shift right
      if(seq4==1)//change direction
        which_way = !which_way;
    }
    
    seq1 = 16;//set values for other pattern to default
    seq2 = 8;//set values for other pattern to default
 }
}

void swap()
{
 first_one = !first_one;//change patterns 
}

int csr(int a)//csr that works when number has only one 1 and seven zeros
{
  a = a/2;//shift a to right
  if(a<1)//set a to 128 when a is smaller than 1 
  {
    a = 128;
  }
  return a;
}

int csl(int a)//csl that works when number has only one 1 and seven zeros
{
  a = a*2;//shift a to left
  if(a>128)//set a to 1 when a is larger than 128
  {
    a = 1;
  }
  return a;
}