#include "EnvShieldSensors.h"
#include <Arduino_MKRENV.h>
#include <Arduino.h>

const int MAX_RETRIES = 5;

EnvShieldSensors::EnvShieldSensors() :
  temperature(0), humidity(0), pressure(0),
  illuminance(0) {}

void EnvShieldSensors::init(){
  int retries = 1;
  while (!begin() && retries++ <= MAX_RETRIES) 
  {
    Serial.println("Failed to initialize MKR ENV shield!");
    Serial.println(String("Retry attempt: ") + retries + "/" + MAX_RETRIES);
  }
  
  initFailedLog(retries);
}

void EnvShieldSensors::initFailedLog(int retries){
  if (retries <= MAX_RETRIES){
      Serial.println("Unable to init Arduino Env Shield REV 2");
  }
}

bool EnvShieldSensors::begin() {
  return ENV.begin();
}

void EnvShieldSensors::readEnvData() {
  temperature = ENV.readTemperature(FAHRENHEIT);
  humidity = ENV.readHumidity();
  pressure = ENV.readPressure();
  illuminance = ENV.readIlluminance();
}

void EnvShieldSensors::printEnvData() {
  Serial.print("Temp: "); Serial.print(temperature); Serial.println(" °F");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
  Serial.print("Pressure: "); Serial.print(pressure); Serial.println(" kPa");
  Serial.print("Light: "); Serial.print(illuminance); Serial.println(" lx");
  Serial.println("----------------------------------------");
}
