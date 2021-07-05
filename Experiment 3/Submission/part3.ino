void setup()
{
  asm(
"        JMP start                \n"
"delay: LDI     r23,  8           \n"    //Delay 1 msec
"w1:    LDI     r24,  25             \n"
"w2:    LDI  r25,  25             \n"
"w3:    DEC  r25                  \n"
"        BRNE w3                    \n"
"        DEC  r24                \n"
"        BRNE w2                    \n"
"        DEC  r23                \n"
"       BRNE w1                    \n"
"        RET                        \n"
";Your Functions Code Begin        \n" //Write your code
// BUTTONS 1-2
"ART_IN:                   \n" 
"         CLZ                    \n"  // Clear zero flag to avoid errors  
"    	  INC r18                           \n" // Increment total count
"         LDI r26,0x01              \n" // update register holding condition for but1
"         CPI r18,11                   \n" // check if the value in the register that should display 1's digit is more than 9
"         BREQ MAX_IN               \n" // if value is more than 9 go to w5
"w6:      RET                           \n" // return to loop

"AZT_IN:          \n" //
"         CLZ                    \n" // Clear zero flag to avoid errors 
"           DEC r18      \n" // Decrement total count
"         LDI r27,0x01              \n"  // update register holding condition for but2
"        CPI r18, 0x00       \n" // check if the value in the register that should display 1's digit is less than 0
"          BREQ MIN_IN        \n" // if value is less than 0 go to w8
"w7:          RET                           \n" // return to loop

"MAX_IN: DEC r18                \n" // since the value in the register is 10 clear it so that it will have the value 0 
"         JMP w6                   \n" // JUMP to the exact line in the incrementing function that called ART_TEN

"MIN_IN: INC r18             \n" // since the value in the register is less than 0 it should be 9 for ex. 30-1 = 29, 30-1!=2FF
"         JMP w7                 \n" // JUMP to the exact line in the decrementing function that called AZT_TEN
// ENDOF BUTTONS 1-2
/*    
// BUTTONS 3-4 DOESNT WORK
"ART_TI:                   \n" 
"         CLZ                    \n"  //DOESNT WORK  
"    	  INC r17                           \n" // DOESNT WORK
"    	  INC r30                           \n" // DOESNT WORK
"         LDI r28,0x01              \n" //DOESNT WORK
"         CPI r17,11                   \n" //DOESNT WORK
"         BREQ MAX_TI               \n" //DOESNT WORK
"t6:      RET                           \n" //DOESNT WORK

"AZT_TI:          \n" //
"         CLZ                    \n" // Clear zero flag to avoid errors 
"           DEC r17      \n" // Decrement total count
"    	  DEC r30                           \n" // Increment total count
"         LDI r29,0x01              \n"
"        CPI r17, 0x00       \n" // check if the value in the register that should display 1's digit is less than 0
"          BREQ MIN_TI        \n" // if value is less than 0 go to w8
"t7:          RET                           \n" // return to loop

"MAX_TI: DEC r17                \n" // since the value in the register is 10 clear it so that it will have the value 0 
"         JMP t6                   \n" // JUMP to the exact line in the incrementing function that called ART_TEN

"MIN_TI: INC r17             \n" // since the value in the register is less than 0 it should be 9 for ex. 30-1 = 29, 30-1!=2FF
"         JMP t7                 \n" // JUMP to the exact line in the decrementing function that called AZT_TEN
*/   
// ENDOF BUTTONS 3-4
"MINUSHUN: SUBI r16,100     \n"
"          RET          \n"
    
"adder:	 ADD     r16, r18           \n" // add incrementer to number holding the register
"        CPI     r16, 100           \n" // compares number to 100
"        BRSH    MINUSHUN           \n" // branch to subtract 100
"        OUT     0x0B, r16            \n" // PORTd <- r16
"        LDI     r17, 5               \n" // change timer according to button press (doesn't work)
"        JMP LOOP                     \n" //go back to main loop

"hun_milis:   DEC r17           \n" // decrement register holding timer number
"       LDI r21, 100           \n" // load 100 to register in the main loop for timer
"       JMP w11                     \n" // jump to w11
    
";Your Functions Code End        \n" 
"                                \n"
"start:                            \n" //Write your code
"        IN      r16,  0x04 ;        \n" //r16 <- DDRB
"        LDI     r16,  0b11001111    \n" // Set r16 to set ddrb later
"        OUT  0x04, r16            \n" //DDRB <- r16
"        IN      r17,  0x07 ;        \n" //r17 <- DDRC
"        LDI     r17,  0b11001111    \n"    // Set r17 to set ddrc later
"        OUT  0x07, r17            \n" //DDRC <- r17
"        IN r18, 0x0A           \n" // r18 <- PORTD
"       LDI r18, 0xFF           \n" // set portd to out
"       OUT 0x0A, r18           \n" // PORTD <- r18
"		LDI r16, 0x00           \n" //total count
"       LDI r17, 0x05           \n" //how many hundered miliseconds
"       LDI r18, 0x01          \n" //designed to keep Incrementer
"       LDI r19, 0x00          \n" // gets values from PINB in the loop
"       LDI r20, 0x00           \n" // gets values from PINC in the loop
"       LDI r21, 0x64           \n" // holds 100 to count number of loops
"       LDI r26, 0x00           \n" //holds condition for but 1
"       LDI r22, 0x00           \n" // holds pinc
"       LDI r27, 0x00           \n" //holds condition for but 2
"       LDI r28, 0x00           \n" //holds condition for but 3
"       LDI r29, 0x00           \n" //holds condition for but 4
//"       LDI r30, 0x05           \n" //holds how many hundred miliseconds we should count next time
  );

}

void loop()
{
  asm(
"LOOP:                            \n"
"        CALL delay                \n"    // Call delay function
"        IN      r19,  0x03;         \n" //r19 <- PINB
"        IN      r22, 0x06;        \n" //r22 <- PINC
// BUTTONS 1-2
"        SBRS    r19, 4                 \n" // skip next line if Button 1 is pushed
"        JMP     w9                \n" // jump to w9 if button isnt pushed
"        SBRS    r26, 0               \n" // skip next line if register holding the condition of but1 is set
"        CALL    ART_IN                 \n" // CALL the function that increments the total count 
"w9:     SBRS    r19, 5              \n" // skip next line if Button 2 is pushed
"        JMP     w10                 \n"  // jump to w9 if button isnt pushed
"        SBRS    r27, 0              \n" // skip next line if register holding the condition of but2 is set
"        CALL    AZT_IN                \n" // CALL the function that decrements the total count
"w10:    SBRS    r19,4               \n" // skip next line if Button 1 is pushed
"        CLR     r26                 \n" // clear register holding the condition of but1 
"        SBRS    r19, 5              \n" // skip next line if Button 2 is pushed
"        CLR     r27                 \n" // clear register holding the condition of but2
// BUTTONS 3-4 
/*
"        SBRS    r22, 4                 \n" //DOESNT WORK
"        JMP     t9                \n" //DOESNT WORK
"        SBRS    r28, 0               \n" //DOESNT WORK
"        CALL    ART_TI                 \n"  //DOESNT WORK
"t9:     SBRS    r22, 5              \n"  //DOESNT WORK
"        JMP     t10                 \n" //DOESNT WORK
"        SBRS    r29, 0              \n" //DOESNT WORK
"        CALL    AZT_TI                \n"  //DOESNT WORK
"t10:    SBRS    r22,4               \n" //DOESNT WORK
"        CLR     r28                 \n" //DOESNT WORK
"        SBRS    r22, 5              \n" //DOESNT WORK
"        CLR     r29                 \n" //DOESNT WORK
*/    
//----------------------------------------------
"        DEC     r21                 \n" // decrement register to count number of loops
"        CPI     r21, 0              \n" // compare r21 with 0
"        BREQ    hun_milis           \n" // branch if 100ms passed
" w11:   CPI     r17, 0              \n" // compare timer holding register with 0
"        BREQ    adder             \n" //branch if period is completed to display number
//"        OUT     0x08, r20         \n" // PORTC <- r20
"        JMP     LOOP                \n" // Restart loop
  );

}