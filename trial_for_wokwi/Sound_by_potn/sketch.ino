#define pot 0
#define BUZZER 1

const int dataPin = 2;   /* DS */
const int clockPin = 3;  /* SHCP */
const int latchPin = 4;  /* STCP */

int pattern = 0b10101010;

/*
byte D1 = 2;
byte D2 = 3;
byte D3 = 4;
byte D4 = 5;
*/ 


byte A = 2;
byte B = 7;
byte C = 8;
byte D = 9;
byte E = 10;
byte F = 11;
byte G = 12;
byte DP = 13; // decimal point

// Define the input pins for the 7-segment display segments.
const int segmentPins[] = {A, B, C, D, E, F, G, DP};

// Define the input pins for the 7-segment display digits.
// sconst int digitPins[] = {D1, D2, D3, D4};

// For common cathode
uint8_t digitON = LOW;
uint8_t digitOFF = HIGH;

uint8_t segmentON = HIGH;
uint8_t segmentOFF = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZER, OUTPUT); // пин со светодиодом — выход
  pinMode(pot, INPUT); // пин с потенциометром - вход


  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);

  for (int i = 0; i < 8; i++) {
      pinMode(segmentPins[i], OUTPUT);
   }
  /*for (int i = 0; i < 4; i++) {
      pinMode(digitPins[i], OUTPUT);
      digitalWrite(digitPins[i], digitOFF);
   }*/
}


void loop() {
  
  // put your main code here, to run repeatedly:
  int val = analogRead(pot);

  //int ValueToBuzzer = map(val/4,0,1023,0,255);
  //analogWrite(BUZZER,ValueToBuzzer);
  // analogWrite(BUZZER, 255);
  Serial.print(val);

  tone(BUZZER, val*5);
  delay(100);

  if(val == 1){
    Serial.print(1);
  }
  /*
  tone(BUZZER, 31);
  delay(1000);

  noTone(BUZZER);
  delay(1000);
  tone(BUZZER, 100, 1000);
  delay(2000);
  */
}
