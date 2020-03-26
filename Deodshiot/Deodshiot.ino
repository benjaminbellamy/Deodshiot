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
#define MOTOR_DELAY 500           // How long will the motor stay on 

int sensorValues[NUM_VAL];        // create an array for sensor data
int i=0;
unsigned long lastTime = 0-MAX_FREQUENCY3;

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

  // Sets the frequency depending on the sliding switch:
  unsigned long maxFrequency = MAX_FREQUENCY1;
  if(digitalRead(SWITCH2_PIN)){
    maxFrequency = MAX_FREQUENCY2;
  } else if(digitalRead(SWITCH3_PIN)){
    maxFrequency = MAX_FREQUENCY3;
  }

  // if the new value is lower that the old one, trigger is raised:
  if(sensorValues[i]-sensorValue > THRESHOLD && (millis()-lastTime)>maxFrequency){
      digitalWrite(RELAY_PIN, HIGH);
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(500);
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      lastTime = millis();
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
