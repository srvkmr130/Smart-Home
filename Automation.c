#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "93c7a5b2b60846d39a7e7e11c8b*****";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SHUBHASHIS";
char pass[] = "123456789";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}

