/////////////////////
/*
GY39----MINI
VCC----VCC
GND----GND
1:RX---TX,send A5 02 A7 to GY-39
2:TX---RX
3:MINI_TX---FT232_RX
*/
//////////////////
#include <Wire.h>               // I2C程式庫
#include <LiquidCrystal_I2C.h>  // LCD_I2C模組程式庫
#include <LiquidCrystal.h>
#include <BME280I2C.h>
#include <SoftwareSerial.h>
#include "Wire.h"
#include "Max44009.h"
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

Max44009 myLux(0x4A);
BME280I2C bme;

uint8_t readStatus = 0;

unsigned char Re_buf[15], counter = 0;
unsigned char sign = 0;
float digitalValue1, digitalValue2, digitalValue3;
double v1 = 0.00;
double v2 = 0.00;
double v3 = 0.00;
double sun1, sun2, sun3;
float gy_temp, gy_humd, gy_lux;
char state = 1;
double  gy_39_temp, gy_39_hum, gy_39_pressure, gy_39_lux, h;

String GET1 ="";

unsigned long previousMillis = 0;  // will store last temp was read
const long interval = 2000;        // interval at which to read sensor
uint32_t lastDisplay = 0;

void setup() {

  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  dht.begin();  //初始化DHT
  //Serial.print("--------------------------------Start-------------------------------------\n");
  //delay(1000);
  //Serial.write(0XA5);
  //Serial.write(0X03);  //初始化,连续输出模式
  //Serial.write(0XA8);  //初始化,连续输出模式
  //delay(10);
  //Re_buf[3] = 0;
  lcd.init();
  lcd.backlight();
  lcd.home();   //LCD歸零，清除所有內容
  lcd.clear();  //LCD歸零，清除所有內容

  while (!Serial) {} // Wait
  Wire.begin();
  while (!bme.begin())
  {
    //Serial.println("Could not find BME280 sensor!");
    delay(3000);
  }

  switch (bme.chipModel())
  {
    case BME280::ChipModel_BME280:
      //Serial.println("Found BME280 sensor! Success.");
      break;
    case BME280::ChipModel_BMP280:
      //Serial.println("Found BMP280 sensor! No Humidity available.");
      break;
    default:
      Serial.println("Found UNKNOWN sensor! Error!");
  }
  /*light*/
  //Serial.print("\nStart max44009_interrupt : ");
  //Serial.println(MAX44009_LIB_VERSION);

  Wire.begin();
  myLux.setContinuousMode();

  myLux.setHighThreshold(30);
  //Serial.print("HighThreshold:\t");
  //Serial.println(myLux.getHighThreshold());

  myLux.setLowThreshold(10);
  //Serial.print("LowThreshold:\t");
  //Serial.println(myLux.getLowThreshold());

  myLux.setThresholdTimer(2);

  myLux.enableInterrupt();
}

void loop() {

  digitalValue1 = analogRead(A0);// read the value from the analog channel
  v1 = (digitalValue1 * 5.00)/1024.00;
  sun1 = 125000.00*(125.00*(((v1/200.00*1000.00)-4.00)/1000.00));
  digitalValue2 = analogRead(A1);// read the value from the analog channel
  v2 = (digitalValue2 * 5.00)/1024.00;
  sun2 = 125000.00*(125.00*(((v2/200.00*1000.00)-4.00)/1000.00));
  digitalValue3 = analogRead(A2);// read the value from the analog channel
  v3 = (digitalValue3 * 5.00)/1024.00;
  sun3 = 125000.00*(125.00*(((v3/200.00*1000.00)-4.00)/1000.00));

  lcd.setCursor(0, 0); // (colum, row)
  lcd.print(v1,4); lcd.print(" "); lcd.print(v2,4);
  lcd.setCursor(0, 1); // (colum, row)
  lcd.print(v3,4);
  
  GY39toMysql();
  
  //Serial.print("--------------------------------end-------------------------------------\n");
}

/*-----Step2： upload BMP280 Database Sensor wirte work-----*/
void GY39toMysql()
{
  /*step.1 執行讀取BME280與lux*/
  float temp(NAN), hum(NAN), pres(NAN);

  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);

  bme.read(pres, temp, hum, tempUnit, presUnit);
  //Serial.print("Temp：");
  //Serial.print(temp);
  //Serial.println("°" + String(tempUnit == BME280::TempUnit_Celsius ? 'C' : 'F'));
  //delay(1000);
  h = dht.readHumidity();   //取得濕度
  //Serial.print("Humidity：");
  //Serial.print(h);
  //Serial.println("% RH");
  //delay(1000);
  //Serial.print("Pressure：");
  //Serial.print(pres);
  //Serial.println(" Pa");
  //delay(1000);
  //lcd.setCursor(0, 0); // (colum, row)
  //lcd.print("T="); lcd.print(temp);
  //lcd.print(" H="); lcd.print(h); 
   

  uint32_t interval = 1000;
  if (millis() - lastDisplay >= interval)
  {
    lastDisplay += interval;
    float lux = myLux.getLux();
    int err = myLux.getError();
    int st = myLux.getInterruptStatus();
    if (err != 0)
    {
      Serial.print("Error:\t");
      Serial.println(err);
    }
    else
    {
      //Serial.print("lux:\t");
      //Serial.print(lux);
      //lcd.setCursor(0, 1); // (colum, row)
      //lcd.print("B="); lcd.print(lux);
      //if (st == 1) Serial.print("");
      //else Serial.print("");
    }
  }

  Serial3.println("Vo1="+String(v1,4)+"&Lux1="+String(sun1,4)+"&Vo2="+String(v2,4)+"&Lux2="+String(sun2,4)+"&Vo3="+String(v3,4)+"&Lux3="+String(sun3,4)+"&gy_temp="+String(gy_39_temp,4)+"&gy_humd="+String(h,4)+"&gy_lux="+String(gy_39_lux,4)+" \n");
  Serial2.println("Vo1="+String(v1,4)+"&Lux1="+String(sun1,4)+"&Vo2="+String(v2,4)+"&Lux2="+String(sun2,4)+"&Vo3="+String(v3,4)+"&Lux3="+String(sun3,4)+"&gy_temp="+String(gy_39_temp,4)+"&gy_humd="+String(h,4)+"&gy_lux="+String(gy_39_lux,4)+" \n");
  Serial.println("Vo1="+String(v1,4)+"&Lux1="+String(sun1,4)+"&Vo2="+String(v2,4)+"&Lux2="+String(sun2,4)+"&Vo3="+String(v3,4)+"&Lux3="+String(sun3,4)+"&gy_temp="+String(gy_39_temp,4)+"&gy_humd="+String(h,4)+"&gy_lux="+String(gy_39_lux,4)+" \n");
    //Serial2.println("Vo1="+String(v1,3)+"&Lux1="+String(sun1,3)+"&Vo2="+String(v2,3)+"&Lux2="+String(sun2,3)+"&Vo3="+String(v3,3)+"&Lux3="+String(sun3,3)+"&gy_temp="+String(gy_temp,3)+"&gy_humd="+String(gy_humd,3)+"&gy_lux="+String(gy_lux,3)+" \n");
    //delay(3000); 
  
  delay(1000);

  /*step.2 執行讀取BME280暫存到變數*/
  gy_39_temp = temp;
  //Serial.println(gy_39_temp);
  gy_39_hum = hum;
  //Serial.println(gy_39_hum);
  gy_39_pressure = pres;
  //Serial.println(gy_39_pressure);

  gy_39_lux = myLux.getLux();
  //Serial.println(gy_39_lux);

  if ( Serial3.find( "Error" ) )
  {
    //Serial.print( "RECEIVED: Error\nExit1" );
    return;
  }

  
}

void serialEvent() {
      while (Serial.available()) {   
      Re_buf[counter]=(unsigned char)Serial.read();
      if(counter==0&&Re_buf[0]!=0x5A) return;      // 检查帧头         
      counter++;       
      if(counter==(Re_buf[3]+5))                //接收到数据
      {
        //Serial.print("No: ");
        //Serial.println( Re_buf[3],DEC);    
         counter=0;                 //重新赋值，准备下一帧数据的接收 
         sign=1;
      }      
      }
}