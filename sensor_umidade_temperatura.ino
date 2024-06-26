/* Programa: Sensor de Temperatura e Umidade DHT11 */
/* Inclui a biblioteca de controle do sensor */
#include "DHT.h"
/* Cria o objeto dht para o sensor DHT11 no pino A0 do Arduino
*/
DHT dht(A0, DHT11);
void setup()
{
/* Inicia a comunicação serial; */
Serial.begin(9600);
/* Inicia o objeto do sensor */
dht.begin();
}
void loop()
{
/* Realiza a leitura do sensor e armazena os dados nas
variáveis h e t */
float h = dht.readHumidity();
float t = dht.readTemperature();
/* Faz os dados de umidade ficarem sem casas decimais */
String H = String(h,0);
/* Faz os dados da temperatura ficarem com uma casa decimal */
String T = String(t,1);
/* Escreve no monitor serial os valores lidos de Umidade e
Temperatura */
Serial.print("Umidade: ");
Serial.print(H);
Serial.print("%");
Serial.print("\t");
Serial.print("Temperatura: ");
Serial.print(T);
Serial.println("°C");
/* Aguarda 2 segundos para a nova leitura */
delay(2000);
}