#include <PMsensor.h>

PMsensor PM;

void setup() {
  Serial.begin(9600);
  
  /////(infrared LED pin, sensor pin)  /////
  PM.init(3, A0);          
}

void loop() {
  Serial.println("=================================");
  Serial.println("Read PM2.5");
  
  float data = 0;
  int err = PMsensorErrSuccess;
  if ((err = PM.read(&data, true, 0.1)) != PMsensorErrSuccess) {
    Serial.print("data Error = ");
    Serial.println(err);
    delay(3000);
    return;
  }
  
  Serial.println(data);
  delay(3000);
}
