#include "ShellyPlug.h"

ShellyPlug::ShellyPlug(const char* ip, uint16_t port)
    : _ip(ip), _port(port) {}

bool ShellyPlug::sendCommand(const char* endpoint, String &responseOut) {
    if (!_client.connect(_ip, _port)) {
        return false;
    }

    // this is doing the get call. Print is actually "printing data to the server"
    _client.print("GET ");
    _client.print(endpoint);
    _client.print(" HTTP/1.1\r\n");
    _client.print("Host: ");
    _client.print(_ip);
    _client.print("\r\n");
    _client.print("Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (_client.connected() && millis() - timeout < 2000) {
        while (_client.available()) {
            responseOut += (char)_client.read();
        }
    }

    _client.stop();
    return true;
}

bool ShellyPlug::on() {
    String resp;
    return sendCommand("/rpc/Switch.Set?id=0&on=true", resp);
}

bool ShellyPlug::off() {
    String resp;
    return sendCommand("/rpc/Switch.Set?id=0&on=false", resp);
}

bool ShellyPlug::toggle() {
    bool current;
    if (!getState(current)) return false;
    return current ? off() : on();
}

bool ShellyPlug::getState(bool &stateOut) {
    String resp;
    if (!sendCommand("/rpc/Switch.GetStatus?id=0", resp)) return false;
    return parseState(resp, stateOut);
}

bool ShellyPlug::parseState(const String& json, bool &stateOut) {
    int idx = json.indexOf("\"state\":");
    if (idx == -1) return false;

    int start = json.indexOf("true", idx);
    if (start != -1) {
        stateOut = true;
        return true;
    }

    start = json.indexOf("false", idx);
    if (start != -1) {
        stateOut = false;
        return true;
    }

    return false;
}
