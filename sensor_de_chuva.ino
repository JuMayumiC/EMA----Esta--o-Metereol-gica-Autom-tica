/* Programa: Sensor de Chuva */
/* Define os pinos para o Sensor e para os LEDs */
int Pin_Sensor = A0;

/* Variável que armazena a intensidade da chuva */
int intensidade = 0;
void setup() {
/* Define o pino do Sensor como entrada; */
pinMode(Pin_Sensor, INPUT);


} /* End Setup */
void loop() {
/* Realiza a leitura do sensor e armazena uma escala de 1 a
9 */
intensidade = map(analogRead(Pin_Sensor), 0, 900, 1, 9);
/* Para cada valor de intensidade, acenderá uma quantidade
de LEDs */

} /* End loop */

