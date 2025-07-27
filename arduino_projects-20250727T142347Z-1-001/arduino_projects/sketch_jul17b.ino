#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

// Fingerprint sensor's RX pin connected to Arduino's D2 pin
// Fingerprint sensor's TX pin connected to Arduino's D3 pin
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// Solenoid lock control pin
const int solenoidPin = 4;

void setup()
{
  Serial.begin(9600);
  pinMode(solenoidPin, OUTPUT);
  digitalWrite(solenoidPin, LOW); // Keep the solenoid lock initially locked

  // Initialize the fingerprint sensor
  finger.begin(57600);
  if (finger.verifyPassword())
  {
    Serial.println("Fingerprint sensor initialized successfully!");
  }
  else
  {
    Serial.println("Couldn't access the fingerprint sensor");
    while (1)
      ; // Loop forever
  }
}

void loop()
{
  getFingerprintID(); // Check for a fingerprint match
  delay(500);         // Delay for stability
}

void getFingerprintID()
{
  uint8_t p = finger.getImage();
  switch (p)
  {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return;
    default:
      Serial.println("Unknown error");
      return;
  }

  // Check if a finger is present and matches with a stored fingerprint
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK)
  {
    Serial.println("Finger found!");
    unlockSolenoid();
  }
  else if (p == FINGERPRINT_NOTFOUND)
  {
    Serial.println("Finger not found");
  }
  else
  {
    Serial.println("Unknown error");
  }
}

void unlockSolenoid()
{
  digitalWrite(solenoidPin, HIGH); // Unlock the solenoid lock
  Serial.println("Solenoid unlocked");
  delay(5000);                     // Keep the solenoid unlocked for 5 seconds
  digitalWrite(solenoidPin, LOW);  // Lock the solenoid lock
  Serial.println("Solenoid locked");
}
