

//ATtiny85 - DRV8833 motor control (speed/direction)

//                        +-\/-+
//                 Reset 1|    |8  VCC
// SW1 Dir. in 3 A3  PB3 2|    |7  PB2 out 2 (NC) - maybe NEOpixel for Rec/Play
//Pot1 spd. in 4 A2  PB4 3|    |6  PB1 out 1 Fast PWM, DRV8833 Ain1
//                   GND 4|    |5  PB0 out 0 Fast PWM, DRV8833 Ain2
//                        ------

#define F_CPU 8000000  // This is used by delay.h library
// #define F_CPU 16500000UL

#include <stdlib.h>
#include <avr/io.h>        // Adds useful constants
#include <util/delay.h>    // Adds delay_ms and delay_us functions

//ATtiny85 - DRV8833 motor control (speed/direction)

// LED output pins:
const int FETdriverA1 = 0;      // (0, IC pin 5)
const int FETdriverA2 = 1;      // (1, IC pin 6)
const int SW1         = 3;      // Direction Switch
const int PotPin1     = 4;      // Speed Pot.

int sensorValue = 0;



// the setup routine runs once when you press reset:
void setup()  { 
   // from https://www.re-innovation.co.uk/docs/fast-pwm-on-attiny85/
    /*
    Control Register A for Timer/Counter-0 (Timer/Counter-0 is configured using two registers: A and B)
    TCCR0A is 8 bits: [COM0A1:COM0A0:COM0B1:COM0B0:unused:unused:WGM01:WGM00]
    2<<COM0A0: sets bits COM0A0 and COM0A1, which (in Fast PWM mode) clears OC0A on compare-match, and sets OC0A at BOTTOM
    2<<COM0B0: sets bits COM0B0 and COM0B1, which (in Fast PWM mode) clears OC0B on compare-match, and sets OC0B at BOTTOM
    3<<WGM00: sets bits WGM00 and WGM01, which (when combined with WGM02 from TCCR0B below) enables Fast PWM mode
    */
    TCCR0A = 2<<COM0A0 | 2<<COM0B0 | 3<<WGM00;
   
    /*
    Control Register B for Timer/Counter-0 (Timer/Counter-0 is configured using two registers: A and B)
    TCCR0B is 8 bits: [FOC0A:FOC0B:unused:unused:WGM02:CS02:CS01:CS00]
    0<<WGM02: bit WGM02 remains clear, which (when combined with WGM00 and WGM01 from TCCR0A above) enables Fast PWM mode
    1<<CS00: sets bits CS01 (leaving CS01 and CS02 clear), which tells Timer/Counter-0 to not use a prescalar
    */
    TCCR0B = 0<<WGM02 | 1<<CS00;
   
    /*
    Control Register for Timer/Counter-1 (Timer/Counter-1 is configured with just one register: this one)
    TCCR1 is 8 bits: [CTC1:PWM1A:COM1A1:COM1A0:CS13:CS12:CS11:CS10]
    0<<PWM1A: bit PWM1A remains clear, which prevents Timer/Counter-1 from using pin OC1A (which is shared with OC0B)
    0<<COM1A0: bits COM1A0 and COM1A1 remain clear, which also prevents Timer/Counter-1 from using pin OC1A (see PWM1A above)
    1<<CS10: sets bit CS11 which tells Timer/Counter-1  to not use a prescalar
    */
    TCCR1 = 0<<PWM1A | 0<<COM1A0 | 1<<CS10;
   
    /*
    General Control Register for Timer/Counter-1 (this is for Timer/Counter-1 and is a poorly named register)
    GTCCR is 8 bits: [TSM:PWM1B:COM1B1:COM1B0:FOC1B:FOC1A:PSR1:PSR0]
    1<<PWM1B: sets bit PWM1B which enables the use of OC1B (since we disabled using OC1A in TCCR1)
    2<<COM1B0: sets bit COM1B1 and leaves COM1B0 clear, which (when in PWM mode) clears OC1B on compare-match, and sets at BOTTOM
    */
    GTCCR = 1<<PWM1B | 2<<COM1B0;
  
    /*
    analog ref 
    ADMUX |= (1 << REFS1);   //use internal reference voltage of 1.1V
    */

    // Set up IO pins
    pinMode(FETdriverA1, OUTPUT);
    pinMode(FETdriverA2, OUTPUT);  
    
    pinMode(PotPin1, INPUT);
    pinMode(SW1, INPUT_PULLUP);
    
    digitalWrite(FETdriverA1, LOW);   //  Switch the FET OFF
    digitalWrite(FETdriverA2, LOW);   //  Switch the FET OFF

} 

// the loop routine runs over and over again forever:
void loop()  { 

  // sensorValue = map(analogRead(PotPin1), 0, 1023, 5, 250);
  // int val = analogRead(PotPin1);
  int vall = map(analogRead(PotPin1), 0, 1023, 5, 250);

  if (digitalRead(SW1)) {
    analogWrite(FETdriverA1, vall);    // Set it to 50%  running at 31.2kHz  
    digitalWrite(FETdriverA2, LOW); 
  }else{
    digitalWrite(FETdriverA1, LOW);    // Set it to 50%  running at 31.2kHz  
    analogWrite(FETdriverA2, vall); 
  }
}