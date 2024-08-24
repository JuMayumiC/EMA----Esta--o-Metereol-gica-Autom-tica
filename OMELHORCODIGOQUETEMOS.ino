#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Definições de pinos para a ESP8266
#define DHTPIN 2           // Pino do sensor de temperatura
#define DHTTYPE DHT11       // Tipo do sensor de temperatura
#define SUS 14              // Pino do sensor de umidade do solo
#define MQ_digital 25      // Pino do sensor de gás (digital)
#define pinoSensorChuva 12  // Pino do sensor de chuva

// Criação dos objetos dos sensores
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Variáveis globais
int Valor_Critico = 45;  // Porcentagem mínima de umidade para iniciar a irrigação
int valor_digital;       // Valor digital do sensor de gás
int intensidade = 0;     // Intensidade da chuva
int umidadeSolo = 0;     // Umidade do solo ajustada

// Configurações do Wi-Fi
const char* ssid = "Unexhome";        // Substitua pelo SSID da sua rede Wi-Fi
const char* password = "#Celebrando2025"; // Substitua pela senha da sua rede Wi-Fi

// Criação do servidor na porta 80
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(SUS, INPUT);
  pinMode(MQ_digital, INPUT);
  pinMode(pinoSensorChuva, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi");

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Novo cliente");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Enviar o cabeçalho da resposta HTTP
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type: text/html");
            client.println();

            // Atualizar os dados dos sensores
            float h = dht.readHumidity();
            float t = dht.readTemperature();
            int ValDigitalIn = digitalRead(SUS);
            int Porcento = 100 - (ValDigitalIn * 100);
            valor_digital = digitalRead(MQ_digital);
            intensidade = 100 - (digitalRead(pinoSensorChuva) * 100);

            // Criar o HTML com os dados dos sensores
            String html = "<!DOCTYPE html>";
            html += "<html lang=\"pt-br\">";
            html += "<head>";
            html += "<meta charset=\"UTF-8\">";
            html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
            html += "<style>";
            html += ":root {";
            html += "    --cor-de-fundo: #4B4B4B;";
            html += "    --cor-do-texto: #FFFFFF;";
            html += "    --cor-do-botao: #6F2DA8;";
            html += "    --cor-do-botao-texto: #FFFFFF;";
            html += "    --cor-do-botao-hover: #B3A0C5;";
            html += "    --cor-do-botao-texto-hover: #FFFFFF;";
            html += "    --cor-do-botao-ativo: #B3A0C5;";
            html += "    --cor-do-titulo: #70c673;";
            html += "    --cor-de-fundo-dados: #4682B4;";
            html += "    --fonte-do-site: 'Roboto', sans-serif;";
            html += "}";
            html += "html, body {";
            html += "    height: 100%;";
            html += "    margin: 0;";
            html += "    padding: 0;";
            html += "}";
            html += "body {";
            html += "    background-color: var(--cor-de-fundo);";
            html += "    color: var(--cor-do-texto);";
            html += "    font-family: var(--fonte-do-site);";
            html += "    margin: 0;";
            html += "    padding: 0;";
            html += "    flex-direction: column;";
            html += "}";
            html += ".wrapper {";
            html += "    display: flex;";
            html += "    flex-direction: column;";
            html += "    min-height: 100vh;";
            html += "}";
            html += "header {";
            html += "    background-color: var(--cor-de-fundo);";
            html += "    color: var(--cor-do-texto);";
            html += "    padding: 20px;";
            html += "    text-align: center;";
            html += "}";
            html += "img {";
            html += "    width: 250px;";
            html += "    height: auto;";
            html += "}";
            html += ".menu ul, a {";
            html += "    list-style-type: none;";
            html += "    margin: 0px;";
            html += "    padding: 0px;";
            html += "    overflow: hidden;";
            html += "    color: var(--cor-do-botao-texto);";
            html += "    text-decoration: none;";
            html += "}";
            html += "button {";
            html += "    background-color: var(--cor-do-botao);";
            html += "    color: #FFFFFF;";
            html += "    font-weight: 600;";
            html += "    border-radius: 50px;";
            html += "    padding: 15px 30px;";
            html += "    margin: 10px 0;";
            html += "    cursor: pointer;";
            html += "    font-size: 30px;";
            html += "}";
            html += "button:hover {";
            html += "    background-color: var(--cor-do-botao-hover);";
            html += "}";
            html += "h1 {";
            html += "    color: var(--cor-do-titulo);";
            html += "    font-size: 30px;";
            html += "    text-align: center;";
            html += "}";
            html += ".dado {";
            html += "    background-color: var(--cor-de-fundo-dados);";
            html += "    padding: 20px;";
            html += "    margin: 20px;";
            html += "    border-radius: 10px;";
            html += "}";
            html += "footer {";
            html += "    color: var(--cor-do-texto);";
            html += "    text-align: center;";
            html += "}";
            html += "footer p {";
            html += "    margin: 0;";
            html += "    padding: 10px;";
            html += "    font-family: var(--fonte-do-site);";
            html += "    font-size: 20px;";
            html += "    font-weight: 700;";
            html += "}";
            html += "</style>";
            html += "</head>";
            html += "<body>";
            html += "<header>";
            html += "<div class=\"container\">";
            html += "<div class=\"logo\">";
            html += "<img src=\"https://github.com/JuMayumiC/EMAP-interface/blob/main/EMAP%20logotipo.png?raw=true\" alt=\"Logo da EMAP\">";
            html += "</div>";
            html += "<h1>Estação Metereológica Automática Portátil</h1>";
            html += "</div>";
            html += "</header>";
            html += "<section class=\"dados\">";
            html += "<div class=\"dado\">";
            html += "<h2>Temperatura: " + String(t, 1) + "ºC</h2>";
            html += "</div>";
            html += "<div class=\"dado\">";
            html += "<h2>Umidade: " + String(h, 1) + "%</h2>";
            html += "</div>";
            html += "<div class=\"dado\">";
            html += "<h2>Intensidade da Chuva: " + String(intensidade) + "</h2>";
            html += "</div>";
            html += "<div class=\"dado\">";
            html += "<h2>Umidade do Solo: " + String(Porcento) + "%</h2>";
            html += "<h3>" + String(Porcento <= Valor_Critico ? "Umidade Baixa !" : "Umidade Adequada...") + "</h3>";
            html += "</div>";
            html += "<div class=\"dado\">";
            html += "<h2>Nível Detectado: " + String(valor_digital) + "%</h2>";
            html += "<h3>" + String(valor_digital > 0 ? "GÁS DETECTADO !!!" : "GÁS AUSENTE !!!") + "</h3>";
            html += "</div>";
            html += "</section>";
            html += "<footer>";
            html += "<div class=\"container\">";
            html += "<p>Desenvolvido por: <a href=\"https://github.com/JuMayumiC\">Mayumi</a></p>";
            html += "</div>";
            html += "</footer>";
            html += "</body>";
            html += "</html>";

            // Enviar o HTML
            client.print(html);

            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    delay(1);
    client.stop();
    Serial.println("Cliente desconectado");
  }
}
