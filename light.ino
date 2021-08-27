// Arduino 程式的架構大體可分為三個部分：(宋楠、韓廣義2015)
// -----------------------------------------------------------------------------------------------------
// ※ 宣告常數、變數及介面的名稱、引用函式庫宣告檔Head。
// -----------------------------------------------------------------------------------------------------
#include "FastLED.h"    // 引用FastLED.h函式庫
                      // GitHub - FastLED/FastLED: 
                      // The main FastLED library (successor to ...
                      // https://github.com/FastLED/FastLED
//宣告常數
#define NUM_LEDS 6   // 燈帶上燈的數量
#define DATA_PIN 9    // 燈帶用的數位針腳 Pin

//宣告陣列變數
CRGB leds[NUM_LEDS];   // 燈帶 6 個 LED 陣列＝>可設定各 LED 顏色

// -----------------------------------------------------------------------------------------------------
// ※ (2) setup()。在Arduino程式執行時首先要呼叫 setup() 函式，它用於初始化變數、設置腳位的輸出／輸入類型、配置序列埠、匯入函式庫檔案等等。每次 Arduino 通電或重新啟動後，setup()函式只會執行一次。
// the setup routine runs once when you press reset:
// -----------------------------------------------------------------------------------------------------
void setup() {

  // initialize serial communication at 9600 bits per second:
  // 設置序列埠每秒傳輸資料的速率。
  // 在與電腦進行通訊時，可以使用下面這些值：
  // 300、1200、2400、 4800、9600、14400、19200、28800、38400、57600、115200。一般來說 9600、57600 和 115200 比較常見。
Serial.begin(9600);

  delay(1000);    // 延遲一段時間，以毫秒為單位，如1000為1秒。

  // 初始化燈帶:WS2812 : LED 控制IC型號， DATA_PIN:控制數位針腳，RGB:顏色控制
  // 第一個參數為傳輸陣列變數(位址)，第二個參數為LED數量
FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);

}

// -----------------------------------------------------------------------------------------------------
// ※ (3) loop()。在 setup()函式中初始化和定義變數之後就會接續執行 loop()函式。顧名思義，該函式在程式執行過程中會不斷重複，並根據回饋來對應地改變執行情況。藉由該函式就能動態控制 Arduino 主控板。
// the loop routine runs over and over again forever:
// -----------------------------------------------------------------------------------------------------
void loop() {
  // read the input on analog pin 0:
  // 從指定的類比介面針腳讀取數值，Arduino 會對該類比值進行數值轉換，
  // 這個方法將輸入的 0-5V 電壓值轉換為 0 - 1023 間的整數值，
  // 並將該整數值作為回傳值。
int iA5 = analogRead(A5);           // A5 接點為光敏電阻
int iA4 = analogRead(A4);           // A4 接點為 HC-SR04 超音波感測器
int iA3 = analogRead(A3);           // A3 接點為 LM35 溫度感測器

  // print out the value you read:
Serial.println(iA5);  // A5接點為光敏電阻偵測到的數值→從序列埠輸出資料
Serial.println(iA4);  // A4接點為HC-SR04超音波感測器偵測到的數值→從序列埠輸出資料
Serial.println(iA3);  // A3接點為LM35溫度感測器到的數值→從序列埠輸出資料
Serial.println();

delay(1000);        // delay in between reads for stability
// 延遲一段時間，以毫秒為單位，如 1 為 1 毫秒。

if  ( (iA5 < 530) ||  (iA4 < 50) ||  (iA3 < 52) ) {  
      // A5接點為光敏電阻，A4接點為HC-SR04超音波感測器，A3接點為 LM35溫度感測器
      // 觸發隨便一個以上設備都會點亮 LED ，||是或(OR)，&&是且(AND)

leds[0] = CRGB::Red;         // 第 1 顆 LED 設定顏色為紅色
leds[1] = CRGB(255,0,0);      // 第 2 顆 LED 設定顏色為紅色

leds[2] = CRGB::Green;       // 第 3 顆 LED 設定顏色為綠色
leds[3] = CRGB(0,255,0);      // 第 4 顆 LED 設定顏色為綠色

leds[4] = CRGB::Blue;        // 第 5 顆 LED 設定顏色為藍色
leds[5] = CRGB(0,0,255);      // 第 6 顆 LED 設定顏色為藍色

FastLED.show();             // LED 點亮

      delay(500);  //延遲一段時間，以毫秒為單位，如500為0.5秒。
  } 
else {
for(intwhiteLed = 0; whiteLed< NUM_LEDS; whiteLed = whiteLed + 1) {
      //燈帶關閉狀態
      // 6顆 LED 陸續設定顏色為黑色
      // leds[whiteLed] = CRGB::Black;
      // 6顆 LED 陸續設定顏色為黑色
      // leds[whiteLed] = CRGB(0,0,0);

      // 6顆 LED 陸續設定顏色為紅色
      // leds[whiteLed] = CRGB(255,0,0);
      // 6顆 LED 陸續設定顏色為白光
      // leds[whiteLed] = CRGB::White;
      // leds[whiteLed] = CRGB(255, 255, 255);

      // 6顆 LED 陸續設定顏色為黃光
      // leds[whiteLed] = CRGB::Yellow;
		   leds[whiteLed] = CRGB(255, 255, 0); 

FastLED.show();  // LED 點亮
    }  

    delay(250);   //延遲一段時間，以毫秒為單位，如250為0.25毫秒。
  }
}
