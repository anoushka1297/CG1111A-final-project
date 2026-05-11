//---------------------------//
// Motor helper functions    //
//---------------------------//
void turnLeftTwice() {  // Pink tile
  leftWheelMotor.run(baseMotorSpeed);
  rightWheelMotor.run(baseMotorSpeed);
  delay(turnDuration * 1.2);

  leftWheelMotor.run(-255);
  rightWheelMotor.run(255);
  delay(700);

  leftWheelMotor.run(baseMotorSpeed);
  rightWheelMotor.run(baseMotorSpeed);
  delay(turnDuration * 1.1);
}

void reverseBack() {  // Orange tile
  leftWheelMotor.run(baseMotorSpeed);
  rightWheelMotor.run(baseMotorSpeed);
  delay(2.2 * turnDuration);
}

void turnLeftOnce() {  // Red tile
  leftWheelMotor.run(baseMotorSpeed);
  rightWheelMotor.run(baseMotorSpeed);
  delay(turnDuration);
}

void turnRightOnce() {  // Green tile
  leftWheelMotor.run(-baseMotorSpeed);
  rightWheelMotor.run(-baseMotorSpeed);
  delay(turnDuration);
}

void turnRightTwice() {  // Light Blue tile
  leftWheelMotor.run(-baseMotorSpeed);
  rightWheelMotor.run(-baseMotorSpeed);
  delay(turnDuration * 1.2);

  leftWheelMotor.run(-255);
  rightWheelMotor.run(255);
  delay(730);

  leftWheelMotor.run(-baseMotorSpeed);
  rightWheelMotor.run(-baseMotorSpeed);
  delay(turnDuration);
}

//---------------------------//
// Color sensing and action  //
//---------------------------//
void performColorAction() {
  // Read red
  LED_IR_Driver.dWrite1(HIGH);
  LED_IR_Driver.dWrite2(LOW);
  delay(RGBDelay);
  int R = readLDR(3);

  // Read blue
  LED_IR_Driver.dWrite1(HIGH);
  LED_IR_Driver.dWrite2(HIGH);
  delay(RGBDelay);
  int B = readLDR(3);

  // Read green
  LED_IR_Driver.dWrite1(LOW);
  LED_IR_Driver.dWrite2(HIGH);
  delay(RGBDelay);
  int G = readLDR(3);

  int sum = R + G + B;
  int sumBG = B + G;

  // Decision logic based on thresholds (calibrated based on observation)
  if (sumBG / 2 > 900) {  // WHITE tile (goal)
    playMelody();
  } else if (sum / 3 > 840) {  // PINK tile
    turnLeftTwice();
  } else if (R > G && R > B) {  // RED or ORANGE
    if (sumBG / 2 > 725) {      // ORANGE
      reverseBack();
    } else {  // RED
      turnLeftOnce();
    }
  } else if (G > R && G > B) {  // GREEN
    turnRightOnce();
  } else {  // LIGHT BLUE
    turnRightTwice();
  }
}
