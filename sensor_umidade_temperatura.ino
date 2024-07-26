#include <Adafruit_Sensor.h>
#include "DHT.h"

/* Define o tipo de sensor e o pino ao qual está conectado */
DHT dht(A0, DHT11);

void setup() {
  /* Inicia a comunicação serial */
  Serial.begin(9600);
  
  /* Inicia o sensor */
  dht.begin();
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
}
