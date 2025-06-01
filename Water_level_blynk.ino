#define BLYNK_TEMPLATE_ID "TMPL3BaIjomck"
#define BLYNK_TEMPLATE_NAME "Water Level Monitoring System"
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>  //  Use this library for ESP8266
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// Blynk authentication token
char auth[] = "pCL581XbSOYQrzRQ_Ii8i4iC1gzB9csg"; 

// WiFi credentials
char ssid[] = "Realme 9 Pro 5G";
char pass[] = "vinit_2910";

// LCD setup (I2C Address: 0x27)
LiquidCrystal_PCF8574 lcd(0x27); // ESP8266-compatible LCD

// Define water level sensor pins
#define sensorPin1 D1
#define sensorPin2 D2
#define sensorPin3 D3
#define sensorPin4 D4

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  // Initialize LCD
  lcd.begin(16, 2); // Initialize LCD
  lcd.setBacklight(255); // Turn on LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("Water Level:");

  // Set sensor pins as inputs
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
}

void loop() {
  Blynk.run(); // Run Blynk

  int level1 = digitalRead(sensorPin1);
  int level2 = digitalRead(sensorPin2);
  int level3 = digitalRead(sensorPin3);
  int level4 = digitalRead(sensorPin4);

  String waterLevel = "Empty";
  
  if (level1 == HIGH) waterLevel = "Low";
  if (level2 == HIGH) waterLevel = "Medium";
  if (level3 == HIGH) waterLevel = "High";
  if (level4 == HIGH) waterLevel = "Full";

  // Display on LCD
  lcd.setCursor(0, 1);
  lcd.print("Level: ");
  lcd.print(waterLevel);
  lcd.print("    "); // Clear remaining text

  // Send data to Blynk
  Blynk.virtualWrite(V1, waterLevel);
  
  delay(1000); // Delay to avoid rapid updates
}