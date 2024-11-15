// Defines pins numbers for Sensor 1
const int trigPin1 = 9;
const int echoPin1 = 10;
// Defines pins numbers for Sensor 2
const int trigPin2 = 5;
const int echoPin2 = 6;
// Pin definitions for the Buzzers, LED, and Vibration Motor
const int passiveBuzzer = 12;  // KY-006 Passive Buzzer connected to pin 12
const int activeBuzzer = 11;   // Normal Active Buzzer connected to pin 11
const int vibrationMotor = 7;  // Vibration motor connected to pin 7
// Defines variables for distance calculation
long duration1, duration2;
int distance1, distance2;
int safetyDistance1, safetyDistance2;
void setup() {
  // Sensor 1 setup
  pinMode(trigPin1, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin1, INPUT);  // Sets the echoPin1 as an Input
  // Sensor 2 setup
  pinMode(trigPin2, OUTPUT); // Sets the trigPin2 as an Output
  pinMode(echoPin2, INPUT);  // Sets the echoPin2 as an Input
  // Buzzer, LED, and Vibration Motor setup
  pinMode(passiveBuzzer, OUTPUT);   // Sets passive buzzer as output
  pinMode(activeBuzzer, OUTPUT);    // Sets active buzzer as output
  pinMode(vibrationMotor, OUTPUT);  // Sets vibration motor pin as an Output
  // Starts the serial communication for monitoring
  Serial.begin(9600);
}

void loop() {
  // Clears the trigPin1 and trigPin2
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sends the pulse from trigPin1 for Sensor 1
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin1, gets the time for sound wave to return
  duration1 = pulseIn(echoPin1, HIGH);
  // Sends the pulse from trigPin2 for Sensor 2
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin2, gets the time for sound wave to return
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance for both sensors
  distance1 = duration1 * 0.034 / 2;  // Distance in cm for Sensor 1
  distance2 = duration2 * 0.034 / 2;  // Distance in cm for Sensor 2
  // Setting the safety distance to trigger alarms
  safetyDistance1 = distance1;
  safetyDistance2 = distance2;
  // Check safety distance for both sensors
  if (safetyDistance1 <= 5 || safetyDistance2 <= 5) {
    // If either sensor detects an object closer than 5 cm, activate alarms
    digitalWrite(vibrationMotor, HIGH);     // Turn on the vibration motor
    // Activate both Passive and Active Buzzers
    tone(passiveBuzzer, 1000);  // Generates a tone at 1000 Hz for the passive buzzer
    digitalWrite(activeBuzzer, HIGH);  // Turns on the active buzzer
  } else {
    // Otherwise, deactivate all alarms
    digitalWrite(vibrationMotor, LOW);     // Turn off the vibration motor
    // Deactivate both Passive and Active Buzzers
    noTone(passiveBuzzer);  // Stops the tone for the passive buzzer
    digitalWrite(activeBuzzer, LOW);  // Turns off the active buzzer
  }
  // Prints the distances from both sensors to the Serial Monitor
  Serial.print("Distance from Sensor 1: ");
  Serial.println(distance1);
  Serial.print("Distance from Sensor 2: ");
  Serial.println(distance2);
  delay(100);  // Delay between readings
}
