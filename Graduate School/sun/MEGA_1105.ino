#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫
#include <LiquidCrystal.h>

uint8_t readStatus = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read sensor

float digitalValue1, digitalValue2, digitalValue3, digitalValue4, v1, v2, v3, v4;
float sun1, sun2, sun3, sun4;
char state = 1;


void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.home();   //LCD歸零，清除所有內容
  lcd.clear();  //LCD歸零，清除所有內容
}

void loop() {
  digitalValue1 = analogRead(A8);// read the value from the analog channel
  v1 = (digitalValue1 * 5.00)/1024.00;
  sun1 = 125000.00*(125.00*(((v1/200.00*1000.00)-4.00)/1000.00));
  digitalValue2 = analogRead(A9);// read the value from the analog channel
  v2 = (digitalValue2 * 5.00)/1024.00;
  sun2 = 125000.00*(125.00*(((v2/200.00*1000.00)-4.00)/1000.00));
  digitalValue3 = analogRead(A10);  // read the value from the analog channel
  v3 = (digitalValue3 * 5.00)/1024.00;
  sun3 = 125000.00*(125.00*(((v3/200.00*1000.00)-4.00)/1000.00));
  digitalValue4 = analogRead(A11);  // read the value from the analog channel
  v4 = (digitalValue4 * 5.00)/1024.00;
  sun4 = 125000.00*(125.00*(((v4/200.00*1000.00)-4.00)/1000.00));

  //Serial3.println("Vo1=55&Lux1=5500&Vo2=505&Lux2=0055&Vo3=505&Lux3=505 \n");
  Serial3.println("Vo1="+String(v1,3)+"&Lux1="+String(sun1,3)+"&Vo2="+String(v2,3)+"&Lux2="+String(sun2,3)+"&Vo3="+String(v3,3)+"&Lux3="+String(sun3,3)+"&Vo4="+String(v4,3)+"&Lux4="+String(sun4,3)+" \n");
  Serial.println("Vo1="+String(v1,3)+"&Lux1="+String(sun1,3)+"&Vo2="+String(v2,3)+"&Lux2="+String(sun2,3)+"&Vo3="+String(v3,3)+"&Lux3="+String(sun3,3)+"&Vo4="+String(v4,3)+"&Lux4="+String(sun4,3)+" \n");
  delay(60000);

  lcd.setCursor(0, 0); // (colum, row)
  lcd.print("1=");lcd.print( float(v1), 2); lcd.print("v "); lcd.print("2=");lcd.print( float(v2), 2); lcd.print("v");
  lcd.setCursor(0, 1); // (colum, row)
  lcd.print("3=");lcd.print( float(v3), 2); lcd.print("v ");
}
