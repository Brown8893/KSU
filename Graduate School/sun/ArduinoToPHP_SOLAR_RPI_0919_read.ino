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
  delay(5000);
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
  lcd.print( float(vol3), 1);lcd.print("v ");lcd.print( float(amp2), 1);lcd.print("c ");lcd.print( float(power), 1);lcd.print("w");
  if ( v1 < 0.80 ){
    lcd.setCursor(0, 1); // (colum, row)
    lcd.print( float(v1), 3);lcd.print("v ");lcd.print("0");lcd.print("Lux");    
  }else{
    lcd.setCursor(0, 1); // (colum, row)
    lcd.print( float(v1), 3);lcd.print("v ");lcd.print( float(sun1), 1);lcd.print("Lux");
  }
  
  //Serial.println(vol1);
  //Serial.println(vol2); 
  //Serial.println(String(vol3,3));
  //Serial.println(vol1, 3);
  //Serial.println(amp2, 3);
  Serial.println(v1, 3);
  Serial.println(sun1, 3);
  Serial.println(v2, 3);
  Serial.println(sun2, 3);
  Serial.println(v3, 3);
  Serial.println(sun3, 3);
  //Serial.println(digitalValue, 3);
  //Serial.println((digitalValue * 5.00)/1024.0);
  //digitalValuedigitalValue
  //Serial.println(amp1);
  delay(5000);
}


/*******************輻射計**************************/

void sendV1()
{
  digitalValue = analogRead(A0);// read the value from the analog channel
  v1 = (digitalValue * 5.00)/1024.00;
}
void sendsun1()
{
  v1 = (digitalValue * 5.00)/1024.00;
  sun1 = 125000.00*(125.00*(((v1/200.00*1000.00)-4.00)/1000.00));
}
void sendV2()
{
  digitalValue = analogRead(A1);// read the value from the analog channel
  v2 = (digitalValue * 5.00)/1024.00;
}
void sendsun2()
{
  v2 = (digitalValue * 5.00)/1024.00;
  sun2 = 125000.00*(125.00*(((v2/200.00*1000.00)-4.00)/1000.00));
}
void sendV3()
{
  digitalValue = analogRead(A2);// read the value from the analog channel
  v3 = (digitalValue * 5.00)/1024.00;
}
void sendsun3()
{
  v3 = (digitalValue * 5.00)/1024.00;
  sun3 = 125000.00*(125.00*(((v2/200.00*1000.00)-4.00)/1000.00));
}
