// PWM control pin
#define PWM1_PIN            5
#define PWM2_PIN            6      
// 74HCT595N Chip pins
#define SHCP_PIN            2                               // The displacement of the clock
#define EN_PIN              7                               // Can make control
#define DATA_PIN            8                               // Serial data
#define STCP_PIN            4                               // Memory register clock                  

const int Forward       = 92;                               // forward
const int Backward      = 163;                              // back
const int Turn_Left     = 149;                              // left translation
const int Turn_Right    = 106;                              // Right translation 
const int Top_Left      = 20;                               // Upper left mobile
const int Bottom_Left   = 129;                              // Lower left mobile
const int Top_Right     = 72;                               // Upper right mobile
const int Bottom_Right  = 34;                               // The lower right move
const int Stop          = 0;                                // stop
const int Contrarotate  = 172;                              // Counterclockwise rotation
const int Clockwise     = 83;                               // Rotate clockwise

// Constants for movement
const int MOVE_SPEED = 200;
const int TURN_SPEED = 200;
const int SIDE_MOVE_SPEED = 200;
const int MOVE_TIME = 1000;     // time to move forward/backward (ms)
const int SIDE_MOVE_TIME = 1000; // time for side movement (ms)
const int TURN_TIME = 500;      // time for 90 degree turn (ms)

// Distance sensor pins and constants
const int TRIG_PIN = 12;
const int ECHO_PIN = 13;
const int OBSTACLE_DISTANCE = 30; // cm - distance to detect obstacle

float getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    float distance = pulseIn(ECHO_PIN, HIGH) / 58.00;
    return distance;
}

void setup() {
    pinMode(SHCP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(STCP_PIN, OUTPUT);
    pinMode(PWM1_PIN, OUTPUT);
    pinMode(PWM2_PIN, OUTPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    Serial.begin(9600);
}

void Motor(int Dir, int Speed) {
    digitalWrite(EN_PIN, LOW);
    analogWrite(PWM1_PIN, Speed);
    analogWrite(PWM2_PIN, Speed);
    digitalWrite(STCP_PIN, LOW);
    shiftOut(DATA_PIN, SHCP_PIN, MSBFIRST, Dir);
    digitalWrite(STCP_PIN, HIGH);
}

void moveForward(int duration) {
    Motor(Forward, MOVE_SPEED);
    delay(duration);
    Motor(Stop, 0);
}

void moveBackward(int duration) {
    Motor(Backward, MOVE_SPEED);
    delay(duration);
    Motor(Stop, 0);
}

void turnLeft() {
    Motor(Contrarotate, TURN_SPEED);
    delay(TURN_TIME);
    Motor(Stop, 0);
}

void turnRight() {
    Motor(Clockwise, TURN_SPEED);
    delay(TURN_TIME);
    Motor(Stop, 0);
}

void moveLeft() {
    Motor(Turn_Left, SIDE_MOVE_SPEED);
    delay(SIDE_MOVE_TIME);
    Motor(Stop, 0);
}

void moveRight() {
    Motor(Turn_Right, SIDE_MOVE_SPEED);
    delay(SIDE_MOVE_TIME);
    Motor(Stop, 0);
}

bool checkObstacle() {
    float distance = getDistance();
    return (distance > 0 && distance < OBSTACLE_DISTANCE);
}

// Spiral search pattern to cover all area
void spiralSearch() {
    int steps = 1;
    int max_steps = 5; // adjust based on room size
    
    while(steps <= max_steps) {
        // Move forward
        for(int i = 0; i < steps; i++) {
            if(checkObstacle()) {
                // Avoid obstacle
                moveBackward(MOVE_TIME/2);
                turnRight();
            } else {
                moveForward(MOVE_TIME);
            }
        }
        
        // Turn right and move sideways
        turnRight();
        moveRight();
        
        // Increase spiral size
        steps++;
    }
}

// Grid search pattern (lawnmower pattern)
void gridSearch() {
    int grid_size = 5; // adjust based on room size
    
    for(int i = 0; i < grid_size; i++) {
        // Move forward in straight line
        for(int j = 0; j < grid_size; j++) {
            if(checkObstacle()) {
                // Avoid obstacle
                moveBackward(MOVE_TIME/2);
                turnRight();
                moveForward(MOVE_TIME/2);
                turnLeft();
            } else {
                moveForward(MOVE_TIME);
            }
        }
        
        // At end of row, turn and move sideways
        if(i % 2 == 0) {
            turnRight();
            moveRight();
            turnRight();
        } else {
            turnLeft();
            moveLeft();
            turnLeft();
        }
    }
}

void loop() {
    // Choose one of the search patterns
    // spiralSearch();
    gridSearch();
    
    // After completing search, return to start (simplified)
    Motor(Stop, 0);
    delay(5000); // wait 5 seconds before starting again
}