馬達運轉程式(藉由自動偵測溫溼度，來判別收繩還是放繩，利用迴圈不斷偵測)
const int In1 = 4;
const int In2 = 5;
const int In3 = 6;
const int In4 = 7;      
#include "DHT.h"
#define dhtPin 8      //讀取DHT11 Data
#define dhtType DHT11 //選用DHT11   

DHT dht(dhtPin, dhtType); // Initialize DHT sensor

void setup() {
  Serial.begin(9600);//設定鮑率9600
  dht.begin();//啟動DHT
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}

void loop() {
  float h = dht.readHumidity();//讀取濕度
  float t = dht.readTemperature();//讀取攝氏溫度
  float f = dht.readTemperature(true);//讀取華氏溫度
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("無法從DHT傳感器讀取！");
    return;
  }
  Serial.print("濕度: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("攝氏溫度: ");
  Serial.print(t);
  Serial.print("*C\t");
  Serial.print("華氏溫度: ");
  Serial.print(f);
  Serial.print("*F\n");
  delay(10000);//延時10秒
  if(h>60){   //這裡代表是判斷濕度大於60 開始收線
  mback();
  delay(5000); 
  mstop();
  }
  else if (h>10 && h<40){ //這裡代表判斷濕度>10 <40 則將線放出
  mfront();
  delay(1000);
  }
  else{   //如果都沒有則停止不動
    mstop();
  }
}
void mstop(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
void mfront(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
void mback(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}
溫溼度顯示程式(藉由DHT11偵測溫溼度，並顯示在面板上)
#include "DHT.h"
#define DHTPIN 8 
#define DHTTYPE DHT11
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// 設定 LCD I2C 位址
//LED_Fundino紅色PCF8574T板子用
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//LED_MH黑色PCF8574A1板子用
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
DHT dht(DHTPIN, DHTTYPE);
void loop()
{
  delay(10000);
  float h = dht.readHumidity();   //取得濕度
  float t = dht.readTemperature();  //取得溫度C

  //顯示在監控視窗裡
  Serial.print("濕度: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("溫度: ");
  Serial.print(t);
  Serial.println(" *C ");

  lcd.clear();
  lcd.setCursor(0, 0);  //設定游標位置 (字,行)
  lcd.print("RH  :");  //Relative Humidity 相對濕度簡寫
  lcd.setCursor(7, 0);  
  lcd.print(h);
  lcd.setCursor(14, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);  //設定游標位置 (字,行)
  lcd.print("Temp:");
  lcd.setCursor(7, 1);  
  lcd.print(t);
  lcd.setCursor(13, 1);
  lcd.print((char)223); //用特殊字元顯示符號的"度"
  lcd.setCursor(14, 1);
  lcd.print("C");

  mfront();
  delay(2000);
  mstop();
  delay(500);
  mback();
  delay(2000);
  mstop();
  delay(500);
  
} // loop()
