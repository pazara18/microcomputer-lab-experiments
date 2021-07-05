int counter_LL = 1;
int counter_HH = 1;
int timer = 0;
int counter_HL = 128;
int counter_LH = 128;
int val;
bool left_or_right_LL = true;
bool left_or_right_HH = true;

void setup()
{
  DDRD = 0xff;
  DDRB = 0x00;
}

void loop()
{
  val = PINB;
  if(val == 5){
    PORTD = counter_HL;
    counter_HL = (counter_HL * 128 + counter_HL / 2) % 256;
  }
  else if(val == 6){
    PORTD = counter_LH;
    if(timer % 2 == 0){
      counter_LH = 1 << (7 - (timer % 8));
    }
    else{
      counter_LH = 1 << (timer % 8);
    }
    timer++;
  }
  else if(val == 7){
    PORTD = counter_HH;
    if(left_or_right_HH){
      counter_HH = (counter_HH / 128 + counter_HH * 2) % 256;
    }
    else{
      counter_HH = (counter_HH * 128 + counter_HH / 2) % 256;
    }
    if(counter_HH == 8 || counter_HH == 16){
      left_or_right_HH = !left_or_right_HH;
    }
  }
  else if(val == 4){
    PORTD = counter_LL;
    if(left_or_right_LL)
    {
      counter_LL = counter_LL*2;
    }
    else
    {
      counter_LL = counter_LL/2;
    }
    if(counter_LL==128 || counter_LL==1)
    {
      left_or_right_LL = !left_or_right_LL;
    }
  }
  if(val != 6){
    timer = 0;
    counter_LH = 128;
  }
  if(val != 5)
    counter_HL = 128;
  if(val != 7){
      counter_HH = 1;
      left_or_right_HH = true;
  }
  if(val != 4){
    counter_LL = 1;
  }
  delay(1000);
}