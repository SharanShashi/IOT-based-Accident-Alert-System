#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID           "TMPL3Lzquuw7p"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "Yku4g6RYgv73p1ezGab8gMyh9TaqY6tJ"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Relay PIN
#define RELAY_PIN 5  // D1 for relay

#define SENSE A0 // NodeMCU uses D0 for analog input

// Buzzer PIN
#define BUZZER_PIN 12 // D6 for buzzer

char ssid[] = "Kishor's Galaxy A23 5G"; // Enter your WIFI name
char pass[] = "15082002";   // Enter your WIFI password

BlynkTimer timer;

bool relayActivated = false;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SENSE, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);  // Initially turn off the relay
  digitalWrite(BUZZER_PIN, LOW);  // Initially turn off the buzzer

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Set up a timer to check Blynk app periodically
  timer.setInterval(1000L, checkBlynk);
}

void checkBlynk() {
  // Nothing to check here for now
}

BLYNK_WRITE(V0) {
  // This function will be called every time the virtual pin V0 changes its state
  int relayState = param.asInt();  // Get the new state of the virtual pin

  if (relayState == 1) {
    // Button V0 pressed in the Blynk app, turn on the relay
    digitalWrite(RELAY_PIN, LOW);
    relayActivated = true;
  } else {
    // Button V0 released in the Blynk app, turn off the relay
    digitalWrite(RELAY_PIN, HIGH);
    relayActivated = false;
  }
}

void loop() {
  Blynk.run();
  timer.run();

  if (relayActivated) {
    // Sensor logic only when the relay is activated
    int sensorValue = analogRead(SENSE);
    Serial.println(sensorValue);

    if (sensorValue <= 50) {
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);  // Turn oF buzzer when sensor value is below threshold
    } else {
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);  // Turn on buzzer when sensor value is below threshold
    }
  }
}
