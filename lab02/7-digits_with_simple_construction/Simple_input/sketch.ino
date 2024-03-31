#define pot 0
#define BUZZER 1

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


void setup() {
  pinMode(BUZZER, OUTPUT); // пин со светодиодом — выход
  pinMode(pot, INPUT); // пин с потенциометром - вход
    // put your setup code here, to run once:
  for (int i=0;i<4;i++) //LEN(digitpins
    { 
      pinMode(digitpins[i],OUTPUT);
      digitalWrite(digitpins[i], LOW);
    }
  for (int i=0;i<8;i++) //LEN(segmentpins
    pinMode(segmentpins[i],OUTPUT);
  Serial.begin(9600);
}

void clearScreen(){
for (int i=0;i<lenDigitpins;i++ )
  { digitalWrite(digitpins[i],LOW);
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

  clearScreen();

// put your main code here, to run repeatedly:
  int val = (int)analogRead(pot);

  //int ValueToBuzzer = map(val/4,0,1023,0,255);
  //analogWrite(BUZZER,ValueToBuzzer);
  // analogWrite(BUZZER, 255);
  Serial.print(val);

  tone(BUZZER, val);
/* 
for (int i=0; i<4; i++){
  printdigit(i,displaydigits[i]);
  clearScreen();
} */
/*
 clearScreen();
  // put your main code here, to run repeatedly:
  int dig_num = 3;
  for(int i = 10; i <= 10000; i *= 10){
    
    printdigit(dig_num, val % i);
    
  }
  */
  printdigit(3, val % 10);
  clearScreen();
  printdigit(2, val % 100 / 10); 
  clearScreen(); 
  printdigit(1, val % 1000 / 100);
  clearScreen();
  printdigit(0, 1);
  clearScreen();
/* 
delay(2000);
clearScreen(); 
delay(2000);
digitalWrite(G,HIGH);
delay(2000);

*/

delay(100);
}

