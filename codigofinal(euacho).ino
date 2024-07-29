#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// Definições de pinos
#define DHTPIN A0           // Pino do sensor de temperatura
#define DHTTYPE DHT11       // Tipo do sensor de temperatura
#define SUS A1              // Pino do sensor de umidade do solo
#define MQ_analogico A2     // Pino do sensor de gás (análogo)
#define MQ_digital 4        // Pino do sensor de gás (digital)
#define pinoSensorChuva A3  // Pino do sensor de chuva

// Criação dos objetos dos sensores e displays
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(128, 64, &Wire, -1);
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);  // LCD

// Variáveis globais
int Valor_Critico = 45;    // Porcentagem mínima de umidade para iniciar a irrigação
int ValAnalogIn;           // Valor analógico do sensor de umidade do solo
int valor_analogico;       // Valor analógico do sensor de gás
int valor_digital;         // Valor digital do sensor de gás
int intensidade = 0;       // Intensidade da chuva

// Definições de caracteres especiais para o LCD
byte onefourthChar[8] = { B00000, B00000, B00000, B00000, B00000, B00000, B11111, B11111 };
byte onefourthCharFlipped[8] = { B11111, B11111, B00000, B00000, B00000, B00000, B00000, B00000 };
byte fullChar[8] = { B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 };
byte triangleChar[8] = { B00001, B00011, B00111, B01111, B11111, B11111, B11111, B11111 };
byte mirroredChar[8] = { B10000, B11000, B11100, B11110, B11111, B11111, B11111, B11111 };
byte triangleCharFlipped[8] = { B11111, B11111, B11111, B11111, B01111, B00111, B00011, B00001 };
byte mirroredCharFlipped[8] = { B11111, B11111, B11111, B11111, B11110, B11100, B11000, B10000 };

void setup() {
    Serial.begin(9600);

    // Inicialização dos sensores e displays
    dht.begin();
    display.begin(SSD1306_SWITCHCAPVCC, 0X3C);
    lcd.begin(16, 2);

    // Criação dos caracteres especiais para o LCD
    lcd.createChar(0, triangleChar);
    lcd.createChar(1, mirroredChar);
    lcd.createChar(2, triangleCharFlipped);
    lcd.createChar(3, mirroredCharFlipped);
    lcd.createChar(4, fullChar); 
    lcd.createChar(5, onefourthCharFlipped);
    lcd.createChar(6, onefourthChar);

    // Configuração dos pinos
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
    int Porcento = map(ValAnalogIn, 0, 1023, 0, 100);
    
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
    intensidade = map(analogRead(pinoSensorChuva), 0, 1023, 1, 100);
    
    // Impressão da intensidade da chuva no monitor serial
    Serial.print("Intensidade da chuva: ");
    Serial.println(intensidade);

    // Display OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Temp: ");
    display.print(t);
    display.println(" C");
    display.print("Hum: ");
    display.print(h);
    display.println(" %");
    display.print("Umidade Solo: ");
    display.print(Porcento);
    display.println(" %");
    display.print("Gas: ");
    display.print(valor_digital == 0 ? "Det" : "No Det");
    display.display();

    // Display LCD - Primeiro conjunto de caracteres
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.write(byte(0)); // Caractere original
    lcd.setCursor(4, 0);
    lcd.write(byte(1)); // Caractere espelhado horizontalmente
    lcd.setCursor(11, 0);
    lcd.write(byte(0)); // Caractere original
    lcd.setCursor(12, 0);
    lcd.write(byte(1)); // Caractere espelhado horizontalmente
    lcd.setCursor(3, 1);
    lcd.write(byte(2)); // Caractere original espelhado verticalmente
    lcd.setCursor(4, 1);
    lcd.write(byte(3)); // Caractere espelhado horizontal e verticalmente
    lcd.setCursor(11, 1);
    lcd.write(byte(2)); // Caractere original espelhado verticalmente
    lcd.setCursor(12, 1);
    lcd.write(byte(3)); // Caractere espelhado horizontal e verticalmente
    lcd.setCursor(6, 1);
    lcd.write(byte(2)); // Caractere original espelhado verticalmente
    lcd.setCursor(9, 1);
    lcd.write(byte(3)); // Caractere espelhado horizontal e verticalmente
    lcd.setCursor(7, 1);
    lcd.write(byte(4)); // Caractere cheio
    lcd.setCursor(8, 1);
    lcd.write(byte(4)); // Caractere cheio

    delay(1000);

    // Display LCD - Segundo conjunto de caracteres
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.write(byte(6)); // Caractere original
    lcd.setCursor(4, 0);
    lcd.write(byte(6)); // Caractere espelhado horizontalmente
    lcd.setCursor(11, 0);
    lcd.write(byte(6)); // Caractere original
    lcd.setCursor(12, 0);
    lcd.write(byte(6)); // Caractere espelhado horizontalmente
    lcd.setCursor(3, 1);
    lcd.write(byte(5)); // Caractere original espelhado verticalmente
    lcd.setCursor(4, 1);
    lcd.write(byte(5)); // Caractere espelhado horizontal e verticalmente
    lcd.setCursor(11, 1);
    lcd.write(byte(5)); // Caractere original espelhado verticalmente
    lcd.setCursor(12, 1);
    lcd.write(byte(5)); // Caractere espelhado horizontal e verticalmente
    lcd.setCursor(6, 1);
    lcd.write(byte(2)); // Caractere original espelhado verticalmente
    lcd.setCursor(9, 1);
    lcd.write(byte(3)); // Caractere espelhado horizontal e verticalmente
    lcd.setCursor(7, 1);
    lcd.write(byte(4)); // Caractere cheio
    lcd.setCursor(8, 1);
    lcd.write(byte(4)); // Caractere cheio

    delay(1000);
}

