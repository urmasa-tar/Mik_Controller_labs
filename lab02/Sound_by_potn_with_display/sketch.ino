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

int D1=3;
int D2=4;
int D3=5;
int D4=6;
int A=13;
int B=12;
int C=11;
int D=10;
int E=9;
int F=8;
int G=7;
int DP=2;
int digitpins[]={D1,D2,D3,D4};
int segmentpins[]={A,B,C,D,E,F,G,DP}; //g,f,e,d,c,b,a,dp
const String digits[]={"11111100","01100000","11011010","11110010", "01100110","10110110","10111110",
"11100000","11111110","11110110","1100111", "1110111", "1111100", "0111001", "1011110","1111001","1110001"};
//#define LEN(x) sizeof(x)/sizeof(x[0])
int lenDigitpins=4;
int lenSegmentpins=7;
int counter = 0;
int displaydigits[]={1,2,3,4};
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

  /*for (int i = 0; i < 4; i++) {
      pinMode(digitPins[i], OUTPUT);
      digitalWrite(digitPins[i], digitOFF);
   }*/

  for (int i=0;i<4;i++) //LEN(digitpins
    { 
      pinMode(digitpins[i],OUTPUT);
      digitalWrite(digitpins[i],HIGH);
    }
  for (int i=0;i<8;i++) //LEN(segmentpins
    pinMode(segmentpins[i],OUTPUT);
  Serial.begin(9600); // Fix output Serial bug
}

void clearScreen(){
  for (int i=0;i<lenDigitpins;i++ ){ 
    digitalWrite(digitpins[i],LOW);

    for (int j=0;j<lenSegmentpins;j++)
      digitalWrite(segmentpins[j],LOW);
    
    digitalWrite(digitpins[i],HIGH);
    }
}

void printdigit(int pos, int i){

  //Serial.println(digits[i]);
  digitalWrite(digitpins[pos],LOW);
  for (int j=0; j<lenSegmentpins; j++){
      if (digits[i].charAt(j)=='1')
        digitalWrite(segmentpins[j],HIGH);
      else digitalWrite(segmentpins[j],LOW);
    }
  
  //digitalWrite(digitpins[pos],HIGH);
}

void test(){
    // put your main code here, to run repeatedly:
for (int i=0;i<lenDigitpins;i++ )
  { digitalWrite(digitpins[i],LOW);
   for (int j=0;j<lenSegmentpins;j++)
       digitalWrite(segmentpins[j],HIGH);
  }
}
void display2(int counter){
  String s=String("0000")+String(counter);
  s=s.substring(s.length()-4);
  int digit;
  Serial.println(s);
  for (int i=0; i<s.length();i++){
    digit=int(s.charAt(i))-48;
   displaydigits[i]= digit;
   Serial.print(i);
   Serial.print(" ");
   Serial.println(digit);
  }
   long int time=millis();
  while(millis()-time<2000)
  for (int i=0; i<4; i++){
  clearScreen();
  printdigit(i,displaydigits[i]);
  clearScreen();
  }
}

void display(int counter){
  
  int digit;
  int divider=0;
  clearScreen();
  for (int i=0;i<4;i++){
    divider=pow(10,(3-i));
    digit = counter % divider;
    counter -= digit*divider;
    clearScreen();
    displaydigits[i]= digit;
    //printdigit(i,digit);
   Serial.print(i);
   Serial.print(" ");
   Serial.println(digit);

  }
  long int time=millis();
  while(millis()-time<2000)
  for (int i=0; i<4; i++){
  printdigit(i,displaydigits[i]);
  clearScreen();
  }
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
