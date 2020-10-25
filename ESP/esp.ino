#include "lib/FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include "lib/FirebaseESP8266HTTPClient.h"
#include "lib/FirebaseFS.h"
#include "lib/FirebaseJson.h"
// using namespace FirebaseESP8266;

// Set these to run example.
#define FIREBASE_HOST "esp-1st-project.firebaseio.com"
#define FIREBASE_AUTH "LJTM2sDQv2ehHguRXcXtwtPBMdGCDJTJ50FTBMVz"
#define WIFI_SSID "Cold"
#define WIFI_PASSWORD "salah199998"
// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

String myString;
int vr = A0; // variable resistor connected
int sdata = 0; // The variable resistor value will be stored in sdata.

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(vr , INPUT);
  // connect to wifi.
  pinMode(D0, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  // Firebase.push("Variable/Value", "fahad");
}
void loop()
{
  sdata = analogRead(vr);
//  myString = String(sdata);
  Serial.println(sdata);
//  Firebase.setfloat(firebaseData, "Reading/Value", sdata);
    // Firebase.pushString("Variable/Value", myString);
  delay(1000);
}
