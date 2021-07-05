void setup()
{
  asm(
"        JMP start                \n"
"delay: LDI     r23,  1            \n"    //Delay 12 msec
"w1:    LDI     r24,  255             \n"
"w2:    LDI  r25,  255             \n"
"w3:    DEC  r25                  \n"
"        BRNE w3                    \n"
"        DEC  r24                \n"
"        BRNE w2                    \n"
"        DEC  r23                \n"
"       BRNE w1                    \n"
"        RET                        \n"
";Your Functions Code Begin        \n" //Write your code
"ARTB:                   \n" //r19 <- PINB
"         CLZ                    \n"  // Clear zero flag to avoid errors  
"    	  INC r18                           \n" // Increment total count
"         LDI r26,0x01              \n"   //load 1 to r26 to store button 1 is pressed
"         CPI r18,10                   \n" // check if the value in the register that should display 1's digit is more than 9
"         BREQ w5               \n" // if value is more than 9 go to w5
"w6:      RET                           \n" // return to loop

"AZTB:        \n" //r19 <- PINB
"         CLZ                    \n" // Clear zero flag to avoid errors
"          DEC r18      \n" // Decrement total count
"        LDI r27,0x01    \n" //load 1 to r27 to store button 1 is pressed
"        CPI r18, 0xFF       \n" // check if the value in the register that should display 1's digit is less than 0
"          BREQ w8        \n" // if value is less than 0 go to w8
"w7:          RET                           \n" // return to loop

"w5: JMP ART_TEN                  \n" // jump to the function that increments 10's digit

"w8: JMP AZT_TEN                 \n" // jump to the function that decrements 10's digit

"HUND: LDI r20,0x00                   \n" //load 0 to 10's digit
"      JMP w6                    \n" // JUMP to the exact line in the incrementing function that called ART_TEN

"ART_TEN: CLR r18                \n" // since the value in the register is 10 clear it so that it will have the value 0
"		  INC r20                \n" // increment the register that keeps 10's digit by one
"         CPI r20,10                   \n" // check if 10's digit exceeds 10 -total count exceeds 100- 
"		  BREQ HUND                \n" // if so go to the function that clears 10's digit back to 0 
"         JMP w6                   \n" // JUMP to the exact line in the incrementing function that called ART_TEN

"AZT_TEN: LDI r18, 0x09             \n" // since the value in the register is less than 0 it should be 9 for ex. 30-1 = 29, 30-1!=2FF
"         DEC r20                \n" // decrement the register that keeps 10's digit by one
"         JMP w7                 \n" // JUMP to the exact line in the decrementing function that called AZT_TEN

";Your Functions Code End        \n" 
"                                \n"
"start:                            \n" //Write your code
"        IN      r16,  0x04 ;        \n" //r16 <- DDRB
"        LDI     r16,  0b11001111    \n" // Set r16 to set ddrb later
"        OUT  0x04, r16            \n" //DDRB <- r16
"        IN      r17,  0x07 ;        \n" //r17 <- DDRC
"        LDI     r17,  0b11001111    \n"    // Set r17 to set ddrc later
"        OUT  0x07, r17            \n" //DDRC <- r17
"        LDI  r18, 0x00          \n" //designed to keep and display the least significant digit
"       LDI  r19, 0x00          \n" // gets values from PINB in the loop
"       LDI r20, 0x00           \n" // gets values from PINC in the loop
"       LDI r26, 0x00           \n" //holds condition for but 1
"       LDI r27, 0x00           \n" //holds condition for but 2
  );

}

void loop()
{
  asm(
"LOOP:                            \n"
"        IN      r19,  0x03;         \n" //r19 <- PINB
"        SBRS    r19, 4                 \n" // skip next line if Button 1 isn't pushed
"        JMP     w9                \n"  // jump if button 1 is pushed
"        SBRS    r26, 0               \n" //skip next line if button 1 isn't released
"        CALL    ARTB                 \n" // CALL the function that increments the total count 
"w9:     SBRS    r19, 5              \n" // skip next line if Button 2 isn't pushed
"        JMP     w10                 \n" // jump if button 1 is pushed
"        SBRS    r27, 0              \n" //skip next line if button 2 isn't released
"        CALL    AZTB                \n" // CALL the function that decrements the total count
"w10:    SBRS    r19,4               \n" // skip next line if Button 1 isn't pushed
"        CLR     r26                 \n" // clear r26
"        SBRS    r19, 5              \n" / skip next line if Button 2 isn't pushed
"        CLR     r27                 \n" // clear r27
"        OUT     0x05, r18            \n" // PORTB <- r18
"        OUT     0x08, r20         \n" // PORTC <- r20
//"        CALL delay                \n"    // Call delay function
"        JMP     LOOP                \n" // Restart loop
  );

}