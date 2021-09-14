
//#include <FirebaseArduino.h>
//#include <FirebaseCloudMessaging.h>
//#include <FirebaseError.h>
//#include <FirebaseHttpClient.h>
//#include <FirebaseObject.h>

#include <ArduinoJson.h>
#include <Firebase.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#define FIREBASE_HOST "";
#define FIREBASE_AUTH "";
#define WIFI_SSID "Hitmman"
#define WIFI_PASSWORD "1234567890"

//String myString;
//char rdata; //recieved char
//int firstVal, secVal, thirdVal; //sensors
void setup() {
  Serial.begin(9600);
// connect to wifi.
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 Serial.print("connecting");
 while (WiFi.status() != WL_CONNECTED) {
   Serial.print(".");
   delay(500);
 }
 Serial.println();
 Serial.print("connected: ");
 Serial.println(WiFi.localIP());
 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // put your main code here, to run repeatedly:

}
