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

int degree(double ln, int past_deg){



  return 0;
}

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

  // position for servo01

  posicion(distance);


  Serial.print("Measured distance: ");
  Serial.println(readDistanceCM());

  delay(1000);
}

