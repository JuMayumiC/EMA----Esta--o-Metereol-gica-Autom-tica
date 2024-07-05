/* Programa: Sensor de Chuva */
/* Define os pinos para o Sensor e para os LEDs */
int Pin_Sensor = A0;
int LED_VERMELHO_3 = 2;
int LED_VERMELHO_2 = 3;
int LED_VERMELHO_1 = 4;
int LED_AMARELO_3 = 5;
int LED_AMARELO_2 = 6;
int LED_AMARELO_1 = 7;

int LED_VERDE_3 = 8;
int LED_VERDE_2 = 9;
int LED_VERDE_1 = 10;
/* Variável que armazena a intensidade da chuva */
int intensidade = 0;
void setup() {
/* Define o pino do Sensor como entrada; */
pinMode(Pin_Sensor, INPUT);
/* Loop para definir os pinos 2 ao 10 como saídas; */
for (int i = 2; i <= 10; i++) {
 pinMode(i, OUTPUT);
} /* End for */
} /* End Setup */
void loop() {
/* Realiza a leitura do sensor e armazena uma escala de 1 a
9 */
intensidade = map(analogRead(Pin_Sensor), 0, 900, 1, 9);
/* Para cada valor de intensidade, acenderá uma quantidade
de LEDs */
switch (intensidade) {
 case 1:
 /* Chama a função para acionar os LEDs */
 leds(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,
HIGH);
 break;
 case 2:
     leds(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,
LOW);

 break;
 case 3:
     leds(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW,
LOW);
 break;
 case 4:
     leds(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW,
LOW);
 break;
 case 5:
     leds(HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW);
 break;
 case 6:
     leds(HIGH, HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW);
 break;
 case 7:
     leds(HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW, LOW);
 break;
 case 8:
     leds(HIGH, HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW);
 break;
 case 9:
     leds(HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW);
 break;
 /* Caso não esteja chovendo, permanecerá acesos os três
LEDs vermelhos */
 default:
     leds(LOW, LOW, LOW, LOW, LOW, LOW, HIGH, HIGH, HIGH);
 break;
} /* End swich */
} /* End loop */

/* Função responsável por acionar os LEDs */
void leds(boolean LVd1, boolean LVd2, boolean LVd3, boolean
LAm1, boolean LAm2, boolean LAm3, boolean LVm1, boolean LVm2,
boolean LVm3) {
digitalWrite(LED_VERDE_1, LVd1);
digitalWrite(LED_VERDE_2, LVd2);
digitalWrite(LED_VERDE_3, LVd3);
digitalWrite(LED_AMARELO_1, LAm1);
digitalWrite(LED_AMARELO_2, LAm2);
digitalWrite(LED_AMARELO_3, LAm3);
digitalWrite(LED_VERMELHO_1, LVm1);
digitalWrite(LED_VERMELHO_2, LVm2);
digitalWrite(LED_VERMELHO_3, LVm3);
}