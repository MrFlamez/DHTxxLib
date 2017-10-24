/*
###############################################################################
# File: DHTxx.cpp
# Version: 1.0.0
# Autor: MrFlamez
# History:
#  2017-10-24 | created
###############################################################################
*/

#include "DHTxx.h"

DHT::DHT(int pin, int type){
  this->_sensorPin = pin;
  this->_sensorType = type;
  this->humidity = 0;
  this->temperature = 0;
}

int DHT::read(){

  /*
  This method reads Data from DHT sensor and returns the state
  wether it was successful or not.
  */
  
  uint8_t sign, sum;
  uint8_t result = DHT_RESP_UNDEF;
  byte data[5];

  for (int i = 0; i < 5;i++){
    data[i] = 0;
  }
  
  //initialize transfer
  pinMode(this->_sensorPin, OUTPUT);
  digitalWrite(this->_sensorPin, LOW);
  delay(18);
  digitalWrite(this->_sensorPin, HIGH);
  delayMicroseconds(30);
  pinMode(this->_sensorPin, INPUT);
  
  //check acknowledge signal
  if (pulseIn(this->_sensorPin, HIGH) > 70){
  
  //data transfer
    for(int bytecnt = 0; bytecnt < 5; bytecnt++){
      for(int bitcnt = 7; bitcnt >= 0; bitcnt--){
        if (pulseIn(this->_sensorPin, HIGH) > 40){
          data[bytecnt] |= (B1 << bitcnt);
        }
      }
    }
  }
  else{
    result = DHT_RESP_ERR_ACKNOWLEDGE;
  }
  
  //if there is no error, verify checksum
  if (result == DHT_RESP_UNDEF){
    sum = data[0] + data[1] + data[2] + data[3];
    if (data[4] != sum){
	  result = DHT_RESP_ERR_CHECKSUM;
	}
  }
  
  //if there is no error, convert data in °C and %RH
  if (result == DHT_RESP_UNDEF){
    switch(this->_sensorType){
	  case TYPE_DHT11:
	  
        this->humidity = (double)data[0];
		this->temperature = (double)data[2];
		break;
		
	  case TYPE_DHT22:
		//negative temperature
		sign = 1;
		if (data[2] & 0x80){
		  data[2] = (data[2] & 0x7F);
		  sign = -1;
		}
		
		this->temperature = (double)sign * word(data[2], data[3])*0.1;
	    this->humidity = (double)word(data[0], data[1])*0.1;
		break;

	  default:
	    result = DHT_RESP_ERR_CONVERSION;
		break;
		
    }
  }
  
  //if there is no error after all, return ok
  if (result == DHT_RESP_UNDEF){
    result = DHT_RESP_OK;
  }
  return result;
}
