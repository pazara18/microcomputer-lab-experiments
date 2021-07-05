int analog, analogPin = A0, analog_digit;
//dout keeps values that are fed to seven segment display
int dout[10] = {1,79,18,6,76,36,32,15,0,4};
void setup()
{
    DDRC = 0b000000; //ddrc assigned as input for analog inputs
    DDRD = 0b11111111;//ddrd assgined as output for 7-segment display
    DDRB = 0b111111;//common anode is set
}

void loop()
{
    analog = analogRead(analogPin);
    analog_digit = analog%10; //analog digit = ones digit
    PORTD = dout[analog_digit]; //analog digit is displayed on ssd
    delay(100);
}