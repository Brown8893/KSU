#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫
#include <WiFi.h>
#include <LiquidCrystal.h>

// LCD I2C位址，默認為0x27或0x3F，依據背板的晶片不同而有差異，16、2為LCD顯示器大小。
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int sensorPin = A0;   // select the input pin for the potentiometer
int digitalValue = 0;  // variable to store the value coming from the sensor
float analogVoltage = 0.00;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  lcd.begin(16,2);
  lcd.backlight();
}

void loop() {
  digitalValue = analogRead(sensorPin);// read the value from the analog channel
  Serial.print("digital value = ");
  Serial.print(digitalValue);        //print digital value on serial monitor
  //convert digital value to analog voltage
  float analogVoltage = (digitalValue * 5.00)/1024.00;
  Serial.print("  analog voltage = ");
  Serial.print(analogVoltage,5);

  float sun = 125000.0*(125.0*(((analogVoltage/200.0*1000.0)-4.0)/1000.0));
  Serial.print("  lux = ");
  Serial.println(sun);
  if (analogVoltage < 0.8){
    lcd.setCursor(2, 0); // (colum, row)從第一排的第三個位置開始顯示
    lcd.print(analogVoltage,5);lcd.print("v");
    lcd.setCursor(2, 1); // (colum,row)從第二排第三格位置開始顯示
    lcd.print("0");lcd.print(" lux");
    delay(5000);
    lcd.clear();
  } else{
    lcd.setCursor(2, 0); // (colum, row)從第一排的第三個位置開始顯示
    lcd.print(analogVoltage,5);lcd.print("v");
    lcd.setCursor(2, 1); // (colum,row)從第二排第三格位置開始顯示
    lcd.print(sun,4);lcd.print(" lux");
    delay(5000);
    lcd.clear();
  }  
}