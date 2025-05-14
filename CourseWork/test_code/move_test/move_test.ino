// PWM
#define PWM1_PIN            5
#define PWM2_PIN            6      
// 
#define SHCP_PIN            2                               //
#define EN_PIN              7                               // 
#define DATA_PIN            8                               // 
#define STCP_PIN            4                               //                  

const int Forward       = 92;                               // 
const int Backward      = 163;                              // 
const int Turn_Left     = 149;                              // 
const int Turn_Right    = 106;                              // 
const int Top_Left      = 20;                               // 
const int Bottom_Left   = 129;                              // 
const int Top_Right     = 72;                               // 
const int Bottom_Right  = 34;                               // 
const int Stop          = 0;                                // 
const int Contrarotate  = 172;                              // 
const int Clockwise     = 83;                               // 

void setup()
{
    pinMode(SHCP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(STCP_PIN, OUTPUT);
    pinMode(PWM1_PIN, OUTPUT);
    pinMode(PWM2_PIN, OUTPUT);
}

void loop()
{
    /* Forward */
    Motor(Forward, 250);     
    delay(2000);
    /* Backward */
    Motor(Backward, 250);
    delay(2000);
    /* Turn_Left */
    Motor(Turn_Left, 250);
    delay(2000);
    /* Turn_Right */
    Motor(Turn_Right, 250);
    delay(2000);
    /* Top_Left */
    Motor(Top_Left, 250);
    delay(2000);
    /* Bottom_Right */
    Motor(Bottom_Right, 250);
    delay(2000);
    /* Bottom_Left */
    Motor(Bottom_Left, 250);
    delay(2000);
    /* Top_Right */
    Motor(Top_Right, 250);
    delay(2000);
    /* Clockwise */
    Motor(Clockwise, 250);
    delay(2000);
    /* Contrarotate */
    Motor(Contrarotate, 250);
    delay(2000);
    /* Stop */
    Motor(Stop, 250);
    delay(2000);
}

void Motor(int Dir, int Speed)
{
    digitalWrite(EN_PIN, LOW);
    analogWrite(PWM1_PIN, Speed);
    analogWrite(PWM2_PIN, Speed);

    digitalWrite(STCP_PIN, LOW);
    shiftOut(DATA_PIN, SHCP_PIN, MSBFIRST, Dir);
    digitalWrite(STCP_PIN, HIGH);
}