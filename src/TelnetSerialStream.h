/* Copyright 2008, 2012-2022 Dirk-Willem van Gulik <dirkx(at)webweaving(dot)org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * Library that provides a fanout, or T-flow; so that output or logs do 
 * not just got to the serial port; but also to a configurable mix of a
 * telnetserver, a webserver, syslog or MQTT.
 */

#ifndef _H_TELNET_LOGTEE
#define _H_TELNET_LOGTEE
#if (defined(ESP32) || defined(ESP8266))

#include <TLog.h>

#ifndef MAX_SERIAL_TELNET_CLIENTS
#define MAX_SERIAL_TELNET_CLIENTS (4)
#endif

class TelnetSerialStream : public LOGBase {
  public:
    TelnetSerialStream(String hostname, const uint16_t telnetPort = 23, const uint16_t maxClients = MAX_SERIAL_TELNET_CLIENTS, bool withMDNS = true) : _hostname(hostname), _telnetPort(telnetPort), _maxClients(maxClients), _withMDNS(withMDNS) {};
    TelnetSerialStream(const uint16_t telnetPort = 23, const uint16_t maxClients = MAX_SERIAL_TELNET_CLIENTS, bool withMDNS = true) : _telnetPort(telnetPort), _maxClients(maxClients), _withMDNS(withMDNS) {};
    ~TelnetSerialStream();
    virtual size_t write(uint8_t c);
    virtual size_t write(uint8_t * buff, size_t len);
    virtual void begin();
    virtual void loop();
    virtual void stop();

  private:
    String _hostname = "";
    uint16_t _telnetPort, _maxClients;
    WiFiServer * _server = NULL;
    WiFiClient ** _serverClients;
    bool _withMDNS;
  protected:
};
#endif
#endif

