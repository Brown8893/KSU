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


void setup()
{
  Serial.begin(baudrate);
  //esp8266.begin(baudrate);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  Serial.print("--------------------------------Start-------------------------------------\n");
  lcd.home();   //LCD歸零，清除所有內容
  lcd.clear();  //LCD歸零，清除所有內容
  //lcd.setCursor(0, 0);lcd.print("Wifi");
  //lcd.setCursor(0, 1);lcd.print("Connecting...");
  //sendDebug("AT+RST");
  delay(1000);
  //sendDebug("AT");
  //Loading("sent AT");
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
  //SentOnCloud( float(vol3), float(amp2), float(power), float(v1), float(sun1), float(v2), float(sun2), float(v3), float(sun3) );

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
