;void setup()
{
  asm(
"		JMP start				\n"
"delay: LDI	 r23,  81			\n"	//Delay 1 sec
"w1:	LDI	 r24,  255 			\n"
"w2:	LDI  r25,  255 			\n"
"w3:	DEC  r25  				\n"
"		BRNE w3					\n"
"		DEC  r24				\n"
"		BRNE w2					\n"
"		DEC  r23				\n"
"       BRNE w1					\n"
"		RET						\n"
";Your Functions Code Begin		\n" //Write your code   
"d_1ms: LDI	 r24,  20 			\n" //~980us delay
"l1:	LDI  r25,  255 			\n"
"l2:	DEC  r25  				\n"
"		BRNE l2					\n"
"		DEC  r24				\n"
"		BRNE l1					\n"
"		RET						\n"	// Return


//Increase Pattern Number
"incPattern:					\n"  //
"		LDI	 r24,  0b00000100	\n" // r24 <- 10
"		CP	 r5,  r24			\n" // Compare r25 - r24
"		BREQ iiC				\n" // Jump iiC if increment number is 10
"    	inc	 r5					\n" // Otherwise, increase increment number
"		IN   r24,  0x05			\n" // Get r24<-PORTC
"		ANDI r24,  0b11110000	\n" // Clear r24 left 4 bit
"		OR	 r24,  r5			\n" // Write to new 7seg value
"		OUT  0x8, r24			\n" // Write portC new value
"iiC:	RET    					\n" // Return

//Decrement Pattern Number    
"decPattern:					\n"
"		LDI	 r24,  0b00000001	\n" // r24 <- 11
"		CP	 r5,  r24			\n" // Compare r25 - r24
"		BREQ iiC				\n" // Jump decIC if increment number is 1
"    	dec	 r5					\n" // Otherwise, decrease increment number
"		IN   r24,  0x08			\n" // Get r24<-PORTC
"		ANDI r24,  0b11110000	\n" // Clear r24 left 4 bit
"		OR	 r24,  r5			\n" // Write to new 7seg value
"		OUT  0x08, r24			\n" // Write portC new value
"decIC:	RET    					\n" // Return


//Increase Period Number
"incPeriod:						\n"  //
"		LDI	 r24,  0b00001001	\n" // r24 <- 10
"		CP	 r6,  r24			\n" // Compare r25 - r24
"		BREQ incP				\n" // Jump incP if increment number is 10
"    	inc	 r6					\n" // Otherwise, increase period number
"		IN   r24,  0x05			\n" // Get r24<-PORTC
"		ANDI r24,  0b11110000	\n" // Clear r24 left 4 bit
"		OR	 r24,  r6			\n" // Write to new 7seg value
"		OUT  0x05, r24			\n" // Write portC new value
"incP:	RET    					\n" // Return

//Decrement Period Number    
"decPeriod:						\n"
"		LDI	 r24,  0b00000001	\n" // r24 <- 11
"		CP	 r6,  r24			\n" // Compare r25 - r24
"		BREQ decP				\n" // Jump decP if period number is 1
"    	dec	 r6					\n" // Otherwise, decrease period number
"		IN   r24,  0x05			\n" // Get r24<-PORTC
"		ANDI r24,  0b11110000	\n" // Clear r24 left 4 bit
"		OR	 r24,  r6			\n" // Write to new 7seg value
"		OUT  0x05, r24			\n" // Write portC new value
"decP:	RET    					\n" // Return
//Tick 1 Ms Function
"tick: 	INC  r8					\n" // Increase r8 (Tick number for each 1 ms)
"		LDI	 r24,  100			\n" // r24 <- 100
"		CP	 r8,  r24			\n" // Compare r25 - r24
"		BRNE retT				\n" // Jump retT if Tick1ms!=100
"		SUB  r8,  r24		    \n" // R25-10 if r25>=10
"		INC  r7					\n" // Increment r7 (Tick number for each 100 ms)
"		CP	 r7,  r6			\n" // Compare r7 and r6 (Period Number)
"		BRLO retT				\n" // Jump retT if Tick100ms<PeriodNumber
"		SUB  r7,  r7		    \n" // Clear r7 if r7==Period Number
"		LDI  r24, 0b00000001	\n" // r24 <- 1
"		MOV	 r9,  r24			\n" // Set new Operation flag to increase seven seg
"retT:	RET						\n"	// Return

"pat1:  CP 	 r10, r5			\n" // Check pattern is changed
"		BREQ pat1C				\n" // Continue new pattern 
"		LDI  r24, 0b00000001	\n" // r24 <- 1
"		MOV  r11, r24			\n" // r11 =1 (Direction_up)
"       MOV  r10, r5			\n" // set previous part as current
"    	JMP  pat1S				\n" // Go to show op.
"pat1C: IN   R24, 0x0B			\n" // R24 <- PORTD 
"    	AND  r11, r11			\n" // Check direction register
"		BRNE pat1U				\n" // If direction=1 branch pat1U
"		LSR  R24				\n" // Shift right R24
"    	LDI  r23, 0b00000001    \n" // r23 <- 1
"       CP   r23, r24			\n" // check LSB is 1
"		BRNE pat1S				\n" // Branch pat1s if not equal
"		INC	 r11				\n" // Set the direction register
"    	JMP  pat1S				\n" // Go to show op.
"pat1U:	LSL  R24				\n" // Shift left R24
"    	LDI  r23, 0b10000000    \n" // r23 <- 1
"       CP   r23, r24			\n" // check LSB is 1
"		BRNE pat1S				\n" // Branch pat1s if not equal
"		DEC	 r11				\n" // Set the direction register
"pat1S: OUT  0x0B, r24 			\n" // Store the led value
"		RET						\n"	// Return

"pat2:  CP 	 r10, r5			\n" // Check pattern is changed
"		BREQ pat2C				\n" // Continue new pattern 
"		LDI  r24, 0b10000000	\n" // r24 <- 10000000
"       MOV  r10, r5			\n" // set previous part as current
"    	JMP  pat2S				\n" // Go to show op.
"pat2C: IN   r24, 0x0B			\n" // r24 <- PORTD 
"		LDI  r23, 0b00000001	\n" // r23 <- 1
"    	CP	 r24, r23			\n" // check r23, r24
"		BREQ pt2R				\n" // branch if LSB is 1
"		LSR  R24				\n" // Shift right R24
"		JMP  pat2S				\n" // JMP pat2S
"pt2R:  	LDI  r24, 0b10000000    \n" // r23 <- 10000000 to restart pattern
"pat2S: OUT  0x0B, r24 			\n" // Store the led value
"		RET						\n"	// Return

"pat3:  CP 	 r10, r5			\n" // Check pattern is changed
"		BREQ pat3C				\n" // Continue new pattern 
"		LDI  r24, 0b00000000	\n" // r24 <- 10000000
"       MOV  r10, r5			\n" // set previous part as current
"		LDI  r23, 0b00000001    \n" // left shift reg
"       MOV  r12, r23			\n" // Store using r12
"		LDI  r23, 0b10000000    \n" // Right shift reg
"       MOV  r13, r23			\n" // Store using r13
"    	JMP  pat3S				\n" // Go to show op.
"pat3C: IN   r24, 0x0B			\n" // r24 <- PORTD 
"       EOR  r24, r12			\n" // EXOR for toggle bits
"       EOR  r24, r13			\n" // EXOR for toggle bits
"		LDI  r23, 0b00000001	\n" // r23 <- 1
"    	CP	 r13, r23			\n" // check r13, r23
"		BRNE pt3Sh				\n" // branch pat3S if Right shift register is not end point
"		LDI  r23, 0b00000001    \n" // left shift reg
"       MOV  r12, r23			\n" // Store using r12
"		LDI  r23, 0b10000000    \n" // Right shift reg
"       MOV  r13, r23			\n" // Store using r13
"		JMP  pat3S				\n" // JMP pat2S
"pt3Sh: LSL  r12				\n" // Left shift r12
"		LSR  r13				\n" // Right shift r13
"pat3S: OUT  0x0B, r24 			\n" // Store the led value
"		RET						\n"	// Return
    
    

"pat4:  CP 	 r10, r5			\n" // Check pattern is changed
"		BREQ pat4C				\n" // Continue new pattern 
"		LDI  r24, 0b00000001	\n" // r24 <- 1
"		MOV  r11, r24			\n" // r11 =1 (Direction_up)
"       MOV  r10, r5			\n" // set previous part as current
"    	JMP  pat4S				\n" // Go to show op.
"pat4C: IN   R24, 0x0B			\n" // R24 <- PORTD 
"    	AND  r11, r11			\n" // Check direction register
"		BRNE pat4U				\n" // If direction=1 branch pat1U
"		LSR  R24				\n" // Shift right R24
"       BREQ pt4D				\n"	// BranchIf right shift generates zero
"    	LDI  r23, 0b00010000    \n" // r23 <- 1
"       CP   r23, r24			\n" // check LSB is 1
"		BRNE pat4S				\n" // Branch pat1s if not equal
"		INC	 r11				\n" // Set the direction register
"		JMP  pat4S				\n" // JMP pat4S
"pt4D:  LDI  r24, 0b10000000    \n" // Set MSB  		
"    	JMP  pat4S				\n" // Go to show op.
"pat4U:	LSL  R24				\n" // Shift left R24
"       BREQ pt4U2				\n"	// BranchIf left shift generates zero
"    	LDI  r23, 0b00001000    \n" // r23 <- 1
"       CP   r23, r24			\n" // check LSB is 1
"		BRNE pat4S				\n" // Branch pat1s if not equal
"		DEC	 r11				\n" // Set the direction register
"		JMP   pat4S				\n" // JMP pat4S
"pt4U2: LDI  r24, 0b00000001    \n" //  Set LSB  		
"pat4S: OUT  0x0B, r24 			\n" // Store the led value
"		RET						\n"	// Return


    
    
";Your Functions Code End		\n" 
"start:							\n" //Write your code
";Your Setup Code Begin			\n"    
"		IN 	 r16,  0x04     	\n" //r16 <- DDRB   
"		ORI	 r16,  0b00001111	\n"	//Set r16[3:0] for 7-segment
"		ANDI r16,  0b11001111	\n"	//Clear r16[5:4] for input
"		OUT  0x04, r16			\n" //DDRB <- r16

"		IN 	 r16,  0x07     	\n" //r16 <- DDRC   
"		ORI	 r16,  0b00001111	\n"	//Set r16[3:0] for 7-segment
"		OUT  0x07, r16			\n" //DDRC <- r16

"		LDI  r16,  0b11111111	\n"	//Set r16[7:0] for output
"		OUT  0x0A, r16			\n" //DDRD <- r16
"		LDI  r16,  0b00000001   \n" //r16 <- 1
"		OUT  0x0B, r16			\n" //PORTD <- 1 	    
"       MOV	 r11,  r16    		\n" //Set direction register for up op.
    
"		IN 	 r16,  0x08     	\n" //r16 <- PORTC   
"		ANDI r16,  0b11110000	\n"	//Clear r16[3:0] for 7-segment
"		OUT  0x08, r16			\n" //PORTC <- r16  
"       LDI  r20,  0b00000000	\n" // Use r20 as PINB Status Reg
"       LDI  r21,  0b00000000	\n" // Use r21 as PINC Status Reg
"		LDI  r16,  0x01			\n" // r16<- 1
"		MOV	 r5, r16			\n" // r5 is Pattern Number, (default 1)
"		MOV	 r10, r16			\n" // r10 is Previous Pattern Number, (default 1)
"		LDI  r16,  0x5			\n" // r16<- 5
"		MOV	 r6, r16			\n" // r6 is Change Period, (default 5; 5 means 500ms)
"		LDI  r16,  0x0			\n" // r16<- 0
"		MOV	 r7, r16			\n" // r7 is Tick Number for each 100 ms
"		MOV	 r8, r16			\n" // r8 is Tick Number for each 1 ms
"		MOV	 r9, r16			\n" // NewOperation Flag, Counter will icrease when it is 1

"		IN   r24,  0x05			\n" // Get r24<-PORTB
"		ANDI r24,  0b11110000	\n" // Clear r24 left 4 bit
"		OR	 r24,  r6			\n" // Write to new 7seg value
"		OUT  0x05, r24			\n" // Write portb new value
"		IN   r24,  0x08			\n" // Get r24<-PORTC
"		ANDI r24,  0b11110000	\n" // Clear r24 left 4 bit
"		OR	 r24,  r5			\n" // Write to new 7seg value
"		OUT  0x08, r24			\n" // Write portc new value
    
";Your Setup Code End			\n" 
  );

}

void loop()
{ 
  
  asm(
"LOOP:							\n"//Write your code
";Your LOOP Code Begin			\n"  
"   	IN 	 r16, 0x03			\n"//r16<- PINB
"   	MOV  r17, r16			\n"//Copy r16 to r17    
"       MOV  r18, r20			\n"//Copy r20 to r18 
"       ANDI r17, 0b00010000	\n"//Get Only First button bit
"       ANDI r18, 0b00010000	\n"//Get Only First button status bit    
"		EOR	 r18, r17			\n"//Check first button status is changed
"		BREQ btn2				\n"//Branch btn2 if state is same
"		AND  r17, r17			\n"//Check r17 is zero or not
"		BREQ b1z				\n"//Branch if r17 zero
"		call decPattern			\n"//Decrease pattern number
"		ORI	 r20, 0b00010000 	\n"//Set status bit
"		JMP btn2				\n"//Jump to check btn2
"b1z:	ANDI r20, 0b11101111	\n"//Clear status bit
"btn2:  MOV  r18, r20			\n"//Copy r20 to r18 
"       ANDI r16, 0b00100000	\n"//Get Only Second button bit
"       ANDI r18, 0b00100000	\n"//Get Only Second button status bit    
"		EOR	 r18, r16			\n"//Check Second button status is changed
"		BREQ btn3				\n"//Branch cont if state is same
"		AND  r16, r16			\n"//Check r16 is zero or not
"		BREQ b2z				\n"//Branch if r17 zero
"		call incPattern			\n"//Increase Increment Number
"		ORI	 r20, 0b00100000 	\n"//Set status bit
"		JMP btn3				\n"//Jump to check btn2
"b2z:	ANDI r20, 0b11011111	\n"//Clear status bit

"btn3: 	IN 	 r16, 0x06			\n"//r16<- PINC
"   	MOV  r17, r16			\n"//Copy r16 to r17    
"       MOV  r18, r21			\n"//Copy r21 to r18 
"       ANDI r17, 0b00100000	\n"//Get Only Third button bit
"       ANDI r18, 0b00100000	\n"//Get Only Third button status bit    
"		EOR	 r18, r17			\n"//Check third button status is changed
"		BREQ btn4				\n"//Branch btn4 if state is same
"		AND  r17, r17			\n"//Check r17 is zero or not
"		BREQ b3z				\n"//Branch if r17 zero
"		call decPeriod			\n"//Increase period number
"		ORI	 r21, 0b00100000 	\n"//Set status bit
"		JMP btn4				\n"//Jump to check btn2
"b3z:	ANDI r21, 0b11011111	\n"//Clear status bit
"btn4:  MOV  r18, r21			\n"//Copy r20 to r18 
"       ANDI r16, 0b00010000	\n"//Get Only Fourth button bit
"       ANDI r18, 0b00010000	\n"//Get Only Fourth button status bit    
"		EOR	 r18, r16			\n"//Check Fourth button status is changed
"		BREQ cont				\n"//Branch cont if state is same
"		AND  r16, r16			\n"//Check r16 is zero or not
"		BREQ b4z				\n"//Branch if r17 zero
"		call incPeriod			\n"//Decrease Increment Number
"		ORI	 r21, 0b00010000 	\n"//Set status bit
"		JMP cont				\n"//Jump to check btn2
"b4z:	ANDI r21, 0b11101111	\n"//Clear status bit    
"cont:  AND	 r9, r9				\n"//Check r9 is set (New Operation)
"    	BREQ dly				\n"//Go to delay if r9 is not set
"       SUB  r9, r9             \n"// Clear new operation flag
"		LDI  r16, 0b00000001	\n" // r16 <- 1
"		CP   r5,  r16			\n" // check part number is 1
"       BRNE cp2				\n" // If not equal check second part
"		CALL pat1				\n" // call pat1 if part number is 1
"		JMP dly					\n" // Jump delay
"cp2:	LDI  r16, 0b00000010	\n" // r16 <- 2
"		CP   r5,  r16			\n" // check part number is 2
"       BRNE cp3				\n" // If not equal check third part
"		CALL pat2				\n" // call pat2 if part number is 2
"		JMP dly					\n" // Jump delay
"cp3:   LDI  r16, 0b00000011	\n" // r16 <- 3
"		CP   r5,  r16			\n" // check part number is 3
"       BRNE pt4				\n" // If not equal go to pt4
"		CALL pat3				\n" // call pat3 if part number is 3
"		JMP dly					\n" // Jump delay
"pt4:   CALL pat4				\n" // Call pat 4   
"dly:	CALL d_1ms   			\n" //Wait 1 ms
"       CALL tick				\n" //Call tick to count wait time and generate operation flag
";Your LOOP Code End			\n" 
"		JMP  LOOP				\n"
);
  
}
