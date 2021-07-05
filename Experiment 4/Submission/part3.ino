int analog, analogPin = A0, analog_digit;
//dout keeps values that are fed to seven segment display
int dout[10] = {1,79,18,6,76,36,32,15,0,4};
void setup()
{
    DDRC = 0b000000;// ddrc assigned as input for analog inputs
    DDRD = 0b11111111;// ddrd assgined as output for 7-segment display
    DDRB = 0b11111111;//common anode is set
}


//used to set analog_digit to number supposed to be displayed next
void fetch_last_digit()
{
    analog_digit = analog%10;
    analog = analog - analog_digit;
    analog = analog/10;
}
void loop()
{
    analog = analogRead(analogPin);
    PORTB = 14;//display of ones digit is active
    fetch_last_digit();//analog digit = ones digit
    PORTD = dout[analog_digit];//analog digit is displayed on ssd
    delay(15);
    PORTB = 13;//display of tens digit is active
    fetch_last_digit();//analog digit = tens digit
    PORTD = dout[analog_digit];//analog digit is displayed on ssd
    delay(15);
    PORTB = 11;//display of hundreds digit is active
    fetch_last_digit();//analog digit = hundreds digit
    PORTD = dout[analog_digit];//analog digit is displayed on ssd
    delay(15);
    PORTB = 7;//display of thousands digit is active
    fetch_last_digit();//analog digit = thousands digit
    PORTD = dout[analog_digit];//analog digit is displayed on ssd
    delay(15);
}