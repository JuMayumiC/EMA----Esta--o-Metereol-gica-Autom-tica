

// Adafruit GFX Library - Version: Latest 
#include <Adafruit_GFX.h>


// Adafruit SSD1306 - Version: Latest 
#include <Adafruit_SSD1306.h>


// Adafruit Unified Sensor - Version: Latest 
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


#define DHTPIN A0
#define DHTTYPE DHT11

//cria objeto de sensor da temperatura 
DHT_Unified dht(DHTPIN, DHTTYPE);
float delayMS ;

Adafruit_SSD1306 display(128, 64, &Wire, -1);



void setup() {
  Serial.begin(9600); 
  
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 500;
  
  display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
  
  
}

void loop() {
  delay(delayMS);
  
  sensors_event_t event;
  
  dht.temperature().getEvent(&event);
  
  medida = ultrasonic.read();
  
  if(isnan(event.temperature)) {
    Serial.println("Erro de leitura da temperatura!");
  } else {
    Monitor_Serial_Temperatura(event.temperature);
    Display_Temperatura(event.temperature);
    delay(500);
    
  }
  
  
  
}

void Monitor_Serial_Temperatura(float T){
  Serial.print("Temperatura: ");
  Serial.print(T);
  Serial.println(" C");
}

void Display_Temperatura(float T) {
  
  display.clearDisplay();
  
  display.setCursor(10, 0);
  
  display.setTextSize(1);
  
  display.setTextColor(1);
  
  display.print("-- TEMPERATURA --");
  
  display.drawRoundRect(0, 12, 128, 40, 10, WHITE);
  
  display.setTextSize(2);
  display.setCursor(25, 25);
  display.print(T);
  display.print("C");
  
  display.display();
}

