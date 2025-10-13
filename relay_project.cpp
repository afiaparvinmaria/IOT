// Pin definitions
#define TRIG_PIN D1
#define ECHO_PIN D2
#define RELAY_PIN D5
#define LED_PIN D6

// Distance threshold in cm
#define DIST_THRESHOLD 20

void setup() {
  Serial.begin(115200);         // NodeMCU default
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // Start with relay and LED off
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  long duration;
  float distance;

  // Trigger ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure echo time
  duration = pulseIn(ECHO_PIN, HIGH);

  // Convert to distance in cm
  distance = (duration * 0.0343) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if object is within threshold
  if (distance > 0 && distance < DIST_THRESHOLD) {
    digitalWrite(RELAY_PIN, HIGH);  // Relay ON
    digitalWrite(LED_PIN, HIGH);    // LED ON
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Relay OFF
    digitalWrite(LED_PIN, LOW);     // LED OFF
  }

  delay(300); // Small delay between readings
}
