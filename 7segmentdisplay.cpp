// Segment pins: A, B, C, D, E, F, G
const int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8};

// Decimal point pin
const int dpPin = 9;

// Buzzer pin
const int buzzerPin = 9;

// The digit at which the buzzer should beep
const int buzzerTriggerDigit = 8;
const int buzzerDigit = 5;



// Digit segment map: A, B, C, D, E, F, G
const byte digits[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  // Setup segment pins
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  pinMode(dpPin, OUTPUT);
  digitalWrite(dpPin, LOW); // DP off

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); // Buzzer off
}

void displayDigit(int digit) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digits[digit][i]);
  }

  digitalWrite(dpPin, LOW); // Optional: DP stays off
}

void beepBuzzer(int durationMs) {
  digitalWrite(buzzerPin, HIGH);
  delay(durationMs);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  for (int i = 0; i < 10; i++) {
    displayDigit(i);

    if (i == buzzerTriggerDigit) {
      beepBuzzer(50); // Buzzer beeps for 200ms
    }
    if (i == buzzerDigit) {
      beepBuzzer(50); // Buzzer beeps for 200ms
    }

    delay(1000); // Wait 1 second before next number
  }
}
