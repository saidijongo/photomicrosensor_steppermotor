void moveMotor(int stepTarget, int speedPercent) {
  int speed = map(speedPercent, 0, 100, 5000, 800);
  _step_delay = speed;

  // Calculate the target position in steps
  int targetSteps = stepTarget;

  // Determine the direction to move
  bool isClockwise = (_step_current_position < targetSteps);

  _motorState = isClockwise ? MotorState::MOVING_CW : MotorState::MOVING_CCW;

  while (_step_current_position != targetSteps) {
    bool sleft = digitalRead(LEFT_SENSOR_PIN) == LOW;
    bool sright = digitalRead(RIGHT_SENSOR_PIN) == LOW;

    // Detect sensors
    if (sleft || sright) {
      stopMotor();
      delay(1000); // Stop for 1 second

      // Move back slightly
      if (isClockwise) {
        motorStep(true, SENSOR_BACK_STEP); // Rotate 8 degrees CCW
      } else {
        motorStep(false, SENSOR_BACK_STEP); // Rotate 8 degrees CW
      }

      delay(1000); // Stop for 1 second
      return;
    }

    motorStep(isClockwise, 1); // Rotate 1 step

    if (_step_current_position >= _step_end_position) {
      return;
    }

    if (_step_current_position <= _step_start_position) {
      return;
    }
  }
}
