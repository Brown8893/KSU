#include <WiFi.h>
#include <WiFiClient.h>
#include <TridentTD_LineNotify.h>

#include <Wire.h>
uint8_t readStatus = 0;

// 修改成上述寄到登入郵箱的 Token權杖號碼
#define LINE_TOKEN ""


// 設定無線基地台SSID跟密碼
const char* ssid     = "I4301_A";
const char* password = "cyrus123";

int soil_sensor = 34; //電壓檢測 AO信號腳 連接到ESP32 GPIO34
#define led_1 2

unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read sensor
 
void setup(void)
{
  Serial.begin(115200);  // 設定速率 感測器
  pinMode(led_1,OUTPUT);//定義板LED腳位為輸出模式
  pinMode(soil_sensor,INPUT);//定義土壤濕度感測器街口為輸入接口。

  WiFi.mode(WIFI_STA);
  // 連接無線基地台
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");
  // 等待連線，並從 Console顯示 IP
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("還沒連到喔");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop(void)
{
  // 量測
  float val= (analogRead(soil_sensor));//讀取值給va1
  String Msg="";
  String humid="";
  Serial.println(val);
  if(val < 24) {    //電壓小於24
    digitalWrite(led_1,LOW);//LED滅
    Msg="電壓過低";
    humid="目前電壓:"+String(val);
      //送出訊息
    LINE.setToken(LINE_TOKEN);
    LINE.notify("\n" + Msg + "\n"+humid);
  }else{ 
    digitalWrite(led_1,HIGH);//LED亮
    Msg=" ";
  }
  // 每10秒鐘發送一次
  delay(1000);
}