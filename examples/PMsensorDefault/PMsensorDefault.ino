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

  float filter_Data = PM.read(0.1);
  //float noFilter_Data = PM.read();

  Serial.print("Filter : ");
  Serial.println(filter_Data);
  //Serial.print("noFilter : ");
  //Serial.println(noFilter_Data);

  
  delay(1000);
}
