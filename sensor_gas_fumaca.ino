/* Programa: Detector de gás e fumaça */
/* Definição dos pinos */
#define MQ_analogico A0
#define MQ_digital 4

/* Variáveis */
int valor_analogico;
int valor_digital;
void setup() {
/* Inicia a comunicação serial com velocidade de 9600 bauds
*/
Serial.begin(9600);
/* Configura os pinos de entrada e saída */
pinMode(MQ_analogico, INPUT);
pinMode(MQ_digital, INPUT);

}/* end setup */
void loop() {
valor_analogico = analogRead(MQ_analogico);
valor_digital = digitalRead(MQ_digital);
 Serial.print("Nível detectado : ");
Serial.print(valor_analogico);
Serial.print(" || ");
if (valor_digital == 0)
{
 Serial .println("GÁS DETECTADO !!!");

}/* end if */
else
{
 Serial.println("GAS AUSENTE !!!");

}/* end else */
delay(500);
}/* end loop */