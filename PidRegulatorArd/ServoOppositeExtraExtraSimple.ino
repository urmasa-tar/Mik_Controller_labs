#include <Servo.h>
#include <PID_v1.h>

// Define pins for the ultrasonic sensor and servos
const int trigPin = 9;
const int echoPin = 10;
const int servoPin1 = 5;
const int servoPin2 = 6;

// Create Servo objects
Servo myServo1;
Servo myServo2;

// Variables for ultrasonic sensor reading
long duration, distance;

// PID variables
double Setpoint, Input, Output;

// PID tunings
double Kp = 2, Ki = 5, Kd = 1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// Variables for servo position control
int position = 0;
int delta = +1; // controls direction and speed

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servos to pins
  myServo1.attach(servoPin1);
  myServo2.attach(servoPin2);

  // Set initial PID values
  Setpoint = 100; // Desired distance for the sensor

  // Turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop() {
  // Read distance from ultrasonic sensor
  distance = readUltrasonic(trigPin, echoPin);

  // Provide the input to the PID
  Input = distance;

  // Compute the PID output
  myPID.Compute();

  // Set the new positions of the servo motors in the same direction
  int newPosition = position + map(Output, 0, 255, -90, 90); // Adjusting with PID output
  myServo1.write(newPosition); // Move servo 1
  myServo2.write(newPosition); // Move servo 2 in the same direction

  // Calculate new position
  position += delta;
  if (position <= 0 || position >= 180)
    delta = -delta;

  // Control the speed with the delay, about 5 to 100ms
  delay(50);

  // Debugging output
  Serial.print("Distance: "); Serial.print(distance); 
  Serial.print(" PID Output: "); Serial.println(Output);
}

long readUltrasonic(int trigPin, int echoPin) {
  // Clear the trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigger high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance (in cm)
  long distance = (duration / 2) / 29.1;

  return distance;
}
