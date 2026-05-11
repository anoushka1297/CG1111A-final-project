#include "MeMCore.h"

//----------------------//
// Hardware Definitions //
//----------------------//

MePort LED_IR_Driver(PORT_4);  //Drives 3 LEDs + IR emitter by 2-4 decoding
MePort AnalogReader(PORT_3);   //Reads analog voltage from LDR and IR receiver
MeDCMotor leftWheelMotor(M1);
MeDCMotor rightWheelMotor(M2);
MeLineFollower lineSensor(PORT_1);  //In built line sensor to detect black lines
MeBuzzer buzzer;                    //Buzzer for feedback + goal melody

//--------------------------------//
// Timing and Pin Configuration   //
//--------------------------------//

#define RGBDelay 50             // Delay between enabling an LED and taking an LDR reading
#define LDRDelay 5              // Delay used for averaging LDR readings
#define IRDelay 10              // Settling delay for IR emitter pulsing
#define ultrasonicPin 10        // Ultrasonic trigger/echo pin
#define SPEED_OF_SOUND 340      // Speed of sound in air (m/s)
#define ultrasonicTimeout 2000  // Maximum wait time for ultrasonic echo

//--------------------------------//
// Tunable Parameters             //
//--------------------------------//

const int baseMotorSpeed = 150;  // Baseline forward speed when following walls
const int turnDuration = 460;    // Base Duration used for turning actions on colored tiles

const float targetLeftWallDist = 11.3;    // Target left wall distance in cm used for ultrasonic correction
const float wallDistanceTolerance = 0.8;  // Deadband for ignoring very small distance fluctuations
const float Kp_ultrasonic = 8;            // Proportional gain for ultrasonic left wall correction

float targetRightWallIR = 135;  // Target IR intensity (calibrated value)
float Kp_infrared = 0.6;        // Proportional gain for IR right wall correction
int robotEnabled = 0;           // Flag determining whether the robot is active or idle

//------- SETUP --------//
void setup() {
  Serial.begin(9600);  // Start serial for debugging or calibration
  pinMode(A7, INPUT);  // Configure pushbutton input to toggle ON/OFF
}

//---------------------------//
// Main Loop                 //
//---------------------------//

void loop() {
  if (analogRead(A7) < 100) {  // Pushbutton toggle
    robotEnabled = !robotEnabled;
    delay(500);
  }
  // If robot is enabled, run the navigation logic
  if (robotEnabled) {
    handleLineDetection();  // Manage line detection and color response
    delay(10);
  }

  delay(5);  // Small loop delay
}
