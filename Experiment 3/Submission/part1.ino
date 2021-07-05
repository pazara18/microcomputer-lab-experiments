void setup()
{
  asm(
"        JMP start                \n"
"delay: LDI     r23,  81            \n"    //Delay 1 sec
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
"EX:        ROL     r16                \n"//Extra shift if carry=1
";Your Functions Code End        \n"
"start:                            \n" //Write your code
"        IN   r16,  0x0A ;        \n" //r16 <- DDRD
"        LDI  r16,  0xFF            \n"    //r16[0] <- 1
"        LDI  r17,  0x01         \n" // r17[0] <- 1
"        OUT  0x0A, r16           \n" //DDRD <- r16
"        OUT  0x0B, r17          \n"// PORTD <- r17
  );

}

void loop()
{
  asm(
"LOOP:                              \n"
"        CALL delay                 \n"    //Call delay function
"        IN      r16,  0x0B ;        \n"    //r16 <- PORTD 
"        ROL     r16                \n"    //CSL r16
"         BRCS   EX                     \n"    //Branch if C=1
"        OUT  0x0B, r16             \n"    //PORTD <- r16
"        JMP  LOOP                  \n"       //continue loop
  );

}