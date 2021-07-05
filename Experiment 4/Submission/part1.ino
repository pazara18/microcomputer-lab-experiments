int GreenOPin = 3; //green output is taken from pin 3
int BlueOPin = 5; //blue output is taken from pin 5
int RedOPin = 6; //red output is taken from pin 6
int GreenIPin = A2; //green input is taken from pin a2
int BlueIPin = A1; //blue output is taken from pin a1
int RedIPin = A0; //red output is taken from pin a0
int Green, Red, Blue;

void setup() {
    pinMode(GreenOPin,OUTPUT);
    pinMode(RedOPin,OUTPUT);
    pinMode(BlueOPin,OUTPUT);
    pinMode(GreenIPin,INPUT);
    pinMode(BlueIPin,INPUT);
    pinMode(RedIPin,INPUT);
}
void loop() {
    Green = analogRead(GreenIPin); //value between 0-1023 is read
    Blue = analogRead(BlueIPin); //value between 0-1023 is read
    Red = analogRead(RedIPin); //value between 0-1023 is read
    analogWrite(GreenOPin,Green/4); //divided by 4 since RGB is 0-255
    analogWrite(RedOPin,Red/4); //divided by 4 since RGB is 0-255
    analogWrite(BlueOPin,Blue/4); //divided by 4 since RGB is 0-255
    delay(100);
}