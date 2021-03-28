#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <DHT.h>
#define R_LED D0
#define G_LED D1
#define B_LED D2
#define DHTPIN D3
DHT dht(DHTPIN, DHT22);
#define DHTupdateinterval 10000
 
const unsigned long HTTP_TIMEOUT = 10000;
const char* ssid = "ASUSLAB";
const char* password = "ASUSASUS";

const char* host = "192.168.2.220";
const char* webpage= "Status_field.php";
const char* webpageupdate= "sensor_control/AddData.php?";
WiFiClient client;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  dht.begin();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED,OUTPUT);
  digitalWrite(R_LED, LOW);
  digitalWrite(G_LED, LOW);
  digitalWrite(B_LED, LOW);
  delay(500);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}

void loop()
{
  static uint32_t lasttime=millis();
  Serial.printf("\n[Connecting to %s ... ", host);
/**************************************/

/*************************************/  
  if (client.connect(host, 80))
  {
    Serial.println("[Host connected]");
    //Get Temperature & Humidity
    Serial.println("[Sending a request as:]");
    client.print(String("GET /")  + webpage + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );
    Serial.println(String("GET /")  + webpage + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n");  
    int timeoutcnt=0;
    while((!client.available()) && (timeoutcnt < 50)) 
    {
       delay(200);  //Use this with time out
       timeoutcnt++;
    }
        //https://circuits4you.com/2017/12/09/thing-speak-esp8266/  
        //---------------------------------------------------------------------
        //If data is available before time out read it.
    if(timeoutcnt < 50)
    {
       if (!client.find("\r\n\r\n")){
          Serial.println("invalid response");
          client.stop();       
          return;
       }  
       String section="LENGTH";
       client.setTimeout(5000);
       while(client.available())
       {
          String line = client.readStringUntil('\n');
          if( section == "LENGTH" )
          {
                // 這裡可以取回 JSON　字串的長度
                // String content_length = line.substring(1);
                /* 有需要處理的寫程式在這裡 */
                section = "JSON";
          }
          else if( section == "JSON" )    // print the good stuff
          {
                Serial.println( line );
                section = "END";
                String jsonStr = line.substring(0); // 給定一個從索引到尾的字串
                // 開始解析 JSON
                Serial.println("");
                 DynamicJsonDocument jsondoc(128);
                // Parse JSON object
                DeserializationError error = deserializeJson(jsondoc, jsonStr);
                if (error) {
                  Serial.print(F("deserializeJson() failed: "));
                  Serial.println(error.c_str());
                  client.stop();                  
                  return;
                }
                float Temp=jsondoc["Temperature"];
                float Humidity=jsondoc["Humidity"];
                Serial.print("Temperaure="); Serial.println(Temp);
                Serial.print("Humidity="); Serial.println(Humidity);                   
          }
        }
      client.stop();
      Serial.println("\n[Disconnected]");
    }
    else
    {
       Serial.println("Request timeout..");
       client.stop();           
       return;
    }                 
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(2000);
}



