#include "PMsensor.h"

PMsensor::PMsensor() {
}

void PMsensor::init(int LEDpin, int sensorPin) {
  _LEDpin = LEDpin;
  _sensorPin = sensorPin;
  pinMode(_LEDpin, OUTPUT);
}

float PMsensor::read(float sensitivity) {
  int ret = PMsensorErrSuccess ;
  _sensitivity = sensitivity;
  digitalWrite(_LEDpin, LOW);
  delayMicroseconds(280);

  rawData = analogRead(_sensorPin);
  delayMicroseconds(40);

  digitalWrite(_LEDpin, HIGH); 	 
  delayMicroseconds(9680);

  val = (0.143 * (rawData * 0.0049)-0.03) * 1000;
  float filteredVal = (prevVal * (1 - _sensitivity)) + (val * _sensitivity);
  prevVal = filteredVal;
  float val = filteredVal;

  return val;

}

float PMsensor::read() {
  int ret = PMsensorErrSuccess ;
  digitalWrite(_LEDpin, LOW);
  delayMicroseconds(280);

  rawData = analogRead(_sensorPin);
  delayMicroseconds(40);

  digitalWrite(_LEDpin, HIGH);
  delayMicroseconds(9680);

  val = (0.143 * (rawData * 0.0049) - 0.03) * 1000;

  return val;
  
}
