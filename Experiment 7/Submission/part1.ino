#include <string.h>
unsigned int value,angle;
double resistor;
int res;
int which_one = 0;
char arr1[19];

void setup()
{
  	Serial.begin(9600);
}


void loop()
{
  if(millis()%200 == 0)//polling freq is 5Hz
  {
    int i = 0, j= 0;
  	value = analogRead(A0);//read value for first flex sensor
    packet(0,value);//function to turn values to packets in requested format
    Serial.println(arr1);//print packet
  	value = analogRead(A1);//read value for second flex sensor
    packet(1,value);
    Serial.println(arr1);
  	value = analogRead(A2);//read value for third flex sensor
    packet(2,value);
    Serial.println(arr1);
  	value = analogRead(A3);//read value for fourth flex sensor
    packet(3,value);
    Serial.println(arr1);
  }
}

void packet(int sensor, int value)
{
  	angle = (value-236)/2.21;//turn value to angle between 0 - 180
  	resistor = (angle*0.44) + 45;//turn value to resistance between 45kOhms - 125kOhms
  	res = resistor*100;//multiply by 100 to process resistance as float with 2 significant digits 
  	arr1[0] = '!';//first char in packet is !
  	if(sensor == 0) arr1[1] = '0';//next char denotes flex sensor number
  	else if(sensor == 1) arr1[1] = '1';
  	else if(sensor == 2) arr1[1] = '2';
  	else if(sensor == 3) arr1[1] = '3';
  	arr1[2] = ';';//next char is semicolon
  	arr1[3] = value/100 + '0';//hundreds digit of the value
  	arr1[4] = (value/10)%10 + '0';//tens digit of the value
  	arr1[5] = value%10 + '0';//ones digit of the value
  	arr1[6] = ';';
  	if(resistor < 100)//if resistor value is 2 digits
    {
      arr1[7] = res/1000 + '0';//tens digit of resistance
      arr1[8] = (res/100)%10 + '0';//ones digit of the resistance
      arr1[9] = '.';
      arr1[10] = (res/10)%10 + '0';//tenths digit of resistance
      arr1[11] = res%10 + '0';//hundredths digit of resistance
      arr1[12] = ';';
      if(angle<10)//if angle is single digit convert it to char similar to resistance and values
      {
        arr1[13] = angle + '0';
        arr1[14] = '#';
        arr1[15] = '\0';
        return;
      }
      else if(angle < 100)//if angle is two digit convert it to char similar to resistance and values
      {
        arr1[13] = angle/10 + '0';
        arr1[14] = angle%10 + '0';
        arr1[15] = '#';
        arr1[16] = '\0';
        return;
      }
      else//if angle is three digit convert it to char similar to resistance and values
      {
        arr1[13] = angle/100 + '0';
        arr1[14] = (angle/10)%10 + '0';
        arr1[15] = angle%10 + '0';
        arr1[16] = '#';
        arr1[17] = '\0';
      }
    }
  	else//if resistor value is three digits convert it to char similar to resistor values above
    {
      arr1[7] = res/10000 + '0';
      arr1[8] = (res/1000)%10 + '0';
      arr1[9] = (res/100)%10 + '0';
      arr1[10] = '.';
      arr1[11] = (res/10)%10 + '0';
      arr1[12] = res%10 + '0';
      arr1[13] = ';';
      if(angle<10)//if angle is one digit convert it to char similar to resistance and values
      {
        arr1[14] = angle + '0';
        arr1[15] = '#';
        arr1[16] = '\0';
        return;
      }
      else if(angle < 100)//if angle is two digit convert it to char similar to resistance and values
      {
        arr1[14] = angle/10 + '0';
        arr1[15] = angle%10 + '0';
        arr1[16] = '#';
        arr1[17] = '\0';
        return;
      }
      else//if angle is three digit convert it to char similar to resistance and values
      {
        arr1[14] = angle/100 + '0';
        arr1[15] = (angle/10)%10 + '0';
        arr1[16] = angle%10 + '0';
        arr1[17] = '#';
        arr1[18] = '\0';
      }
    }
      
}
