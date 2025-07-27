#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

const int AirValue = 249;   // You need to replace this value with Value_1
const int WaterValue = 199;  // You need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent = 0;

const int sensor_pin = A1; /* Soil moisture sensor O/P pin */
const int relay_pin = 6;
void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
}

void loop() {
  soilMoistureValue = analogRead(A0);
  Serial.println(soilMoistureValue);
  soilmoisturepercent = map(soilMoistureValue,AirValue, WaterValue,  0, 100);

  // Rest of your existing code...

  // Additional code for soil moisture percentage display on the OLED
  float moisture_percentage;
  //int sensor_analog=0;
  //sensor_analog = analogRead(sensor_pin);
  //moisture_percentage = (100 - ((soilMoistureValue / 1023.00) * 100));


  // Display on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Water me!");
  //display.print("Moisture Percentage = ");
  display.print(soilmoisturepercent);
  //display.print("%");
  Serial.println(soilMoistureValue);
  // Update the display
  display.display();
  if (soilmoisturepercent < 5) {
    Serial.println(soilmoisturepercent);
    Serial.println("Moisture is less than 20%, turning the relay to operate the motor");
    analogWrite(relay_pin, 0);  // Turn on the relay
    delay(5000);  // Run the relay for 5 seconds (adjust as needed
    //digitalWrite(relay_pin, LOW);   // Turn off the relay
    Serial.println("Motor operation complete");
    display.print("Watering");
  }
  else{
    //Serial.println("Moisture is more than 20");
    analogWrite(relay_pin,1023);
    display.print("Watering");

  }

  delay(1000);
}
