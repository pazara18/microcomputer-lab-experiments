int counter = 0;
int val;

void setup()
{
  DDRD = B11111111;
  DDRB = 0x00;
  //Serial.begin(9600);
}
void loop()
{
  PORTD = counter;
  val = PINB;
  if(val == 4){
  counter++;
  }else{
  counter--;
  }
  //Serial.print(pinState10);
  delay(1000);
}