const int dataPin = 3;  
const int latchPin = 4; 
const int clockPin = 5; 
byte leds = 0;
int currentLED = 0;

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  leds = 0;
}

void loop() {
  writeRegister(B10101010); 
  delay(500);              
  writeRegister(B01010101); 
  delay(500);              
}

void writeRegister(byte data) {
  digitalWrite(latchPin, LOW);

  for (int i = 7; i >= 0; i--) {
    // Установка бита данных на выходе
    digitalWrite(dataPin, bitRead(data, i));
    // Генерация импульса тактового сигнала
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
  }
  digitalWrite(latchPin, HIGH);
}