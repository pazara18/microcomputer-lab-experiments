#include <Wire.h>

#include <Servo.h>

int ang;
Servo Servo0;
Servo Servo1;
Servo Servo2;
Servo Servo3;
void setup()
{
  Wire.begin(12);//address of servo microcontroller
  DDRD = 255;//set data
  DDRB = 255;
  Servo0.attach(3);//connect servos to appopriate pins
  Servo1.attach(5);
  Servo2.attach(6);
  Servo3.attach(9);
  Servo0.write(0);
  Servo1.write(0);
  Servo2.write(0);
  Servo3.write(0);
  Wire.onReceive(rec);//when info is recieved call rec function
}


void loop()
{}

void rec(int num_rec)
{
  ang = Wire.read();//read value from master
  Servo0.write(ang);//write value to servo
  ang = Wire.read();
  Servo1.write(ang);
  ang = Wire.read();
  Servo2.write(ang);
  ang = Wire.read();
  Servo3.write(ang);
}