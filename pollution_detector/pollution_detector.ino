// Pin connections
const int MQ135_PIN = A0;
const int BUZZER_PIN = 9;

// Threshold for high pollution level
const int POLLUTION_THRESHOLD = 200; // Adjust this value according to your needs

// Variables
int pollutionLevel = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set buzzer pin as output
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Read the sensor value
  int sensorValue = analogRead(MQ135_PIN);

  // Convert sensor value to pollution level
  pollutionLevel = map(sensorValue, 0, 1023, 0, 500);

  // Print pollution level to serial monitor
  Serial.print("Pollution Level in PPM:  ");
  Serial.println(pollutionLevel);

  // Check if pollution level exceeds the threshold
  if (pollutionLevel > 200) {
    // Activate the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000); // Buzzer on for 1 second
    digitalWrite(BUZZER_PIN, LOW);
    delay(1000); // Buzzer off for 1 second
  }

  // Delay before next reading
  delay(1000); // Adjust the delay as needed
}