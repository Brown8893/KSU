void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
}

void loop() {
  /*
  Serial3.print("Vo1=55");
  Serial3.print("&Lux1=55");
  Serial3.print("&Vo2=55");
  Serial3.print("&Lux2=55");
  Serial3.print("&Vo3=55");
  Serial3.print("&Lux3=55");
  */
  Serial3.println("Vo1=55&Lux1=5500&Vo2=505&Lux2=0055&Vo3=505&Lux3=505 \n");
  Serial.println("Vo1=55&Lux1=55&Vo2=55&Lux2=55&Vo3=55&Lux3=505");
  delay(1000);
}
