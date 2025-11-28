#include <Ultrasonic.h>
#include <Servo.h>
#include <PID_v1.h>
#include <ResponsiveAnalogRead.h>

// Pin assignments
const int servoPin = 9;
const int triggerPin = 12;
const int echoPin = 11;

// Distance range for the PID controller
const int minDistance = 3;
const int maxDistance = 30;

const int printInterval = 500; // Print sensor readings every 500 milliseconds (0.5 seconds)

// PID constants
const float Kp = 2.5;
const float Ki = 0.2;
const float Kd = 0.7;

// PID variables
double setpoint, input, output;

// Objects
PID pidController(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
ResponsiveAnalogRead analogDistance(0, true);
Servo servo;
Ultrasonic ultrasonic(triggerPin, echoPin);

// Reads and filters the distance from the ultrasonic sensor
float readDistance() {
  int rawDistance = ultrasonic.read();
  analogDistance.update(rawDistance);
  int filteredDistance = analogDistance.getValue();
  return filteredDistance;
}

// Prints the raw and filtered sensor readings to the serial monitor
void printMonitor() {
  Serial.print(ultrasonic.read());
  Serial.print("\t");
  Serial.print(analogDistance.getValue());
  Serial.println("");
  delay(printInterval);
}


void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pidController.SetMode(AUTOMATIC);
  pidController.SetOutputLimits(-90, 90);
}

void loop() {
  setpoint = 8;
  input = readDistance();

  // Check if the distance is 0 (sensor failure)
  if (input == 0) {
    // Set the servo to a fixed angle or turn it off
    servo.write(0);
  }
  else {
    pidController.Compute();
    servo.write(output);
  }

  printMonitor();
  delay(printInterval);
}

