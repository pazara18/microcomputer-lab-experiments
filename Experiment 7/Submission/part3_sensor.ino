#include <Wire.h>

int value,angle;
uint8_t arr[4];//array to hold angles
int last_time = 0,now;

void setup()
{
  	Wire.begin(11);//address of sensor microcontroller 
  	Wire.onRequest(requestEvents);//call requestEvents on request
}


void loop()
{
  now = millis();
  if(now - last_time > 200)//freq = 5Hz
  {
    last_time = now;
  	value = analogRead(A0);//read analog values
    packet(0,value);//turn angles to packets
  	value = analogRead(A1);
    packet(1,value);
  	value = analogRead(A2);
    packet(2,value);
  	value = analogRead(A3);
    packet(3,value);
  }
}

void packet(int sensor, int value)//calculate angle and put into array
{
  	angle = (value-236)/2.21;
    arr[sensor] = angle;
}

void requestEvents()//send angle array
{
  Wire.write(arr,4);
}