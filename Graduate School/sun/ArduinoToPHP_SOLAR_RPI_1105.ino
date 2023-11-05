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
float digitalValue, v1, v2, v3;
int vol1, amp1;
float vol2, amp2, vol3, power, sun1, sun2, sun3;
char state = 1;
SoftwareSerial esp8266(rxpin, txpin); // RX, TX


//*-- IoT Information
#define SSID "KSU_Brown"
#define PASS "steven8893"
#define IP "120.114.135.31"
String GET = "GET /Sensor/SOLAR/SolarEsp8266d.php?";


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
  delay(5000);
  sendDebug("AT");
  Loading("sent AT");
}

void loop(void)
{
  Serial.print("--------------------------------Start-------------------------------------\n");
  delay(1000);
  sendV();
  sendI();
  sendP();
  delay(1000);
  SentOnCloud( float(vol3), float(amp2), float(power) );

  lcd.home();   //LCD歸零，清除所有內容
  lcd.clear();  //LCD歸零，清除所有內容
  lcd.setCursor(0, 0); // (colum, row)
  lcd.print( float(vol3), 2);lcd.print("v ");lcd.print( float(amp2), 2);lcd.print("a ");
  lcd.setCursor(0, 1); // (colum, row)
  lcd.print( float(power), 3);lcd.print("w");

  //Serial.println(vol1);
  //Serial.println(vol2);
  Serial.print(vol3, 3); Serial.println(" v");
  Serial.print(amp2, 3); Serial.println(" a");
  Serial.print(power, 3); Serial.println(" w");
  //Serial.println(digitalValue, 3);
  //Serial.println((digitalValue * 5.00)/1024.0);
  //digitalValuedigitalValue
  //Serial.println(amp1);
  delay(60000);
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


/*******************太陽能板**************************/
void sendV()
{
  vol1 = analogRead(A0);
  vol2 = (float)vol1 * 5.00 / 1024.00;
  vol3 = (float)vol2 / 0.9011 * 10.0000;
  //vol3 = analogRead(A0);
}
void sendI()
{
  amp1 = analogRead(A1);
  amp2 = (float)amp1 * 5.00 / 1024.00;
}
void sendP()
{
  power = vol3 * amp2;
}

void SentOnCloud( float vol3, float amp2, float power)
{
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80"; //8080  
  sendDebug(cmd);
  if ( esp8266.find( "Error" ) )
  {
    Serial.print( "RECEIVED: Error\nExit1" );
    return;
  }
  cmd = GET + "&Voltage=" + String(vol3,3) + "&Current=" + String(amp2,3) + "&Power=" + String(power,3) + "\r\n";
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
