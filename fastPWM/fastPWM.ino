
/*
this is an arduino style code
orignal from https://www.gadgetronicx.com/attiny85-pwm-tutorial-phase-correct-fast-mode/
*/

// this one is set from the  arduino tools-board section
//#include<avr/io.h>
//#define F_CPU 16500000UL

void PWM_config()
{
  DDRB = (1 << PB1) | (1 << PB0); // set PB1 and PB0 as output to enable PWM generation
  TCCR0A = 0x00;                  // Normal mode
  TCCR0A |= (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1) | (1 << COM0A0) | (1 << COM0B0);
  TCCR0B = 0x00;
  TCCR0B |= (1 << CS00) | (1 << CS02); // prescaling with 1024
  TCNT0 = 0;
  OCR0A = 150; // Generating PWM of 58.9% duty cycle from OC0A
  OCR0B = 250; // Generating PWM of 98% duty cycle from OC0B
}
void setup() {
}
void loop()
{
  PWM_config();
}
