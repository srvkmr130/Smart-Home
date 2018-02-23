#include <SPI.h>
#include "ESP8266WiFi.h"

const char* ssid     = "SHUBHASHIS";
const char* password = "123456789";

const char* server = "api.carriots.com";
const String APIKEY = "f347bae96e7c8cfc1fa73aeb1c410a4cf686c9116a9b2474f7a326cc********";
const String DEVICE = "defaultDevice@srvkmr130.srvkmr130";
WiFiClient client;
int ledpin = 4;//D2
int pirpin = 12;//D6
int pirstate =LOW;
int val = 0;

void setup(){
  Serial.begin(9600);
  delay(10);
  pinMode(ledpin,OUTPUT);
  pinMode(pirpin,INPUT);
   Serial.println("calibrating");
   for(int i = 0; i < 20; i++){
      Serial.print(".");
      delay(1000);
      }
  
  // start wifi

    Serial.println();
    Serial.println();
    Serial.print("Connecting to "); 
   Serial.println(ssid);
   WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  val = digitalRead(pirpin);
  Serial.println(val);
  if(val == HIGH){

    digitalWrite(ledpin,HIGH);
    if (pirstate == LOW){
      Serial.println("Motion Detected");
      pirstate =HIGH;
      Serial.println(F("Send Stream"));
      sendStream();
      delay(3000);
      }
   /*   while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
    delay(30000);
  } */
  }
else{
  digitalWrite(ledpin,LOW);
  if(pirstate == HIGH){
    Serial.println("motion Detected email sent");
    pirstate = LOW;
  }
}
}

// function to talk to the Carriot Platform

void sendStream()
{
  
   String txt = "";          // Text to send
  if ( pirstate == HIGH ) {   // Alarm OFF
     txt = "ALERRT! Motion is Detected";
  } else {                  // Alarm ON
   txt = "Error";
  }
  Serial.println(txt); 
  if (client.connect(server, 80)) {   // If there's a successful connection
    Serial.println(F("connected"));
    // Build the data field
    String json = "{\"protocol\":\"v2\",\"device\":\""+DEVICE+"\",\"at\":1356390000,\"data\":{\"light\":\""+txt+"\"}}";
    // Make a HTTP request
    client.println("POST /streams HTTP/1.1");
    client.println("Host: api.carriots.com");
    client.println("Accept: application/json");
    client.println("User-Agent: Arduino-Carriots");
    client.println("Content-Type: application/json");
    client.print("carriots.apikey: ");
    client.println(APIKEY);
    client.print("Content-Length: ");
    int thisLength = json.length();
    client.println(thisLength);
    client.println("Connection: close");
    client.println();
    client.println(json);
  }
  else {
    // If you didn't get a connection to the server:
    Serial.println(F("connection failed"));
  }

}


