unsigned int seed[2] = {31,63};//numbers are taken from wiki
int random_number = 0;
//mapping arrays for seven segment display
int dout[16] = {192,128,192,192,128,64,64,192,192,192,192,0,64,128,64,64};
int bout[16] = {15,1,22,19,25,27,31,1,31,25,29,31,14,23,30,28};
int* arr;//pointer to beginning of dynamic array
int index = 0;
int size;//size of dynamic array
char buffer[5];//buffer to keep user input

int tint(char* numStr);//function to turn char arrays to int
int number_of_occurrence(int number);//function to find how many times a number is in an array
void wait_millis(int msecs);//function to wait to make sure Serial communication works

void setup()
{
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(3),generate,RISING);//generate is called on button press
}

void loop()
{
  // void loop must stay empty
}

void generate()
{
  sei();//enable interrupts to make serial communication work within interrupt
  int i = 0;
  Serial.println("Please enter a m value:");//print prompt and wait user input
  while(1)
  {
     if(Serial.available())//if there is input
     {
       wait_millis(10);//wait 10 ms to make sure Serial communication work
       while(Serial.available() > 0)
       {  
  	     buffer[i] = Serial.read();//read input to buffer
         i++;
       }
       break;
     }
  }
  size = tint(buffer);//turn buffer to int
  arr = (int*) malloc(sizeof(int) * size);//create dynamic array with size of user input
  while(index < size)//fill dynamic array
  {
    random_number = (seed[0] + seed[1]) % 32767;//create random number similar to part 1
    seed[0] = seed[1];
    seed[1] = random_number;
    random_number = random_number % 8;//take mod 8 of number
    arr[index] = random_number;//fill the array
    index++;
  }
  //print how many times each number occured
  Serial.print("# of 0's: ");
  Serial.println(number_of_occurrence(0));
  Serial.print("# of 1's: ");
  Serial.println(number_of_occurrence(1));
  Serial.print("# of 2's: ");
  Serial.println(number_of_occurrence(2));
  Serial.print("# of 3's: ");
  Serial.println(number_of_occurrence(3));
  Serial.print("# of 4's: ");
  Serial.println(number_of_occurrence(4));
  Serial.print("# of 5's: ");
  Serial.println(number_of_occurrence(5));
  Serial.print("# of 6's: ");
  Serial.println(number_of_occurrence(6));
  Serial.print("# of 7's: ");
  Serial.println(number_of_occurrence(7));
  free(arr);//free dynamiccally allocated memory
}

int number_of_occurrence(int number)
{
  int count = 0;
  for(int i = 0; i < size; i++)
  {
    if(arr[i] == number) count++;//if number is found increment count
  }
  return count;
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

void wait_millis(int msecs)//dead time used to make sure serial.available works correctly
{ 
  long now = millis();
  while(millis()-now < msecs);
}