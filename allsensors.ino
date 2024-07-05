//Bibliotecas 
// Adafruit GFX Library - Version: Latest 
#include <Adafruit_GFX.h>


// Adafruit SSD1306 - Version: Latest 
#include <Adafruit_SSD1306.h>


// Adafruit Unified Sensor - Version: Latest 
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>



// Definições de pinos
//sensor de temperatura
#define DHTPIN A0
#define DHTTYPE DHT11
//sensor de umidade do solo
#define SUS A1
//sensor de gás fumaça
#define MQ_analogico A2
#define MQ_digital 4
//sensor de chuva
#define pinoSensorChuva A3



//cria objeto de sensor da temperatura 
DHT_Unified dht(DHTPIN, DHTTYPE);
float delayMS ;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Variáveis
/* Porcentagem de umidade mínima para iniciar a irrigação */
int Valor_Critico = 45;
/* Variável para armazenar o valor analógico do sensor */
int ValAnalogIn;
//variáveis do sensor de gás fumaça
int valor_analogico;
int valor_digital;
/* Variável que armazena a intensidade da chuva */
int intensidade = 0;

void setup() {
    Serial.begin(9600); 
    
    dht.begin();
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    delayMS = sensor.min_delay / 500;
    
    display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
    
    pinMode(SUS, INPUT);
    pinMode(MQ_analogico, INPUT);
    pinMode(MQ_digital, INPUT);
    pinMode(pinoSensorChuva, INPUT);
}


void loop() {
    delay(delayMS);
    
    sensors_event_t event;
    
    dht.temperature().getEvent(&event);
    
    ValAnalogIn = analogRead(SUS);
    int Porcento = map(ValAnalogIn, 1023, 0, 0, 100);
    
    valor_analogico = analogRead(MQ_analogico);
    valor_digital = digitalRead(MQ_digital);
    
    intensidade = analogRead(pinoSensorChuva);
    
    if(isnan(event.temperature)) {
        Serial.println("Erro de leitura da temperatura!");
    } else {
        Monitor_Serial_Temperatura(event.temperature);
        Display_Temperatura(event.temperature);
        delay(500);
        
    }
    
    Serial.print(Porcento);
    Serial.println("%");
    
    if (Porcento <= Valor_Critico) {
        Serial.println("Umidade baixa!");
    } else {
        Serial.println("Umidade Adequada...");
    }
    
    Serial.print("Nível detectado : ");
    Serial.print(valor_analogico);
    Serial.print(" || ");
    if (valor_digital == 0)
    {
        Serial.println("GÁS DETECTADO !!!");
    }
    else
    {
        Serial.println("GAS AUSENTE !!!");
    }
    
    Serial.print("Intensidade da chuva: ");
    Serial.println(intensidade);
    
    delay(500);
}