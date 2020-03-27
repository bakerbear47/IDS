#include <Arduino.h>
#include "WiFi.h" 
#include "AsyncUDP.h"

const int Button = 23;
const char * ssid = "HUAWEI P20 lite";
const char * password = "hallohallo";
AsyncUDP udp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
pinMode(Button,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
if (digitalRead(Button)==LOW){
  udp.broadcastTo("init 9 9", 7000);
  Serial.println("PUSHED");
}else{
  Serial.println("Not Pushed");
}

}