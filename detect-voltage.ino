#define OUTPUT_PIN 2        // Pin providing power to the breadboard
#define SENSE_PIN1 32       // Analog pin to sense current in wire 1
#define SENSE_PIN2 33       // Analog pin to sense current in wire 2

#define OUTPUT_PIN2 4

void setup() {
  Serial.begin(115200);

  // Set up OUTPUT_PIN to provide power
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, HIGH);  // Turn on power to the breadboard

  pinMode(OUTPUT_PIN2, OUTPUT);

  // Set up sense pins as inputs
  pinMode(SENSE_PIN1, INPUT);
  pinMode(SENSE_PIN2, INPUT);
}

void loop() {
  int sensorValue1 = analogRead(SENSE_PIN1);
  int sensorValue2 = analogRead(SENSE_PIN2);

  // Convert the analog reading to voltage (for a 3.3V ESP32, use a factor of 3.3/4095)
  float voltage1 = sensorValue1 * (3.3 / 4095.0);
  float voltage2 = sensorValue2 * (3.3 / 4095.0);

  if ((voltage1 > 1) && (voltage2 > 1)) {
    Serial.println("CORRECT KEY");
    digitalWrite(OUTPUT_PIN2, HIGH);
  } else {
    Serial.println("WRONG KEY");
    digitalWrite(OUTPUT_PIN2, LOW);
  }

  delay(1000);  // Wait a second before reading again
}

void printVoltageInfo(float voltage1, float voltage2) {
  // Output the results
  Serial.print("Voltage across wire 1: ");
  Serial.print(voltage1);
  Serial.println(" V");

  Serial.print("Voltage across wire 2: ");
  Serial.print(voltage2);
  Serial.println(" V");

  // Determine if current is flowing (current above 1V threshold)
  if (voltage1 > 1) {
      Serial.println("Current detected in wire 1");
  } else {
      Serial.println("No current in wire 1");
  }

  if (voltage2 > 1) {
      Serial.println("Current detected in wire 2");
  } else {
      Serial.println("No current in wire 2");
  }
}
