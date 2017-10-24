/*
###############################################################################
# File: DHTxx.h
# Version: 1.0.0
# Autor: MrFlamez
# History:
#  2017-10-24 | created
###############################################################################
*/
#ifndef DHTxx_H
#define DHTxx_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#endif

//sensor types
#define TYPE_DHT11 11
#define TYPE_DHT22 22

//response types
#define DHT_RESP_OK               0
#define DHT_RESP_ERR_ACKNOWLEDGE  1
#define DHT_RESP_ERR_CHECKSUM     2
#define DHT_RESP_ERR_CONVERSION   3
#define DHT_RESP_UNDEF            255

class DHT{

  public:
    double humidity; //%RH
    double temperature; //°C
    DHT(int pin, int type);
    int read();
  
  private:
    int _sensorPin;
    int _sensorType;

};

#endif //DHTxx_H
