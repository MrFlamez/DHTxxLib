#include "DHTxx.h"

int dht11_pin = 2;
int dht22_pin = 3;
int result = DHT_RESP_UNDEF;

DHT dht11 = DHT(dht11_pin, TYPE_DHT11);
DHT dht22 = DHT(dht22_pin, TYPE_DHT22);


void setup() {
  Serial.begin(9600);
  delay(1000); //time to initialize DHT sensor
}

void loop() {
  result = dht11.read();
  
  //check transfer result
  if (result == DHT_RESP_OK){
    Serial.println(dht11.humidity);
    Serial.println(dht11.temperature);
    Serial.println(" ");
  }
  else{
    Serial.println("error")
  }
  
  result = dht22.read();
  
  //check transfer result
  if (result == DHT_RESP_OK){
    Serial.println(dht22.humidity);
    Serial.println(dht22.temperature);
    Serial.println(" ");
  }
  else{
    Serial.println("error")
  }
  
  delay(10000);
}