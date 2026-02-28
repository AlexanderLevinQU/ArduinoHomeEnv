#include "EnvShieldSensors.h"
#include <Arduino_MKRENV.h>
#include <Arduino.h>

EnvShieldSensors::EnvShieldSensors() :
  temperature(0), humidity(0), pressure(0),
  illuminance(0) {}

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
