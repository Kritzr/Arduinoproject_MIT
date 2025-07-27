#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

const int AirValue = 620;   // This is the value for when the sensor is the driest
const int WaterValue = 310;  // This is the value for when the sensor is the wettest
int soilMoistureValue = 0;
int soilmoisturepercent = 0;

const int sensor_pin = A1; /* Soil moisture sensor O/P pin */
const int relay_pin = 7; //relay pin

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
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);

  // Rest of your existing code...

  // Additional code for soil moisture percentage display on the OLED
  float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = (100 - ((sensor_analog / 1023.00) * 100));

  // Display on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Moisture Percentage = ");
  display.print(moisture_percentage);
  display.print("%");

  // Update the display
  display.display();
  if ( moisture_percentage < 5)

  {

   
    analogWrite(relay_pin, 0);
    digitalWrite(relay_pin, HIGH);
    delay(4000);
    digitalWrite(relay_pin, LOW);  

  }  

  

  else{
    analogWrite(relay_pin,1023);

  }

  
  delay(50);
}
