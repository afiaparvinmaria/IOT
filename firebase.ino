#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "BUBT Hardware Lab"
#define WIFI_PASSWORD "bubt1234"

#define API_KEY "AIzaSyBtZ6kzEZ8C0ch2-Ou7fdEBzAap-0EbNUk"
#define DATABASE_URL "https://datafetching-5aa86-default-rtdb.firebaseio.com/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected!");
  Serial.println(WiFi.localIP());

  // Firebase configuration
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  config.timeout.serverResponse = 10 * 1000;

  // Anonymous sign-in (no email/password)
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Anonymous sign-in successful");
  } else {
    Serial.printf("Sign-up failed, reason: %s\n", config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  delay(2000);
}

void loop() {
  if (!Firebase.ready()) {
    Serial.println("Firebase not ready yet");
    delay(2000);
    return;
  }

  if (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0) {
    sendDataPrevMillis = millis();
    Serial.println("Trying to send data...");

    // Write data to Firebase
    if (Firebase.RTDB.setString(&fbdo, "/section", "6")) {
      Serial.println("Data sent successfully");
    } else {
      Serial.println("Send failed: " + fbdo.errorReason());
    }

    // Read data from Firebase
    if (Firebase.RTDB.getString(&fbdo, "/section")) {
      Serial.print("Received: ");
      Serial.println(fbdo.stringData());
    } else {
      Serial.println("Read failed: " + fbdo.errorReason());
    }
  }
}
