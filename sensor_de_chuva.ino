/* Programa: Sensor de Chuva */
/* Define os pinos para o Sensor e para os LEDs */
int Pin_Sensor = A3;

/* Variável que armazena a intensidade da chuva */
int intensidade = 0;
void setup() {
/* Define o pino do Sensor como entrada; */
pinMode(Pin_Sensor, INPUT);


Serial.begin(9600);


} /* End Setup */
void loop() {
/* Realiza a leitura do sensor e armazena uma escala de 1 a
9 */
intensidade = map(analogRead(Pin_Sensor), 1023, 900, 1, 9);


Serial.print("Intensidade da Chuva: ");

Serial.println(intensidade);

delay(1000);

} /* End loop */

