#include "PMsensor.h"

PMsensor::PMsensor() {
}

void PMsensor::init(int LEDpin, int sensorPin) {
  _LEDpin = LEDpin;
  _sensorPin = sensorPin;
  pinMode(_LEDpin, OUTPUT);
}


int PMsensor::read(float* pdata, bool isfilter) {
  int ret = PMsensorErrSuccess ;
  digitalWrite(_LEDpin, LOW);
  delayMicroseconds(280);

  rawData = analogRead(_sensorPin);
  delayMicroseconds(40);

  digitalWrite(_LEDpin, HIGH);
  delayMicroseconds(9680);

  val = (0.143 * (rawData * 0.0049) - 0.03) * 1000;
  if(val < -10) {
	  int ret = PMsensorErrDataLow;
	  return ret;
  }
  else {
	*pdata = val;  
  }
  
  return ret;
}


int PMsensor::read(float* pdata, bool isfilter, float sensitivity) {
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

  val = filteredVal;
  if (val < 100) {
    val = val / 4;
  }
  else if (val > 100 && val < 200) {
    val = (val / 4) * 1.15;
  }
  else if (val > 200 && val < 300) {
    val = (val / 4) * 1.15 * 1.3;
  }
  else if (val > 300 && val < 400) {
    val = (val / 4) * 1.15 * 1.3 * 1.45;
  }
  else if (val > 400 && val < 500) {
    val = (val / 4) * 1.15 * 1.3 * 1.45 * 1.6;
  }
  
  if(filteredVal < -10) {
	  int ret = PMsensorErrDataLow;
	  return ret;
  }
  else {
	  *pdata = val;
  }


  return ret;

}

