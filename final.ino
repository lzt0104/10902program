#include <SoftwareSerial.h>
#include "DHT.h"
SoftwareSerial BT(0,1);
#define dhtPin 2      //讀取DHT11 Data
#define dhtType DHT11 //選用DHT11    
const int DOpin=2;
const int Relaypin=3;
const int PIROut=2;
const int ledPin=13;
const int Buzzpin=6;
const int Copin=7;
const int Gaspin=8;
const int Xpin = 1;
const int Ypin = 2;
int ERR;
int Xout;
int Yout;
int sensorValue=0;
int PIRresult=0;
int CoValue;
int GasValue;
int BT_receive;
int SensorValue;
float h;
float t;
  void setup() {
    pinMode(PIROut, INPUT);    
    pinMode(ledPin, OUTPUT);
    pinMode(Buzzpin,OUTPUT);
    pinMode(Copin,INPUT);
    pinMode(Gaspin,INPUT);
    pinMode(Relaypin,OUTPUT);
    pinMode(DOpin, INPUT);
    Serial.begin(9600);
    float h = readHumidity();   
    float t = readTemperature();
    BT.begin(9600);}
  void loop(){
    smart();
    temp();
    rober();
    oldman();
    co();
    window();  
  }

  void smart(){
    if(BT.available()){
       BT_receive=BT.read();
        if(BT_receive=='I'){
          digitalWrite(Relaypin,HIGH);}
        if(BT_receive=='O'){
          digitalWrite(Relaypin,LOW);}}
  }

  void temp(){
    if(ERR=(h,t)==0){
      BT.println("H");
      BT.println(h);
      delay(1000);
      BT.println("T");
      BT.println(t);
      delay(1000);}
  }

  void rober(){
    sensorValue = digitalRead(PIROut);
    if (sensorValue == 1) {    
      digitalWrite(ledPin, HIGH);
      PIRresult=256;
      }
    else {
      digitalWrite(ledPin, LOW);
      PIRresult=100;}
    Serial.println(PIRresult);
    delay(50);
    BT.println(PIRresult); 
  }

  void oldman(){
    Xout = analogRead(Xpin);
    Yout = analogRead(Ypin);
    BT.print("X");
    delay(1000);
    BT.print(Xout);
    delay(1000); 
    BT.print("Y");
    delay(1000);
    BT.print(Yout);
    delay(1000);
  }

  void door(){
    if(BT.available()){
       BT_receive=BT.read();
        if(BT_receive=='1'){
          digitalWrite(Relaypin,HIGH);
          delay(100);
          digitalWrite(Relaypin,LOW);}}
    delay(100);
  }

  void co(){
    CoValue=digitalRead(Copin);
    GasValue=digitalRead(Gaspin);
    if(CoValue==0||GasValue==0){
      tone(Buzzpin,262);
      delay(100);
      tone(Buzzpin,440);
      delay(100);}
    else{
      noTone(Buzzpin);}
  BT.println("C");
  BT.println(CoValue);
    delay(1000);
  BT.println("G");
  BT.println(GasValue);
    delay(1000);
  }


  void window(){
    SensorValue=digitalRead(DOpin);
    BT.println(SensorValue);
    delay(1000);
  }
