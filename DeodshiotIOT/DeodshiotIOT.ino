/*
  Deodshiot · A Light Triggered Air Freshener
  https://github.com/benjaminbellamy/Deodshiot
  
  Uploads telemetry to ThingsBoard using MQTT.
  See https://thingsboard.io/docs/reference/mqtt-api/#telemetry-upload-api for more details
*/

#include "ThingsBoard.h"
#include <ESP8266WiFi.h>
#include "Credentials.h"

#define RELAY_PIN D3               // Pin number for relay
#define SWITCH1_PIN D1             // Pin number for sliding switch
#define SWITCH2_PIN D2             // Pin number for sliding switch
#define SENSOR_PIN A0             // Pin number for light sensor
#define NUM_VAL 20                // How many values we will store
#define DELAY 50                  // Delay between each reading. If latency is 1000ms, then DELAY should be equal to (1000/NUMVAL)
#define THRESHOLD 50              // What threshold value (old value minus current value) will trigger
#define MAX_FREQUENCY1 1800000    // How often (once every 30mn) do we allow triggering
#define MAX_FREQUENCY2 300000     // How often (once every 5mn) do we allow triggering
#define MAX_FREQUENCY3 30000      // How often (once every 30s) do we allow triggering
#define MIN_DURATION1 300000      // How long (during at least 5mn) should the light stay on to allow triggering
#define MIN_DURATION2 180000      // How long (during at least 3mn) should the light stay on to allow triggering
#define MIN_DURATION3 5000        // How long (during at least 5s) should the light stay on to allow triggering
#define MOTOR_DELAY 200           // How long the motor will stay on 

// Baud rate for debug serial
#define SERIAL_DEBUG_BAUD   115200

int sensorValues[NUM_VAL];        // create an array for sensor data
int i=0;
unsigned long lastTime = millis()-MAX_FREQUENCY3;
unsigned long switchOnTime = millis();
boolean isLightOn=false;

// Initialize ThingsBoard client
WiFiClient espClient;
// Initialize ThingsBoard instance
ThingsBoard tb(espClient);
// the Wifi radio's status
int status = WL_IDLE_STATUS;

void setup() {
  // initialize serial for debugging
  Serial.begin(SERIAL_DEBUG_BAUD);
  Serial.println("Deodshiot starting...");
  
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);     // turn the motor off
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off
  pinMode(SWITCH1_PIN, INPUT_PULLUP);
  pinMode(SWITCH2_PIN, INPUT_PULLUP);
  digitalWrite(RELAY_PIN, LOW);
  resetValues();
  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  InitWiFi();
}

void loop() {
  unsigned long startLoopTime=millis();
  
  // read the input on analog pin:
  int sensorValue = analogRead(SENSOR_PIN);

  if (WiFi.status() != WL_CONNECTED) {
    reconnect();
  }
  if (!tb.connected()) {
    // Connect to the ThingsBoard
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Failed to connect");
      return;
    }
  }

  // Sets the frequency and duration depending on the sliding switch:
  unsigned long maxFrequency = MAX_FREQUENCY3;
  unsigned long minDuration = MIN_DURATION3;
  unsigned int positionSwitch=3;
  if(!digitalRead(SWITCH1_PIN)){
    maxFrequency = MAX_FREQUENCY1;
    minDuration = MIN_DURATION1;
    positionSwitch=1;
  } else if(!digitalRead(SWITCH2_PIN)){
    maxFrequency = MAX_FREQUENCY2;
    minDuration = MIN_DURATION2;
    positionSwitch=2;
  }

  // Switch ON
  // if the new value is higher that the old one, we store the current time:
  if(sensorValue-sensorValues[i] > THRESHOLD){
      lastTime = millis();
      switchOnTime = lastTime;
      isLightOn=true;
      resetValues();
      tb.sendTelemetryInt("lightOn", 1);
  }

  // Switch OFF
  // if the new value is lower that the old one, trigger is raised:"$
  if(isLightOn && sensorValues[i]-sensorValue > THRESHOLD){
      if((millis()-lastTime)>maxFrequency && (millis()-switchOnTime)>minDuration){
        digitalWrite(RELAY_PIN, LOW);     // turn the motor on
        digitalWrite(LED_BUILTIN, LOW);   // turn the LED on
        delay(MOTOR_DELAY);
        digitalWrite(RELAY_PIN, HIGH);     // turn the motor off
        digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off
        tb.sendTelemetryInt("pschitt", 1);
      }
      lastTime = millis();
      isLightOn=false;
      resetValues();
      tb.sendTelemetryInt("lightOn", 0);
      tb.sendTelemetryInt("lightDuration", (millis()-switchOnTime)/1000);
  }

  // we store the current value on top of the old one:
  sensorValues[i] = sensorValue;

  // We move to the next cell array:
  i=(i+1) % NUM_VAL;

  if((i % NUM_VAL)==0){
    Serial.println((millis()-switchOnTime)/1000);
    tb.sendTelemetryInt("lightValue", sensorValue);
    tb.sendTelemetryInt("positionSwitch", positionSwitch);
  }

  tb.loop();
  
  unsigned long duration=millis()-startLoopTime; 
  if(duration<DELAY){
    delay(DELAY-duration);        // delay in between reads for stability
  }
}

// Reset all values in array :
void resetValues(){
    for (int j=0; j<NUM_VAL; j++) sensorValues[j]=analogRead(SENSOR_PIN);
}

void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}

void reconnect() {
  // Loop until we're reconnected
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    WiFi.begin(WIFI_AP, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connected to AP");
  }
}
