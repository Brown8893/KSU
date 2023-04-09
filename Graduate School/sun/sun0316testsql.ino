#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫
//#include <WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <LiquidCrystal.h>
#include <WiFiClient.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

int sensorPin = 0;   // select the input pin for the potentiometer
int digitalValue = 0;  // variable to store the value coming from the sensor
float analogVoltage = 0.00;
String vv, luxlux, postData, sun;

const char* ssid= "I4304";    // wifi name
const char* pass= "ksuie354";  // wifi password

//#define HOST "example.com"          // Enter HOST URL without "http:// "  and "/" at the end of URL

#define sensor A0

WiFiServer server(80);    //  WiFiServer is a class , creat a server object, here server to be active on PORT 80

void setup() {
   
  //Serial.begin(115200);   // Initialaztion Serial monitor  with 115200 bps
  

  Serial.begin(115200); 
  Serial.println("Communication Started \n\n");  
  delay(1000);
  Wire.begin();
  lcd.begin();

  WiFi.mode(WIFI_STA);           
  WiFi.begin(ssid, pass);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED) 
    { Serial.print(".");
      delay(500); }

  Serial.println();
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());    //print local IP address

  delay(30);

  WiFi.begin(ssid,pass);  // Wifi Initialization with SSID and PASSWORD
  Serial.print("Connecting to ");
  Serial.print(ssid);  // Print connecting to Wifi name
 // here is waiting to connect internet
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.println(".");
    delay(100);
  }
  Serial.println(" ");
  Serial.println("connected succesfully");
  server.begin();   //  begin the server
  Serial.print("Server begin at IP ");
  Serial.println(WiFi.localIP());  // print IP address of Node MCU
  

}

void loop() {

  HTTPClient http;    // http object of clas HTTPClient
  WiFiClient wclient; // wclient object of clas HTTPClient    

  //vv = char(digitalValue);  
  //luxlux = char(sun);  

  // if there is avaailable data from client then we have to read and store in String variable

  String request = wclient.readStringUntil('\n'); //  it will read untill \n 
  wclient.flush();  // flush out extra line from request
  Serial.println(request);

  int req = analogRead(sensor);

  String response ="HTTP/1.1 200 OK\r\n Content-type:text/html\r\n\r\n<!DOCTYPE HTML><HTML><BODY>LightIntensity is ";
  response+= req;
  response+= "</BODY></HTML>";
  wclient.print(response);
  delay(10); 

  digitalValue = analogRead(sensorPin);// read the value from the analog channel
  Serial.print("digital value = ");
  Serial.print(digitalValue);        //print digital value on serial monitor
  //convert digital value to analog voltage
  analogVoltage = (digitalValue * 5.00)/1024.00;
  Serial.print("  analog voltage = ");
  Serial.println(analogVoltage);

  float sun = 125000*(125*(((analogVoltage/200*1000)-4)/100));
  lcd.setCursor(2, 0); // (colum, row)從第一排的第三個位置開始顯示
  lcd.print(analogVoltage);lcd.print("v");
  lcd.setCursor(2, 1); // (colum,row)從第二排第三格位置開始顯示
  lcd.print(sun);lcd.print(" lux");
  delay(5000);
  // now here the server has to keep listening for clients 

  vv = String(digitalValue);
  luxlux = String(sun);

  postData = "vv=" + vv + "&luxlux=" + luxlux;
  http.begin(wclient, "http://localhost/sun0316/dbwrite.php");              // Connect to host where MySQL databse is hosted
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");            //Specify content-type header

  int httpCode = http.POST(postData);   // Send POST request to php file and store server response code in variable named httpCode
  //Serial.println("Values are, v = " + vv + " and lux = "+ luxlux );

  if (httpCode == 200) { Serial.println("Values uploaded successfully."); Serial.println(httpCode); 
    String webpage = http.getString();    // Get html webpage output and store it in a string
    Serial.println(webpage + "\n"); 
}

// if failed to connect then return and restart

else { 
  Serial.println(httpCode); 
  Serial.println("Failed to upload values. \n"); 
  http.end(); 
  return; }

}
