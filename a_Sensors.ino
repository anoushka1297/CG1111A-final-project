
//----------------------//
// Ultrasonic Sensor    //
//----------------------//

float readUltrasonic() {
  pinMode(ultrasonicPin, OUTPUT);
  digitalWrite(ultrasonicPin, LOW);  // Set trigger LOW to ensure a clean pulse start

  delayMicroseconds(2);
  digitalWrite(ultrasonicPin, HIGH);  // Send 10µs pulse to trigger ultrasonic sensor
  delayMicroseconds(10);
  digitalWrite(ultrasonicPin, LOW);  // Turn off pulse

  pinMode(ultrasonicPin, INPUT);                                    // Switch to read echo signal
  long duration = pulseIn(ultrasonicPin, HIGH, ultrasonicTimeout);  // Measure echo duration

  if (duration == 0)
    return -1;  // Return -1 if no wall detected (out of range)

  // Convert pulse duration to distance in cm: distance = (time/2) * speed of sound
  return duration / 2.0 / 1000000 * SPEED_OF_SOUND * 100;
}


//---------------------------//
// IR Sensor (Right Wall)    //
//---------------------------//

int readIR() {
  LED_IR_Driver.dWrite1(HIGH);  // Turn off IR emitter (baseline)
  LED_IR_Driver.dWrite2(HIGH);
  delay(IRDelay);
  double base = AnalogReader.aRead1();  // Baseline voltage with no reflection

  LED_IR_Driver.dWrite1(LOW);  // Turn on IR emitter
  LED_IR_Driver.dWrite2(LOW);
  delay(IRDelay);
  double value = AnalogReader.aRead1();  // Measure reflected IR light

  return base - value;  // Difference = reflected intensity, higher means closer wall
}


//---------------------------//
// LDR (Light Sensor)        //
//---------------------------//

int readLDR(int n) {
  int sum = 0;  // Sum of n readings to compute average and reduce noise
  for (int i = 0; i < n; i++) {
    sum += AnalogReader.aRead2();  // Read LDR voltage corresponding to reflected LED light
    delay(LDRDelay);
  }
  return sum / n;  // Return averaged value for more stable color detection
}
