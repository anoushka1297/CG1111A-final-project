//---------------------------//
// Line Sensor Handling      //
//---------------------------//

void handleLineDetection() {
  int state = lineSensor.readSensors();  // Check S1/S2 line states

  if (state == S1_IN_S2_IN) {  // Both sensors detect black line
    leftWheelMotor.stop();
    rightWheelMotor.stop();

    LED_IR_Driver.dWrite1(LOW);  // Turn off LEDs before color sensing
    LED_IR_Driver.dWrite2(LOW);
    delay(50);

    performColorAction();  // Run color detection and appropriate action

  } else if (state == S1_OUT_S2_OUT) {  // Both sensors detect white
    followWalls();                      // Continue wall following
  }
}

//---------------------------//
// Wall-Following Movement   //
//---------------------------//

void followWalls() {
  float distance = readUltrasonic();
  if (distance < 0 || distance > 15)  // Out of range readings
    distance = targetLeftWallDist;    // Default to target distance for safe motion

  float deviationUS = targetLeftWallDist - distance;  // Left wall deviation
  float correctionUS = -Kp_ultrasonic * deviationUS;  // Apply proportional correction
  if (abs(deviationUS) < wallDistanceTolerance)
    correctionUS = 0;  // Ignore small deviations

  int irValue = readIR();
  float deviationIR = targetRightWallIR - irValue;  // Right wall deviation
  float correctionIR = -Kp_infrared * deviationIR;  // Proportional correction

  float totalCorrection = correctionUS + correctionIR;  // Combine both walls

  int leftSpeed = constrain(baseMotorSpeed - totalCorrection, -255, 255);   // Correct left motor
  int rightSpeed = constrain(baseMotorSpeed + totalCorrection, -255, 255);  // Correct right motor

  leftWheelMotor.run(-leftSpeed * 1.5);  // Apply corrected speed
  rightWheelMotor.run(rightSpeed * 1.5);

  delay(10);  // Short delay for smooth motion
}