#include <Adafruit_Sensor.h>
#include "DHT.h"



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
    /* Realiza a leitura do sensor e armazena os dados nas variáveis h e t */
  float h = dht.readHumidity(); // Lê a umidade
  float t = dht.readTemperature(); // Lê a temperatura em Celsius
  
  /* Verifica se a leitura do sensor foi bem-sucedida */
  if (isnan(h) || isnan(t)) {
    Serial.println("Falha ao ler o sensor DHT!");
    return;
  }
  
  /* Formata os dados de umidade e temperatura para impressão no monitor serial */
  String H = String(h, 0); // Umidade sem casas decimais
  String T = String(t, 1); // Temperatura com uma casa decimal
  
  /* Escreve no monitor serial os valores lidos de Umidade e Temperatura */
  Serial.print("Umidade: ");
  Serial.print(H);
  Serial.print("%");
  Serial.print("\t");
  Serial.print("Temperatura: ");
  Serial.print(T);
  Serial.println("°C");
  
  /* Aguarda 2 segundos para a próxima leitura */
  delay(2000);
    
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

    intensidade = map(analogRead(Pin_Sensor), 0, 1023, 1, 100);
    
    Serial.print("Intensidade da chuva: ");
    Serial.println(intensidade);
    
    delay(500);
}