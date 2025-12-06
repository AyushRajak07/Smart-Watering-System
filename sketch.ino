// Smart Plant Watering System with OLED Display + ThingSpeak
// Works perfectly on Wokwi (free tier)

#include <WiFi.h>
#include "ThingSpeak.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED settings (128x64)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pins
const int SOIL_MOISTURE_PIN = 34;        // Analog soil sensor
const int SPRINKLER_PIN = 19;            // Relay or LED for pump/sprinkler

// Thresholds (in percentage)
int THRESHOLD_LOW = 30;     // Turn ON watering below this
int THRESHOLD_HIGH = 75;    // Turn OFF watering above this

bool sprinklerOn = false;

// WiFi & ThingSpeak (Wokwi-GUEST works without password)
const char* WIFI_NAME = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";
unsigned long myChannelNumber = 2564339;
const char* myWriteAPIKey = "3PDPDDF1RA32WIER";

WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Start OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address usually 0x3C
    Serial.println(F("OLED not found! Check wiring"));
    while(1);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(15,20);
  display.println("Plant");
  display.setCursor(10,40);
  display.println("System");
  display.display();
  delay(2000);

  // Connect to WiFi
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,20);
  display.println("Connecting WiFi...");
  display.display();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  display.clearDisplay();
  display.setCursor(0,20);
  display.println("WiFi Connected!");
  display.setCursor(0,40);
  display.print("IP: ");
  display.println(WiFi.localIP());
  display.display();
  delay(2000);

  ThingSpeak.begin(client);
  pinMode(SPRINKLER_PIN, OUTPUT);
  digitalWrite(SPRINKLER_PIN, LOW);
}

void loop() {
  // Read soil moisture (0-4095 → 0-100%)
  int raw = analogRead(SOIL_MOISTURE_PIN);
  int moisturePercent = map(raw, 0, 4095, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);

  // Control sprinkler (pump/relay)
  if (moisturePercent < THRESHOLD_LOW && !sprinklerOn) {
    sprinklerOn = true;
    digitalWrite(SPRINKLER_PIN, HIGH);
  }
  else if (moisturePercent > THRESHOLD_HIGH && sprinklerOn) {
    sprinklerOn = false;
    digitalWrite(SPRINKLER_PIN, LOW);
  }

  // Update OLED Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Smart Plant Monitor");

  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print("Moist: ");
  display.print(moisturePercent);
  display.println("%");

  display.setCursor(0, 45);
  if (moisturePercent < THRESHOLD_LOW) {
    display.println(" Watering!");
  } else if (moisturePercent > THRESHOLD_HIGH) {
    display.println(" Soil Good");
  } else {
    display.println(" Watering ON");
  }

  // Show sprinkler status with icon
  display.setTextSize(2);
  display.setCursor(100, 45);
  display.println(sprinklerOn ? "ON" : "OFF");

  display.display();

  // Print to Serial Monitor too
  Serial.print("Moisture: ");
  Serial.print(moisturePercent);
  Serial.print("% | Sprinkler: ");
  Serial.println(sprinklerOn ? "ON" : "OFF");

  // Send to ThingSpeak
  ThingSpeak.setField(1, moisturePercent);
  ThingSpeak.setField(2, sprinklerOn ? 1 : 0);
  int response = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (response == 200) {
    Serial.println("ThingSpeak update OK");
  } else {
    Serial.println("ThingSpeak error: " + String(response));
  }

  delay(15000); // ThingSpeak free tier: min 15 seconds
}
