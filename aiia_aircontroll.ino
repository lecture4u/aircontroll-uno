/* servo motor configuration
 *
 * pin: analog 9
 * power: 5v
 * GND
 * 
 * light sensor configuration
 * 
 * pin: A0
 * power: 3.2v
 * GND
 * 
 */

#include <Servo.h>
// number of pin connected to Servo is analog 9
int servoPin = 9;

// light sensor cds pin is A0
int cds = A0;

// actuator configuration
Servo servo;
int angle = 0;
bool isOff = false;

// latency configuration(ms)
int latency = 500;

// data handling configuration
int rawInput[5] = {0,};
int refinedInput[3] = {0,};
int refinedCount = 0;

/*********************************************/

void setup() {
  Serial.begin(9600); // to check status of cds through serial communication
  servo.attach(servoPin);
}

/*********************************************/

// actuator control
void pushButton() {
  for(angle = 25; angle > 0; angle--) {
    servo.write(angle);
    delay(15);
  }
}

void retreat() {
  // sacn from 0 to 180 degrees
  for(angle = 0; angle < 25; angle++) {
    servo.write(angle);
    delay(15);
  }
}

void controlActuator() {
  pushButton();
  retreat();
}

int getAverageFromRawInput() {
  int sum = 0;
  for(int i = 4; i > -1; i--) {
    sum += rawInput[i];
  }
  return sum/5;
}

void addToRefined(int refinedData) {
  int length = sizeof(refinedInput);
  for(int i = 0; i < length-1; i++) {
    refinedInput[i] = refinedInput[i+1];  
  }
  refinedInput[2] = refinedData;
}

int getAverageFromRefined() {
  int sum = 0;
  for(int i = 2; i > -1; i--) {
    sum += refinedInput[i];
  }
  return sum/3;
}

void addToRaw() {
  for(int i = 4; i > -1; i--) {
    int cdsValue = analogRead(cds);
    Serial.print("cds=");
    Serial.println(cdsValue);
    rawInput[i] = cdsValue;  
    delay(latency);  
  }
}

/*********************************************/

void loop() {

  addToRaw();
  
  int rawAverage = getAverageFromRawInput();
  Serial.print("raw average= ");
  Serial.println(rawAverage);
  addToRefined(rawAverage);

/* spec out. no need for sliding window
  int refinedAverage = getAverageFromRefined();
  Serial.print("refined= ");
  Serial.println(refinedAverage);
*/

  // the more light exists, the lower the value is
  // the value 500 is heuristically decided by experiment.
  // cds sensor was under black-room condition
  if(rawAverage > 500) {
    //airconditioner is not working
    controlActuator();
  }
  // else airconditioner is working
}
