#ifndef SHELLY_PLUG_H
#define SHELLY_PLUG_H

#include <WiFiNINA.h>

class ShellyPlug {
public:
    ShellyPlug(const char* ip, uint16_t port = 80);

    bool on();
    bool off();
    bool toggle();
    bool getState(bool &stateOut);

private:
    const char* _ip;
    uint16_t _port;
    WiFiClient _client;

    bool sendCommand(const char* endpoint, String &responseOut);
    bool parseState(const String& json, bool &stateOut);
};

#endif