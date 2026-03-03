#ifndef ENV_SHIELD_SENSORS_H
#define ENV_SHIELD_SENSORS_H

class EnvShieldSensors {
public:
  float temperature;
  float humidity;
  float pressure;
  float illuminance;

  EnvShieldSensors();
  void init();
  bool begin();
  void readEnvData();
  void printEnvData();

private: 
  void initFailedLog(int retries);
};

#endif