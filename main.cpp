#include <Arduino.h>
#include <Wifi.h>
#include <AsyncUDP.h>

  int pinX = 36;
  int pinY = 39;
  int button = 13;
  int potPin = 34;
  int potVal;
  int prevX;
  int prevY;
  int tolerance = 20;

  int port = 7000;

  const char * ssid = "ASUS_94";
  const char * password = "0416886767K";
  AsyncUDP udp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(button, INPUT_PULLUP); //læs lige PULLUP
  pinMode(potPin,INPUT);
  prevX = analogRead(pinX);
  prevY = analogRead(pinY); 
}

void direction(int horizontal, int vertical){
  if(horizontal == 0){
    udp.broadcastTo("moveleft", 7000);
    Serial.println("left");
  } else if(horizontal ==4095){
    udp.broadcastTo("moveright", 7000);
    Serial.println("Right");
  } else if(vertical == 0){
    udp.broadcastTo("moveup", 7000);
    Serial.println("Up");
  }else if(vertical == 4095){
    udp.broadcastTo("movedown", 7000);
    Serial.println("Down");
  } else{
    Serial.println("Still");
    udp.broadcastTo("stop", 7000);
  }
}

void speed(int Speed){
  if (Speed < 1000){
    udp.broadcastTo("speed 1", 7000);
  } else if (Speed >1000 || Speed < 2000){
    udp.broadcastTo("speed 4", 7000);
  }else if(Speed > 2000 || Speed < 3000){ 
    udp.broadcastTo("speed 7", 7000);
  }else if(Speed > 3000 || Speed <= 4095){ 
    udp.broadcastTo("speed 9", 7000);
  }
}

void loop() {
  /*if(abs(analogRead(pinX)-prevX) > tolerance || abs(analogRead(pinY)-prevY) > tolerance){
    Serial.println(map(analogRead(pinX), 0, 4095, -100, 100));
    Serial.println(map(analogRead(pinY), 0, 4095, -100, 100));
    prevX = analogRead(pinX);
  }*/

  direction(analogRead(pinX), analogRead(pinY));
  if(digitalRead(13) == LOW){
    udp.broadcastTo("init 9 9", 7000);
    Serial.println("Clicked");
  }
  speed(potVal = analogRead(potPin));
  
  Serial.println(potVal);

}