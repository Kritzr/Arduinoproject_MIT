#include <Adafruit_Fingerprint.h>

SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);


#define RELAY_PIN       4

#define ACCESS_DELAY    5000


void setup()

{

  // set the data rate for the sensor serial port

  finger.begin(57600);

  delay(5);

  if (finger.verifyPassword())

  {

  }

  else

  {

    while (1) { delay(1); }

  }

 

  pinMode(RELAY_PIN, OUTPUT);

   

}



void loop()

{

  if ( getFingerPrint() != -1)

  {

   

    digitalWrite(RELAY_PIN, HIGH);
    delay(4000);
    digitalWrite(RELAY_PIN, LOW);  

  }  

  delay(50);
 

}



// returns -1 if failed, otherwise returns ID #

int getFingerPrint()

{

  int p = finger.getImage();

  if (p != FINGERPRINT_OK)  return -1;



  p = finger.image2Tz();

  if (p != FINGERPRINT_OK)  return -1;



  p = finger.fingerFastSearch();

  if (p != FINGERPRINT_OK)  return -1;



  // found a match!

  return finger.fingerID;

}