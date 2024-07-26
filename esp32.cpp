#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Definições de pinos
#define DHTPIN 23           // Pino do sensor de temperatura (DHT11)
#define DHTTYPE DHT11       // Tipo do sensor de temperatura
#define SUS 4               // Pino do sensor de umidade do solo
#define MQ_analogico 35     // Pino do sensor de gás (análogo)
#define MQ_digital 32       // Pino do sensor de gás (digital)
#define pinoSensorChuva 2  // Pino do sensor de chuva

// Criação dos objetos dos sensores
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Variáveis globais
int Valor_Critico = 45;    // Porcentagem mínima de umidade para iniciar a irrigação
int ValAnalogIn;           // Valor analógico do sensor de umidade do solo
int valor_analogico;       // Valor analógico do sensor de gás
int valor_digital;         // Valor digital do sensor de gás
int intensidade = 0;       // Intensidade da chuva

void setup() {
    Serial.begin(9600);
    
    dht.begin();
    
    display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
    
    pinMode(SUS, INPUT);
    pinMode(MQ_analogico, INPUT);
    pinMode(MQ_digital, INPUT);
    pinMode(pinoSensorChuva, INPUT);
}

void loop() {
    // Leitura do sensor de temperatura e umidade
    float h = dht.readHumidity();      // Lê a umidade
    float t = dht.readTemperature();   // Lê a temperatura em Celsius
    
    // Verificação de erro na leitura do sensor de temperatura
    if (isnan(h) || isnan(t)) {
        Serial.println("Falha ao ler o sensor DHT!");
    } else {
        // Formata os dados para impressão no monitor serial
        Serial.print("Umidade: ");
        Serial.print(h);
        Serial.print("%\t");
        Serial.print("Temperatura: ");
        Serial.print(t);
        Serial.println("°C");
    }
    
    // Leitura do sensor de umidade do solo
    ValAnalogIn = analogRead(SUS);
    int Porcento = map(ValAnalogIn, 0, 4095, 0, 100); // Ajuste para a resolução do ESP32 (12 bits)
    
    // Impressão da umidade do solo no monitor serial
    Serial.print("Umidade do Solo: ");
    Serial.print(Porcento);
    Serial.println("%");
    
    // Verificação da umidade do solo
    if (Porcento <= Valor_Critico) {
        Serial.println("Umidade baixa!");
    } else {
        Serial.println("Umidade adequada...");
    }
    
    // Leitura do sensor de gás
    valor_analogico = analogRead(MQ_analogico);
    valor_digital = digitalRead(MQ_digital);
    
    // Impressão do nível de gás no monitor serial
    Serial.print("Nível de Gás (analog): ");
    Serial.print(valor_analogico);
    Serial.print("\tNível de Gás (digital): ");
    if (valor_digital == 0) {
        Serial.println("GÁS DETECTADO !!!");
    } else {
        Serial.println("GÁS AUSENTE !!!");
    }
    
    // Leitura do sensor de chuva
    intensidade = map(analogRead(pinoSensorChuva), 0, 4095, 1, 100); // Ajuste para a resolução do ESP32 (12 bits)
    
    // Impressão da intensidade da chuva no monitor serial
    Serial.print("Intensidade da chuva: ");
    Serial.println(intensidade);
    
    delay(2000);  // Aguarda 2 segundos para a próxima leitura
}
