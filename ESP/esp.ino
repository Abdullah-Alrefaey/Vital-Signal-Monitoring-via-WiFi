#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <FirebaseESP8266HTTPClient.h>
#include <FirebaseFS.h>
#include <FirebaseJson.h>

// Configure Firebase Variables
#define FIREBASE_HOST "esp-1st-project.firebaseio.com"
#define FIREBASE_AUTH "LJTM2sDQv2ehHguRXcXtwtPBMdGCDJTJ50FTBMVz"
#define WIFI_SSID "Cold"
#define WIFI_PASSWORD "salah199998"

// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

String myString;
int vr = A0;         // variable resistor connected
int sdata = 0;       // The variable resistor value will be stored in sdata.

void setup()
{
    // Debug console
    Serial.begin(115200);
    pinMode(vr , INPUT);
    pinMode(D0, OUTPUT);
  
    // connect to wifi.
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
        
    // Enable auto reconnect the WiFi when connection lost
    Firebase.reconnectWiFi(true);
}


void loop()

{
    sdata = analogRead(vr);
    Serial.println(sdata);
    
    if (Firebase.setFloat(firebaseData, "/Reading", sdata)) {
        // Success
        Serial.println("Set int data success");
    } else {
        // Failed?, get the error reason from firebaseDate
        Serial.print("Error in setInt, ");
        Serial.println(firebaseData.errorReason());
    }
  
    delay(200);
}
