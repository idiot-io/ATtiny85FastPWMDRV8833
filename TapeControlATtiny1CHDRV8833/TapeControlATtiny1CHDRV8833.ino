//ATtiny85 - DRV8833 motor control (speed/direction)

//                        +-\/-+
//                 Reset 1|    |8  VCC
// SW1 Dir. in 3 A3  PB3 2|    |7  PB2 out 2 (NC) - maybe NEOpixel for Rec/Play
//Pot1 spd. in 4 A2  PB4 3|    |6  PB1 out 1 Fast PWM (AIN_2)
//                   GND 4|    |5  PB0 out 0 Fast PWM (AIN_1)
//                        ------

//CH1

int AIN_1 = 0; //DRV8833 Ain1
int AIN_2 = 1; //DRV8833 Ain2
int SW1 = 3; //Direction Switch
int PotPin1 = 4;  // Speed Pot.


int outputValue1 = 0;        // value output to the PWM (analog out)

void setup() {
  pinMode(SW1, INPUT_PULLUP);
  pinMode(AIN_1, OUTPUT);
  pinMode(AIN_2, OUTPUT);
}

void loop() {

  int outputValue1 = map(analogRead(PotPin1), 0, 1023, 0, 255);
  int Dir1 = digitalRead(SW1);

  // change the analog out value:
  if (Dir1 == 0) {
    analogWrite(AIN_1, outputValue1);
    digitalWrite(AIN_2, LOW);
    delay(2);
  }
  if (Dir1 == 1) {
    digitalWrite(AIN_1, LOW);
    analogWrite(AIN_2, outputValue1 );
    delay(2);
  }
}

