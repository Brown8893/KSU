#define LED_BUILTIN 2 
#include <WiFi.h>
#include <HTTPClient.h>
const char ssid[]="KSU_Brown"; //修改為你家的WiFi網路名稱
const char pwd[]="steven8893"; //修改為你家的WiFi密碼
#define RXD2 16
#define TXD2 17
int sensorValue;

String url = "http://120.114.135.31:80/Sensor/SOLAR/SolarEsp8266c.php?";
String url2 = "";
//將資料上傳ThinkSpeak
void UploadData(){ 
  //建立一個網頁
  HTTPClient http;  

  //提交網址
  http.begin(url2);
  //讀取網頁內容
  int httpCode = http.GET();
  if(httpCode == HTTP_CODE_OK){
    String payload = http.getString();
    Serial.print("網頁內容=");
    Serial.println(payload);
  } 
  else{
     Serial.println("網路傳送失敗");
  }
  //關閉網頁
  http.end(); 
}


void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // set the digital pin as output:
  pinMode(A0,INPUT);
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  WiFi.mode(WIFI_STA); //設置WiFi模式
  WiFi.begin(ssid,pwd); 
  Serial.print("WiFi connecting");
  //當WiFi連線時會回傳WL_CONNECTED，因此跳出迴圈時代表已成功連線
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);   
  }
  Serial.println("");
  Serial.print("IP位址:");
  Serial.println(WiFi.localIP()); //讀取IP位址
  Serial.print("WiFi RSSI:");
  Serial.println(WiFi.RSSI()); //讀取WiFi強度
}

void loop() {
  //url = "http://192.168.0.101:80/Sensor/SOLAR/SolarEsp8266c.php?";
  if (Serial2.available()) { // if there is data comming
    String command = Serial2.readStringUntil('\n'); // read string until newline character
    command.replace(" ","");
    //command = "Vo1=55&Lux1=55&Vo2=55&Lux2=55&Vo3=55&Lux3=505";

    url2 = url + command;
    url2.replace(" ","");
    Serial.println(command);
    Serial.println(url2);
    UploadData();
    delay(500);
  }
  /*
  url = "http://192.168.0.101:80/Sensor/SOLAR/SolarEsp8266c.php?Vo1=55&Lux1=55&Vo2=55&Lux2=55&Vo3=55&Lux3=505";
  UploadData();
  delay(1000);
  */
  /*Serial3.print("Vo1=55&Lux1=55&Vo2=55&Lux2=55&Vo3=55&Lux3=55");*/
  
  /*String command = "Vo1=55&Lux1=55&Vo2=55&Lux2=55&Vo3=55&Lux3=55";
  url = url + command;
  //ReadSensor();
  UploadData();
  delay(1000);
  */
  
}