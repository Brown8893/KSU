#include <SoftwareSerial.h>
#define baudrate   9600
#define rxpin      3
#define txpin      4

//#define sensorPin = A0;   // select the input pin for the potentiometer
int digitalValue = 0;  // variable to store the value coming from the sensor
float analogVoltage = 0.00;
float sun;
SoftwareSerial esp8266(rxpin, txpin); // RX, TX

//*-- IoT Information
#define SSID "KSU_KSU"
#define PASS "ksu123456789"
#define IP "120.114.135.31"
String GET = "GET /Sensor/SOLAR/SolarEsp8266-2.php?";

void setup() {
  Serial.begin(baudrate);
  esp8266.begin(baudrate);
  Serial.print("--------------------------------Start-------------------------------------\n");
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
  SentOnCloud( float(analogVoltage), float(sun));
  delay(28000);
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
      break;
    }
    else if (timeout == 5) {
      Serial.print( state );
      Serial.println(" fail...\nWifi Unable to connect");
      Serial.println("Please Please turn it back on Sequence");
      connectWiFi();
    }
    else
    {
      Serial.println("Wifi Loading...");
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
  sun = (float)125000*(125*(((analogVoltage/200*1000)-4)/100));
}

void SentOnCloud( float analogVoltage, float sun )
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
  cmd = GET + "&Voltage=" + (float)analogVoltage + "&Lux=" + (float)sun + "\r\n";
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
