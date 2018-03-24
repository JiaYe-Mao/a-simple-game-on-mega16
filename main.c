/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
� Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 2016/12/17
Author  : GaryMao
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega16.h>

// Alphanumeric LCD Module functions
#include <alcd.h>
#include <delay.h>
#include <stdlib.h>



unsigned char car=0,flag_stage=0;
unsigned char length[4],width[4],str1[3];
unsigned int changce=7,blockCount=0,interval=240;
unsigned int flag_time=0,low=0,i,compare1=8,score=0;

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
   // If button2 pressed
   if(!PIND.2)
   {
       // If the position of the car is 0, then put the car position to 1;
      if((car<1)&&(flag_stage==1))
      {
        car=1;
      }
   }
}

// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
   // If button3 pressed
   if(!PIND.3)
   {
       // If the position of the car is 1, then put the car position to 0;
      if((car>0)&&(flag_stage==1))
      {
        car=0;
      } 
   }
  
}

// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{

    if(flag_stage==1)
    {
        flag_time++;
        // Every (interval * 2 / 16MHz)s time, the blocks move.
        if(flag_time==interval)
        {
            flag_time=0;
            changce++;

            for(i=0;i<3;i++)
            {
                // find the leftmost block
                if(length[i]<length[low])
                {
                    low=i;
                }

            }

            // toggle the flash lights
            PORTA.3=~PORTA.3;
            PORTA.4=~PORTA.4;

            // If the leftmost block appears at the 1st or 2nd position.
            if((length[low]==0)||(length[low]==1))
            {
                // If it collides the car, finish the game.
                if(width[low]==car) flag_stage++;
                else if(length[low]==0)
                {
                    // If it doesn't, set the block to the rightmost, and increase the score.
                    width[low]=1;
                    length[low]=65;
                    score++;
                }
            }

            if(changce==compare1)
            {
                changce=0;
                // The fresh block from right side.
                length[blockCount]=16;
                width[blockCount]=rand()%2;
                compare1=rand()%3+4;
                // The moving speed of blocks are increasing.
                if(interval>100) interval=interval-3;

                // If the block count < 3, then add block count
                if(blockCount<3)blockCount++;
                else blockCount=0;
            }

            // move the blocks to left for 1 cell
            length[0]--;
            length[1]--;
            length[2]--;
            length[3]--;

        }
    }
}

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0x18;

// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0x00;

// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 250.000 kHz
// Mode: CTC top=OCR0
// OC0 output: Disconnected
TCCR0=0x0B;
TCNT0=0x00;
OCR0=0xFA;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: On
// INT1 Mode: Falling Edge
// INT2: Off
GICR|=0xC0;
MCUCR=0x0A;
MCUCSR=0x00;
GIFR=0xC0;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x02;

// USART initialization
// USART disabled
UCSRB=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;

// Alphanumeric LCD initialization
// Connections specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTB Bit 0
// RD - PORTB Bit 1
// EN - PORTB Bit 2
// D4 - PORTD Bit 4
// D5 - PORTD Bit 5
// D6 - PORTD Bit 6
// D7 - PORTD Bit 7
// Characters/line: 16
lcd_init(16);

// Global enable interrupts
#asm("sei")

length[0]=65;
length[1]=65;
width[0]=1;
width[1]=1;
length[2]=65;
length[3]=65;
width[2]=1;
width[3]=1;
PORTA.3=1;
PORTA.4=1;

// Game starts here!
// This is a Finite State Machine(FSM).
// It has three states, which are the start screen, the game and the end respectively
while (1)
    {
        // start screen
        if(flag_stage==0)
        {
            // If one of the buttons is pressed, the game will start.
            if((!PIND.2)||(!PIND.3))flag_stage++;
          
            lcd_gotoxy(0,0);
            lcd_puts("PRESS TO START");
        }
       
        //the game
        if(flag_stage==1)
        {
        
            // Clear the screen, so that the last frame won't be kept on the screen.
            lcd_clear();
            /**
             *  There are always 4 blocks computed,
             *  but they may not on the screen because their x-coordinates may larger than the screen width.
             */
            lcd_gotoxy(length[0],width[0]);
            lcd_putchar(255);
            lcd_gotoxy(length[1],width[1]);
            lcd_putchar(255);
            lcd_gotoxy(length[2],width[2]);
            lcd_putchar(255);
            lcd_gotoxy(length[3],width[3]);
            lcd_putchar(255);
            /**
             *  Shows the car on the screen.
             */
            lcd_gotoxy(0,car);
            lcd_putchar(126);
            lcd_putchar(41);
            lcd_puts(str1);
            /**
             *  A short period of time delay, so that the screen won't flicker.
             */
            delay_ms(33);

        
        }
        
        if(flag_stage==2) 
        {
         
          lcd_clear();
          lcd_gotoxy(3,0);
          lcd_puts("GAME OVER");  
          lcd_gotoxy(0,1);
          lcd_puts("YOUR SCORE:");
          itoa(score,str1);
          lcd_puts(str1);
        }
    }
}