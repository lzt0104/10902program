#include <Servo.h>
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <RTClib.h>
#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>

char auth[] = "NmLavOZIQfVG16U3xAmHSqhfS4l8T3Tc";   //Blynk 身分驗證令牌
char ssid[] = "ASUS98";                               //WiFi名稱
char pass[] = "hs2362620";                        //WiFi密碼
int pinValue ;

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3);
#define ESP8266_BAUD 9600
ESP8266 wifi(&EspSerial);
Servo myservo;                                      //建立一個 servo 物件，最多可建立 12個 servo

WidgetLED led3(V3);                                 //設定 led3 為腳位(V3)
BLYNK_WRITE(V3)                                     //Blynk虛擬腳位(V3)
{
myservo.write(param.asInt());
}
BLYNK_WRITE(V1)                                     //Blynk虛擬腳位(V1)
{
pinValue = param.asInt();                        //pinValue是 blynk 送來的命令
Serial.print("V1 Slider value is: ");
Serial.println(pinValue);
if (pinValue == 1)                                 //如果按鈕數據=1
{
myservo.write (0);                            //馬達運轉
led3.on();                                    //Blynk LED 開啟
delay (10000);                                //馬達運轉10000毫秒=10秒
myservo.write (90);                           //馬達停止
led3.off();                                   //Blynk LED 關閉
pinValue  = 0;                                //按鈕數據=0
}
}

BLYNK_WRITE(V2)                                     //Blynk虛擬腳位(V2)
{
pinValue = param.asInt();                        //pinValue是 blynk 送來的命令
Serial.print("V2 Slider value is: ");
Serial.println(pinValue);
if (pinValue == 1)                                 //如果按鈕數據=1
{
myservo.write (0);                            //馬達運轉
led3.on();                                    //Blynk LED 開啟
delay (5000);                                //馬達運轉5000毫秒=5秒
myservo.write (90);                           //馬達停止
led3.off();                                   //Blynk LED 關閉
pinValue  = 0;                                //按鈕數據=0
}
}
BLYNK_WRITE(V4)                                     //Blynk虛擬腳位(V4)
{
pinValue = param.asInt();                        //pinValue是 blynk 送來的命令
Serial.print("V4 Slider value is: ");
Serial.println(pinValue);
if (pinValue == 1 )                                 //如果按鈕數據=1
{
myservo.write (0);                            //馬達運轉
led3.on();                                    //Blynk LED 開啟
delay (3000);                                //馬達運轉3000毫秒=3秒
myservo.write (90);                           //馬達停止
led3.off();                                   //Blynk LED 關閉
pinValue  = 0;                                //按鈕數據=0
}

}
BLYNK_WRITE(V5)                                     //Blynk虛擬腳位(V5)
{
pinValue = param.asInt();                        //pinValue是 blynk 送來的命令
Serial.print("V5 Slider value is: ");
Serial.println(pinValue);
if (pinValue == 1)                                 //如果按鈕數據=1
{
myservo.write (0);                            //馬達運轉
led3.on();                                    //Blynk LED 開啟
delay (3500);                                //馬達運轉3500毫秒=3.5秒
myservo.write (90);                           //馬達停止
led3.off();                                   //Blynk LED 關閉
pinValue  = 0;                                //按鈕數據=0
}
}


void setup()
{
Serial.begin(9600);                               //設定通訊速率
delay(10);                                        //延遲10毫秒
EspSerial.begin(ESP8266_BAUD);                    //設置esp8266通訊速率
delay(10);                                        //延遲10毫秒
Blynk.begin(auth, wifi, ssid, pass);              //設置Blynk連線至wifi
myservo.attach(9);                                // 由9號數位接角輸出訊號給伺服馬達
myservo.write (90);                               //馬達停止
delay (200);                                      //延遲200毫秒
Serial.begin(9600);
setSyncProvider(RTC.get);
}
void loop()
{
int hs = hour();
int ms = minute();
int ss = second();
Blynk.run ();
Serial.print("Hour= ");
Serial.println(hs);
Serial.print("Minute= ");
Serial.println(ms);
Serial.print("Second= ");
Serial.println(ss);
delay(1000);
if ((hs == 6 && ms == 0 && ss == 0)  ||  (hs == 12 && ms == 0 && ss == 0)  ||  (hs == 18 && ms == 0 && ss == 0))  //自動控制時間執行feed函數
{
feed();
}
}

void feed()
{
myservo.write (0);                            //馬達運轉
led3.on();                                    //Blynk LED 開啟
delay (5000);                                //馬達運轉5000毫秒=5秒
myservo.write (90);                           //馬達停止
led3.off();                                   //Blynk LED 關閉
pinValue  = 0;
}
