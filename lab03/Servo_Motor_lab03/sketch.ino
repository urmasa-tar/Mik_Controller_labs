#include <Servo.h>
int servoPin=11;

#define ECHO_PIN 2
#define TRIG_PIN 3

Servo servo1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  servo1.attach(servoPin);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

double readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

int posicion(double dist){
  
  double local_d = dist / 400 * 360;

  servo1.write((int)local_d);

  return 0;
}

int status = 1;

int degree(double ln, int past_deg){ // To set posicion for servo_motor

  int result;

  if (ln <= 20){
    //savve posicion
    result = past_deg;
  }else{
    // count the new one
    result = past_deg + 5 * status;
    if(result >= 140) status = -1;
    if(result <= 40) status = 1;
  }

  return result;
}

int serv_pos = 40;

void loop() {
  // put your main code here, to run repeatedly:

  double distance = readDistanceCM();

  /*
  servo1.write(0);
  delay(5000);
  servo1.write(90);
  delay(5000);
  servo1.write(180);
  delay(5000);
  */

  // positio for servo01
  // 1) First option -> posision calculates by length befor aim
  // posicion(distance);
  
  // 2) Find the nearest aim on robots way
  // Move servo motor untile i will find aim near than 100 cm
  serv_pos = degree(distance, serv_pos);
  servo1.write(serv_pos);

  Serial.print("Measured distance: ");
  Serial.println(readDistanceCM());

  delay(50);
}

