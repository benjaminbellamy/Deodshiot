/*
  Deodshiot · A Light Triggered Air Freshener
  https://github.com/benjaminbellamy/Deodshiot
*/

#define RELAY_PIN 2               // Pin number for relay
#define SWITCH2_PIN 7             // Pin number for relay
#define SWITCH3_PIN 8             // Pin number for relay
#define SENSOR_PIN A0             // Pin number for light sensor
#define NUM_VAL 20                // How many values we will store
#define DELAY 50                  // Delay between each reading. If latency is 1000ms, then DELAY should be equal to (1000/NUMVAL)
#define THRESHOLD 50              // What threshold value (old value minus current value) will trigger
#define MAX_FREQUENCY1 30000      // How often (30s) do we allow triggering
#define MAX_FREQUENCY2 300000     // How often (5mn) do we allow triggering
#define MAX_FREQUENCY3 1800000    // How often (30mn) do we allow triggering
#define MIN_DURATION1 5000        // How long (5s) should the light stay on to allow triggering
#define MIN_DURATION2 180000      // How long (3mn) should the light stay on to allow triggering
#define MIN_DURATION3 300000      // How long (5mn) should the light stay on to allow triggering
#define MOTOR_DELAY 500           // How long will the motor stay on 

int sensorValues[NUM_VAL];        // create an array for sensor data
int i=0;
unsigned long lastTime = millis()-MAX_FREQUENCY3;
unsigned long switchOnTime = millis();
boolean isLightOn=false;


// Reset all values in array :
void resetValues(){
    for (int j=0; j<NUM_VAL; j++) sensorValues[j]=analogRead(SENSOR_PIN);
}

// Setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SWITCH2_PIN, INPUT);
  pinMode(SWITCH3_PIN, INPUT);
  digitalWrite(RELAY_PIN, LOW);
  resetValues();
}

// Loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin:
  int sensorValue = analogRead(SENSOR_PIN);

  // Sets the frequency and duration depending on the sliding switch:
  unsigned long maxFrequency = MAX_FREQUENCY1;
  unsigned long minDuration = MIN_DURATION1;
  if(digitalRead(SWITCH2_PIN)){
    maxFrequency = MAX_FREQUENCY2;
    minDuration = MIN_DURATION2;
  } else if(digitalRead(SWITCH3_PIN)){
    maxFrequency = MAX_FREQUENCY3;
    minDuration = MIN_DURATION3;
  }

  // Switch ON
  // if the new value is higher that the old one, we store the current time:
  if(sensorValue-sensorValues[i] > THRESHOLD){
      lastTime = millis();
      switchOnTime = lastTime;
      isLightOn=true;
      resetValues();
  }

  // Switch OFF
  // if the new value is lower that the old one, trigger is raised:
  if(isLightOn && sensorValues[i]-sensorValue > THRESHOLD){
      if((millis()-lastTime)>maxFrequency && (millis()-switchOnTime)>minDuration){
        digitalWrite(RELAY_PIN, HIGH);     // turn the motor on
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
        delay(500);
        digitalWrite(RELAY_PIN, LOW);     // turn the motor off
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off
      }
      lastTime = millis();
      isLightOn=false;
      resetValues();
  }

  // we store the current value on top of the old one:
  sensorValues[i] = sensorValue;

  // We move to the next cell array:
  i=(i+1) % NUM_VAL;

  // print out the value you read:
  Serial.println(sensorValue);
  delay(DELAY);        // delay in between reads for stability
}
