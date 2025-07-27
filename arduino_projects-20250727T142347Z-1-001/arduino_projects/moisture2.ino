#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

const int AirValue = 620;   // You need to replace this value with Value_1
const int WaterValue = 310;  // You need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent = 0;

const int sensor_pin = A1;   // Soil moisture sensor O/P pin
const int relay_pin = 7;     // Pin connected to the relay module

void setup() {
  Serial.begin(9600);
  pinMode(relay_pin, OUTPUT); // Set relay pin as an output
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
}

void loop() {
  soilMoistureValue = analogRead(sensor_pin);
  Serial.println(soilMoistureValue);

  // Map soil moisture to percentage
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  soilmoisturepercent = constrain(soilmoisturepercent, 0, 100); // Ensure the value is between 0 and 100

  // Display soil moisture on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Moisture Percentage = ");
  display.print(soilmoisturepercent);
  display.print("%");
  display.display();

  // Check soil moisture level and control the relay
  if (soilmoisturepercent < 10) {
    Serial.println("Moisture is less than 10%, turning on the relay to water the plant");
    display.print("Moisture is less than 10%, turning on the relay to water the plant");
    digitalWrite(relay_pin, HIGH);  // Turn on the relay
    delay(5000);  // Run the relay for 5 seconds (adjust as needed)
    digitalWrite(relay_pin, LOW);   // Turn off the relay
    Serial.println("Watering complete");
    display.print("Watering complete");
  }

  delay(5000);
}
