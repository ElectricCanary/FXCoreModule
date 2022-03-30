/*
 * FXCore_Module_Pgm_Selector.c
 *
 * Created: 06/12/2021 21:14:55
 * Author : Antoine Ricoux for Electric Canary
 
 This codeis  shared under a BY-NC-SA Creative Commons License
 Go here for complete license : https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 
 For Attiny202
 Analog value to 4bit value converter to select one of 16 programs from a potentiometer.
 
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define PGM0_PIN 2
#define PGM1_PIN 3
#define PGM2_PIN 6
#define PGM3_PIN 7
#define POT_PIN 1

volatile uint8_t pot;
volatile uint8_t sw;

void IO_Init(void)
{
  //PGM pins as outputs
  VPORTA_DIR |= (1<<PGM0_PIN) | (1<<PGM1_PIN) | (1<<PGM2_PIN) | (1<<PGM3_PIN);
}

void ADC_Init(void)
{
  //Enable ADC, 8-bit, free running mode, VCC as ref
  ADC0_CTRLA |= ADC_ENABLE_bm | ADC_FREERUN_bm | ADC_RESSEL_bm;
  ADC0_CTRLC |= ADC_SAMPCAP_bm | ADC_REFSEL0_bm;
  //Enable result ready interrupt
  ADC0_INTCTRL |= ADC_RESRDY_bm;
  //Interrupts global enable
  sei();
  //Select Channel 1
  ADC0_MUXPOS = 1;
  //Start conversion
  ADC0_COMMAND |= ADC_STCONV_bm;
}

ISR(ADC0_RESRDY_vect)
{
  pot = ADC0_RESL>>4;
}

int main(void)
{
  //Run at 10MHz
  CLKCTRL_MCLKCTRLB = 0;
  IO_Init();
  ADC_Init();
  
    while (1) 
    {
    if(pot & 0b00000001)
    {
      VPORTA_OUT |= (1<<PGM0_PIN);
    }
    
    else
    {
      VPORTA_OUT &= ~(1<<PGM0_PIN);
    }
    
    if(pot & 0b00000010)
    {
      VPORTA_OUT |= (1<<PGM1_PIN);
    }
    
    else
    {
      VPORTA_OUT &= ~(1<<PGM1_PIN);
    }
    
    if(pot & 0b00000100)
    {
      VPORTA_OUT |= (1<<PGM2_PIN);
    }
    
    else
    {
      VPORTA_OUT &= ~(1<<PGM2_PIN);
    }
    
    if(pot & 0b00001000)
    {
      VPORTA_OUT |= (1<<PGM3_PIN);
    }
    
    else
    {
      VPORTA_OUT &= ~(1<<PGM3_PIN);
    }
    }
}
