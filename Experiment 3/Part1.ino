void setup()
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
"								\n"	
";Your Functions Code End		\n" 
"start:							\n" //Write your code
";Your Setup Code Begin			\n"    
"		IN 	 r16,  0x0A     	\n" //r16 <- DDRD   
"		ORI	 r16,  0b11111111	\n"	//r16[0] <- 1
"		OUT  0x0A, r16			\n" //DDRD <- r16
"		LDI	 r16,  0b00000001	\n" //r17 <- 1
"		OUT  0x0B, r16			\n" //PORTD <- r16
";Your Setup Code End			\n" 
  );

}

void loop()
{
  asm(
"LOOP:							\n"//Write your code
";Your LOOP Code Begin			\n"    
"		IN 	 r16,  0x0B 		\n" //r16 <- PORTD  
"		ROL	 r16				\n" //r16 = r16 << 1
"       BRCC CNT				\n"	//if not carry continue
"		ROL  r16				\n"	//if carry, rotate again
"CNT:  	OUT  0x0B, r16			\n" //PORTD <- r16	
"		CALL delay				\n" //Wait 1 sec
";Your LOOP Code End			\n" 
"		JMP  LOOP				\n"
);
  
}
