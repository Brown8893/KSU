#include <SoftwareSerial.h>
#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫
#include <LiquidCrystal.h>
#define baudrate   9600
#define rxpin      7
#define txpin      8

uint8_t readStatus = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); 

unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read sensor

// v1-
float digitalValue1, digitalValue2, digitalValue3, v1, v2, v3;
float sun1, sun2, sun3;
char state = 1;
SoftwareSerial esp8266(rxpin, txpin); // RX, TX

//*-- IoT Information
#define SSID "I4304"
#define PASS "ksuie354"
#define IP "172.20.168.81"
String GET = "GET /Sensor/SOLAR/SolarEsp8266_3.php?";


void setup()
{
  Serial.begin(baudrate);
  esp8266.begin(baudrate);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  Serial.print("--------------------------------Start-------------------------------------\n");
  lcd.home();   //LCD歸零，清除所有內容
  lcd.clear();  //LCD歸零，清除所有內容
  lcd.setCursor(0, 0);lcd.print("Wifi");
  lcd.setCursor(0, 1);lcd.print("Connecting...");
  sendDebug("AT+RST");
  delay(1000);
  sendDebug("AT");
  Loading("sent AT");
}

void loop(void)
{
  Serial.print("--------------------------------Start-------------------------------------\n");
  delay(1000);
  sendV1();
  sendsun1();
  sendV2();
  sendsun2();
  sendV3();
  sendsun3();
  delay(1000);
  SentOnCloud( float(v1), float(sun1), float(v2), float(sun2), float(v3), float(sun3) );

  lcd.home();   //LCD歸零，清除所有內容
  lcd.clear();  //LCD歸零，清除所有內容
  lcd.setCursor(0, 0); // (colum, row)
  lcd.print( float(v1), 3);lcd.print("v ");lcd.print( float(v2), 3);lcd.print("v");
  lcd.setCursor(0, 1); // (colum, row)
  lcd.print( float(v3), 3);lcd.print("v");

  //if ( v1 < 0.80 ){
    //lcd.setCursor(0, 1); // (colum, row)
    //lcd.print( float(v1), 3);lcd.print("v ");lcd.print("0");lcd.print("Lux");    
  //}else{
    //lcd.setCursor(0, 1); // (colum, row)
    //lcd.print( float(v1), 3);lcd.print("v ");lcd.print( float(sun1), 1);lcd.print("Lux");
  //}
  Serial.print("v1 : ");  Serial.println(v1, 3);
  Serial.print("sun1 : ");  Serial.println(sun1, 3);
  Serial.print("v2 : ");  Serial.println(v2, 3);
  Serial.print("sun2 : ");  Serial.println(sun2, 3);
  Serial.print("v3 : ");  Serial.println(v3, 3);
  Serial.print("sun3 : ");  Serial.println(sun3, 3);
  //Serial.println(digitalValue, 3);
  //Serial.println((digitalValue * 5.00)/1024.0);
  //digitalValuedigitalValue
  //Serial.println(amp1);
  delay(1000);
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
      break;
    }
    else if (timeout == 5) {
      Serial.print( state );
      lcd.home();   //LCD歸零，清除所有內容
      lcd.clear();  //LCD歸零，清除所有內容
      lcd.setCursor(0, 0);lcd.print("Wifi Connection");
      lcd.setCursor(0, 1);lcd.print("Failed");
      Serial.println(" fail...\nWifi Unable to connect");
      Serial.println("Please Please turn it back on Sequence");
      connectWiFi();
    }
    else
    {
      Serial.print("Wifi Loading...");
      lcd.home();   //LCD歸零，清除所有內容
      lcd.clear();  //LCD歸零，清除所有內容
      lcd.setCursor(0, 0);lcd.print("Wifi Loading...");
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

/*******************輻射計**************************/

void sendV1()
{
  digitalValue1 = analogRead(A8);// read the value from the analog channel
  v1 = (digitalValue1 * 5.00)/1024.00;
}
void sendsun1()
{
  v1 = (digitalValue1 * 5.00)/1024.00;
  sun1 = 125000.00*(125.00*(((v1/200.00*1000.00)-4.00)/1000.00));
}
void sendV2()
{
  digitalValue2 = analogRead(A9);// read the value from the analog channel
  v2 = (digitalValue2 * 5.00)/1024.00;
}
void sendsun2()
{
  v2 = (digitalValue2 * 5.00)/1024.00;
  sun2 = 125000.00*(125.00*(((v2/200.00*1000.00)-4.00)/1000.00));
}
void sendV3()
{
  digitalValue3 = analogRead(A10);  // read the value from the analog channel
  v3 = (digitalValue3 * 5.00)/1024.00;
}
void sendsun3()
{
  v3 = (digitalValue3 * 5.00)/1024.00;
  sun3 = 125000.00*(125.00*(((v2/200.00*1000.00)-4.00)/1000.00));
}

void SentOnCloud( float v1, float sun1, float v2, float sun2, float v3, float sun3 )
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
  cmd = GET + "&Vo1=" + String(v1,3) + "&Lux1=" + String(sun1,3) + "&Vo2=" + String(v2,3) + "&Lux2=" + String(sun2,3) + "&Vo3=" + String(v3,3) + "&Lux3=" + String(sun3,3) + "\r\n";
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