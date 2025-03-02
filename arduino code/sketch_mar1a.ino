#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define OLED_ADDRESS 0x3C
#define O2_SENSOR_ADDRESS 0x58


#define SDA_PIN 21
#define SCL_PIN 22
#define MQ135_PIN 14

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 0);
  display.print(F("Oxi-Tech"));
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print(F("Developed by- Pradyog"));
  display.setCursor(45, 45);
  display.print(F("At UEMJ"));
  display.display();
  
  for (int i = 0; i <= 100; i += 10) {
    display.fillRect(0, 30, (i * SCREEN_WIDTH) / 100, 10, SSD1306_WHITE);
    display.display();
    delay(500); 
  }

  display.clearDisplay();
  display.display();
  

  delay(1000);
}

void loop() {
  
  Wire.beginTransmission(O2_SENSOR_ADDRESS);
  Wire.write(0x01);
  Wire.endTransmission();
  
  Wire.requestFrom(O2_SENSOR_ADDRESS, 2); 
  
  uint16_t o2Value = 0;
  if (Wire.available() == 2) {
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    
    
    o2Value = (msb << 8) | lsb;
  }
  
  
  int mq135Value = analogRead(MQ135_PIN);
  float voltage = mq135Value * (4 / 4095.0); 
  float aqi = voltage * 100;
  

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(20, 0);
  display.print(F("Oxi-Tech"));
  display.setCursor(0, 20);
  display.print(F("O2:"));
  display.setCursor(40, 20);
  display.print(o2Value);
  display.setCursor(0, 40);
  display.print(F("AQI:"));
  display.setCursor(50, 40);
  display.print(aqi);
  display.display();
  
  delay(1000); 
}