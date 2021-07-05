#include <Servo.h>//servo library to interact with servo engines

char arr[100] = {0}, s0[4] = {0};//arrays to hold values
int ang, angs[4];
Servo Servo0;
Servo Servo1;
Servo Servo2;
Servo Servo3;
void setup()
{
  Serial.begin(115200);
  DDRD = 255;//data direction of d is output because of servos
  DDRB = 255;//data direction of b is output because of servos
  Servo0.attach(3);//connect servos to appopriate pins
  Servo1.attach(5);
  Servo2.attach(6);
  Servo3.attach(9);
  Servo0.write(0);//write 0 to initialize servos
  Servo1.write(0);
  Servo2.write(0);
  Servo3.write(0);
}


void loop()
{
  if(Serial.available() > 0)//if an input is given via serial monitor
  {
    wait_millis(10);
  	int i = 0, j = 0;
  	while(Serial.available() > 0)
    {
      while (Serial.available() > 0)//read into buffer until either message ends or # character is read
      {
        arr[i] = Serial.read();
        if (arr[i] == '#')
        {
          break;
        }
        i++;
      }
      
      Serial.println(arr);//print written message to serial monitor
      int count = 0;
      j=0;
      while(arr[j] != '\0')//count number of semicolons
      {
          if(arr[j] == ';')
          {
              count++;
          }

          j++;
      }
      if(arr[0] != '!')//if array doesn't start with !
      {
        Serial.print("Error! There is no start char\n");
        clear();
      }
      else if(count < 3)//if there is not enough input
      {
        Serial.print("Error! There is not enough input\n");
        clear();
      }
      else if(count > 3)//if there are extra inputs
      {
        Serial.print("Error! There is extra input\n");
        clear();
      }
      else if(strstr(arr, ";;"))//if there is an empty input
      {
        Serial.print("Error! All parameters must be filled!\n");
        clear();
      }
      else if(arr[strlen(arr)-1] != '#')//if last element is not a #
      {
        Serial.print("Error! There is no endchar!\n");
        clear();
      }
      
      else
      {
        int  r=0;
        j=1, i=0;
        while(arr[j] != '\0')//starting from first char after !
        {
            int t = 0;
            if((arr[j]>57)||(arr[j]<48))//if value stored at index is not a number print error and break loop
            {
              Serial.print("Error! Invalid input!\n");
              clear();
              break;
            }
            s0[i] = arr[j];//store number values in s0
            i++;
            j++;
            if((arr[j] == ';')||(arr[j]=='#'))//if char is semicolon or hash
            {
              i = 0;
              j++;
              ang = tint(s0);//turn value stored in s0 array to int
              if(ang > 180)//give error if angle is greater than 180
              {
                Serial.print("Error! Angle value must be less than 180!\n");
                clear();
                break;//break from loop
              }
              angs[r] = ang;//write angle to angle array
              r++;//move angle array index by one
            while(s0[t] != '\0')//clear s0 array to store next int
            {
              s0[t] = '\0';
              t++;
            }
          }
        }
        if(r==4)
        {
          print_input();//print result in correct format
          Servo0.write(angs[0]);//turn servos using given values
          Servo1.write(angs[1]);
          Servo2.write(angs[2]);
          Servo3.write(angs[3]);
          clear();
        }
      }
    }
  }
}

void clear()//reset all arrays after the output is displayed
{
  int i = 0;
  while(arr[i] != '\0')//clear buffer
  {
    arr[i] = '\0';
    i++;
  }
  i = 0;
  while(s0[i] != '\0')//clear number array used to turn char array to int
  {
    s0[i] = '\0';
    i++;
  }
  i = 0;
  while(i<4)//clear angles array
  {
    angs[i] = 0;
    i++;
  }
}

void wait_millis(int msecs)//dead time used to make sure serial.available works correctly
{ 
  long now = millis();
  while(millis()-now < msecs);
}

int tint(char* numStr)//function to turn given char array to integer value
{
    int intVal=0 ;

    while(*numStr != '\0')
    {
        intVal *= 10;//multiply with ten to shift the number
        intVal  += *numStr - '0';//add next index to number
        numStr++;//move to next index
    } 
    return intVal;
}

void print_input()//function to print correct output in requested format
{
  Serial.print("S0:");
  Serial.print(angs[0]);
  Serial.print("; S1:");
  Serial.print(angs[1]);
  Serial.print("; S2:");
  Serial.print(angs[2]);
  Serial.print("; S3:");
  Serial.print(angs[3]);
  Serial.print("\n");
}