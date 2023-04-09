#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫
#include <WiFi.h>
//#include <MySQL_Connection.h>
//#include <MySQL_Cursor.h>
#include <LiquidCrystal.h>
//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>

// LCD I2C位址，默認為0x27或0x3F，依據背板的晶片不同而有差異，16、2為LCD顯示器大小。
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int sensorPin = A0;   // select the input pin for the potentiometer
int digitalValue = 0;  // variable to store the value coming from the sensor
float analogVoltage = 0.00;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  lcd.begin();
  //lcd.backlight();
}

void loop() {
  digitalValue = analogRead(sensorPin);// read the value from the analog channel
  Serial.print("digital value = ");
  Serial.print(digitalValue);        //print digital value on serial monitor
  //convert digital value to analog voltage
  analogVoltage = (digitalValue * 5.00)/1024.00;
  Serial.print("  analog voltage = ");
  Serial.println(analogVoltage);

  float sun = 125000.00*(125.00*(((analogVoltage/200.00*1000.00)-4.00)/100.00));
  lcd.setCursor(2, 0); // (colum, row)從第一排的第三個位置開始顯示
  lcd.print(analogVoltage);lcd.print("v");
  lcd.setCursor(2, 1); // (colum,row)從第二排第三格位置開始顯示
  lcd.print(sun);lcd.print(" lux");
  delay(5000);
}
