#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <FirebaseESP8266HTTPClient.h>
#include <FirebaseFS.h>
#include <FirebaseJson.h>

// Configure Firebase Variables
#define FIREBASE_HOST "esp-1st-project.firebaseio.com"
#define FIREBASE_AUTH "LJTM2sDQv2ehHguRXcXtwtPBMdGCDJTJ50FTBMVz"
#define WIFI_SSID "Refaey"
#define WIFI_PASSWORD "Body@12345"

// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

String myString;
int ThermistorPin = A0;         // Thermistor connected
int sdata = 0;       // The variable resistor value will be stored in sdata.

int V_out;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup()
{
    // Debug console
    Serial.begin(115200);
    pinMode(ThermistorPin , INPUT);
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
    // Read Data from the sensor
    sdata = analogRead(ThermistorPin);

    // Convert Analoag Reading to Temperature
    V_out = analogRead(ThermistorPin);
    R2 = R1 * (1023.0 / (float)V_out - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
    T = T - 273.15;
    
    Serial.println(T);
    
    if (Firebase.setFloat(firebaseData, "/Reading", T)) {
        // Success
        Serial.println("Set int data success");
    } else {
        // Failed?, get the error reason from firebaseDate
        Serial.print("Error in setInt, ");
        Serial.println(firebaseData.errorReason());
    }
  
    delay(200);
}
