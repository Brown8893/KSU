#include <SoftwareSerial.h>
#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫
#include <LiquidCrystal.h>
#define baudrate   9600
#define rxpin      3
#define txpin      4

LiquidCrystal_I2C lcd(0x27, 16, 2); 

//#define sensorPin = A0;   // select the input pin for the potentiometer
int digitalValue = 0;  // variable to store the value coming from the sensor
double analogVoltage = 0.00;
double sun = 0.00;
SoftwareSerial esp8266(rxpin, txpin); // RX, TX

//*-- IoT Information
#define SSID "KSU_KSU"
#define PASS "ksu123456789"
#define IP "120.114.135.31"
String GET = "GET /Sensor/SOLAR/SolarEsp8266-2.php?";

void setup() {
  Serial.begin(baudrate);
  esp8266.begin(baudrate);
  Wire.begin();
  lcd.begin();
  Serial.print("--------------------------------Start-------------------------------------\n");
  lcd.home();   //LCD歸零，清除所有內容
  lcd.clear();  //LCD歸零，清除所有內容
  lcd.setCursor(0, 0);lcd.print("Wifi");
  lcd.setCursor(0, 1);lcd.print("Connecting...");
  lcd.clear();  // 清除舊訊息
  lcd.home();
  sendDebug("AT+RST");
  delay(5000);
  sendDebug("AT");
  Loading("sent AT");
}

void loop() {
  Serial.print("--------------------------------Start-------------------------------------\n");
  delay(1000);
  sendV();
  sendS();
  delay(1000);
  SentOnCloud( double(analogVoltage), double(sun) ); 
  lcd.home();   //LCD歸零，清除所有內容
  lcd.clear();  //LCD歸零，清除所有內容
  lcd.setCursor(2, 0); // (colum, row)從第一排的第三個位置開始顯示
  lcd.print(analogVoltage,5);lcd.print("v");
  lcd.setCursor(2, 1); // (colum,row)從第二排第三格位置開始顯示
  lcd.print(sun,3);lcd.print(" lux ");
  delay(3500);  
}

void sendDebug(String cmd)
{
  Serial.print("SEND: ");
  Serial.println(cmd);
  esp8266.println(cmd);
}

void Loading(String state)
{
  for (int timeout = 0 ; timeout <= 5 ; timeout++)
  {
    if (esp8266.find("OK"))
    {
      Serial.println("RECEIVED: OK\r\n");
      lcd.home();   //LCD歸零，清除所有內容
      lcd.clear();  //LCD歸零，清除所有內容
      lcd.setCursor(0, 0);lcd.print("Wifi Connection OK");
      //lcd.clear();  // 清除舊訊息
      //lcd.home();
      break;
    }
    else if (timeout == 5) {
      Serial.print( state );
      lcd.home();   //LCD歸零，清除所有內容
      lcd.clear();  //LCD歸零，清除所有內容
      lcd.setCursor(0, 0);lcd.print("Wifi Connection");
      lcd.setCursor(0, 1);lcd.print("Failed");
      //lcd.clear();  // 清除舊訊息
      //lcd.home();
      Serial.println(" fail...\nWifi Unable to connect");
      Serial.println("Please Please turn it back on Sequence");
      connectWiFi();
    }
    else
    {
      Serial.println("Wifi Loading...");
      lcd.home();   //LCD歸零，清除所有內容
      lcd.clear();  //LCD歸零，清除所有內容
      lcd.setCursor(0, 0);lcd.print("Wifi Loading...");
      //lcd.home();
      //lcd.clear();  // 清除舊訊息
      delay(1000);
    }
  }
}

void Wifi_connect()
{
  Serial.println("Esp8266 to Wifi");
  String cmd = "AT+CWJAP=\"";
  cmd += SSID;
  cmd += "\",\"";
  cmd += PASS;
  cmd += "\"";
  sendDebug(cmd);
  Loading("Wifi_connect");
}

boolean connectWiFi()
{
  esp8266.println("AT+CIPMUX=0");
  esp8266.println("AT+CWMODE=3");
  Wifi_connect();
}

/*v*/
void sendV()
{
  digitalValue = analogRead(A0);
  analogVoltage = (digitalValue * 5.00)/1024.00;
}

void sendS()
{
  sun = 125000.00*(125.00*(((analogVoltage/200.00*1000.00)-4.00)/1000.00));
}

void SentOnCloud( double analogVoltage, double sun )
{
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",8080"; //8080  
  sendDebug(cmd);
  if ( esp8266.find( "Error" ) )
  {
    Serial.print( "RECEIVED: Error\nExit1" );
    return;
  }
  /*
  if ( sun < 0 )
  {
    cmd = GET + "&Voltage=" + (float)analogVoltage + "&Lux=" + "0" + "\r\n";
  }
  else
  {
    cmd = GET + "&Voltage=" + (float)analogVoltage + "&Lux=" + (float)sun + "\r\n";
  }
  */
  cmd = GET + "&Voltage=" + (double)analogVoltage + "&Lux=" + (double)sun + "\r\n";
  esp8266.print( "AT+CIPSEND=" );
  esp8266.println( cmd.length() );

  if (esp8266.find( ">" ) )
  {
    Serial.print(">");
    Serial.print(cmd);
    esp8266.print(cmd);
  }
  else
  {
    esp8266.print( "AT+CIPCLOSE" );
  }
  if ( esp8266.find("OK") )
  {
    Serial.println( "RECEIVED: OK" );
  }
  else
  {
    Serial.println( "RECEIVED: Error\nExit2" );
    connectWiFi();
  }
}
