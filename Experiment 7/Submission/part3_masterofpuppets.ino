#include <Wire.h>

uint8_t angles[4];//array to hold angles
void setup()
{
  	Wire.begin();//no address since master
}

uint8_t acc = 0; 
char received[19];//array to store recieved packet
int last_time = 0,now;

void loop()
{
  now = millis();
  if(now - last_time > 200)//polling freq is 5Hz
  { 
    last_time = now;
    int i = 0;
  	Wire.requestFrom(11, 4);//request 4 bytes from sensor microcontroller 
    while((Wire.available())&&(i < 4))//store info from sensor to an array
    {
  		angles[i] = Wire.read(); 
    	i++;
    }
    Wire.beginTransmission(12);//send info to servo microcontroller
    Wire.write(angles,4);
    Wire.endTransmission();//end transmission
  }
}