

//ATtiny85 - DRV8833 motor control (speed/direction)

//                        +-\/-+
//                 Reset 1|    |8  VCC
// SW1 Dir. in 3 A3  PB3 2|    |7  PB2 out 2 (NC) - maybe NEOpixel for Rec/Play
//Pot1 spd. in 4 A2  PB4 3|    |6  PB1 out 1 Fast PWM, DRV8833 Ain1
//                   GND 4|    |5  PB0 out 0 Fast PWM, DRV8833 Ain2
//                        ------
#define F_CPU 16500000UL
int SW1 = 3; //Direction Switch
int PotPin1 = 4;  // Speed Pot.
int sensorValue = 0;

void PWM_config()
{
  /*
  fastPWM code and explain from 
  gadgetronicx.com/attiny85-pwm-tutorial-phase-correct-fast-mode/
  */
  DDRB = (1 << PB1) | (1 << PB0); // set PB1 and PB0 as output to enable PWM generation
  TCCR0A = 0x00;                  // Normal mode
  TCCR0A |= (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1) | (1 << COM0A0) | (1 << COM0B0);
  TCCR0B = 0x00;
  TCCR0B = _BV(CS00); //presacle 1
  /*
    Setting                          Prescale_factor
    TCCR0B = _BV(CS00);              1
    TCCR0B = _BV(CS01);              8
    TCCR0B = _BV(CS00) | _BV(CS01);  64
    TCCR0B = _BV(CS02);              256
    TCCR0B = _BV(CS00) | _BV(CS02);  1024
  */
  TCNT0 = 0;
  OCR0A = 0; // Generating PWM of 58.9% duty cycle from OC0A
  OCR0B = 250; // Generating PWM of 98% duty cycle from OC0B
}

void setup(){
  pinMode(SW1, INPUT_PULLUP);
  PWM_config();
}
void loop(){
  sensorValue = map(analogRead(PotPin1), 0, 1023, 5, 250);

  if (digitalRead(SW1)) {
    OCR0A = sensorValue; // Generating PWM  from OC0A
    OCR0B = 0; // Generating PWM  from OC0B
  }else{
    OCR0A = 0; // Generating PWM from OC0A
    OCR0B = sensorValue; // Generating PWM from OC0B
  }
}