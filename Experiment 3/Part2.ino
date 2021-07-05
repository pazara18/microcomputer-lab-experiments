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
"		RET						\n"
//Increment Function
"inc7: 	IN	 r25,  0x05			\n" // r25<- PORTB
"		ANDI r25,  0b00001111	\n"	// Get only seven segment bits
"		INC  r25				\n" // Increment first digit
"		LDI	 r24,  0b00001010	\n" // r24 <- 10
"		CP	 r25,  r24			\n" // Compare r25 - r24
"		BRNE incB				\n" // Jump incC if portB!=10
"		LDI  r25,  0b00000000   \n" // Clear R25 if r25==10
"	 	IN	 r23,  0x08			\n" // r23<- PORTC
"		ANDI r23,  0b00001111	\n"	// Get only seven segment bits
"		INC  r23				\n" // Increment first digit
"		CP	 r23,  r24			\n" // Compare r23 - r24
"		BRNE incC				\n" // Jump incC if portC !=10
"		LDI  r23,  0b00000000   \n" // Clear r25 if r25==10
"incC:  IN   r24,  0x08			\n" // Get r24<-PORTC
"		ANDI r24,  0b11110000	\n" // Clear r24 left 4 bit
"		OR	 r23,  r24			\n" // Write to new 7seg value
"		OUT  0x08, r23			\n" // Write portc new value
"incB:  IN   r24,  0x05			\n" // Get r24<-PORTB
"		ANDI r24,  0b11110000	\n" // Clear r24 left 4 bit
"		OR	 r25,  r24			\n" // Write to new 7seg value
"		OUT  0x05, r25			\n" // Write portb new value
"		RET						\n"
//Decrement Function
"dec7: 	IN	 r25,  0x05			\n" // r25<- PORTB
"		ANDI r25,  0b00001111	\n"	// Get only seven segment bits
"		DEC  r25				\n" // Decrement first digit
"		BRPL incB				\n" // Jump decC if portB>=0
"		LDI  r25,  0b00001001   \n" // Clear R25 if r25 10
"	 	IN	 r23,  0x08			\n" // r23<- PORTC
"		ANDI r23,  0b00001111	\n"	// Get only seven segment bits
"		DEC  r23				\n" // Decrement first digit
"		BRPL incC				\n" // Jump decC if portC>=0
"		LDI  r23,  0b00001001   \n" // Clear r25 if r25 10
"decC:  IN   r24,  0x08			\n" // Get r24<-PORTC
"		ANDI r24,  0b11110000	\n" // Clear r24 left 4 bit
"		OR	 r23,  r24			\n" // Write to new 7seg value
"		OUT  0x08, r23			\n" // Write portc new value
"decB:  IN   r24,  0x05			\n" // Get r24<-PORTB>=0
"		ANDI r24,  0b11110000	\n" // Clear r24 left 4 bit
"		OR	 r25,  r24			\n" // Write to new 7seg value
"		OUT  0x05, r25			\n" // Write portb new value
"		RET						\n"
    
    
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

"		IN 	 r16,  0x05     	\n" //r16 <- PORTB   
"		ANDI r16,  0b11110000	\n"	//Clear r16[3:0] for 7-segment
"		OUT  0x05, r16			\n" //PORTB <- r16
    
"		IN 	 r16,  0x08     	\n" //r16 <- PORTC   
"		ANDI r16,  0b11110000	\n"	//Clear r16[3:0] for 7-segment
"		OUT  0x08, r16			\n" //PORTC <- r16  
"       LDI  r20,  0b00000000	\n" // Use r20 as led flag
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
"		call inc7				\n"//Increment seven segment
"		ORI	 r20, 0b00010000 	\n"//Set status bit
"		JMP btn2				\n"//Jump to check btn2
"b1z:	ANDI r20, 0b11101111	\n"//Clear status bit
"btn2:  MOV  r18, r20			\n"//Copy r20 to r18 
"       ANDI r16, 0b00100000	\n"//Get Only Second button bit
"       ANDI r18, 0b00100000	\n"//Get Only Second button status bit    
"		EOR	 r18, r16			\n"//Check Second button status is changed
"		BREQ cont				\n"//Branch cont if state is same
"		AND  r16, r16			\n"//Check r16 is zero or not
"		BREQ b2z				\n"//Branch if r17 zero
"		call dec7				\n"//Decrement seven segment
"		ORI	 r20, 0b00100000 	\n"//Set status bit
"		JMP cont				\n"//Jump to check btn2
"b2z:	ANDI r20, 0b11011111	\n"//Clear status bit


"cont:		CALL d_1ms			\n" //Wait 1 ms
";Your LOOP Code End			\n" 
"		JMP  LOOP				\n"
);
  
}
