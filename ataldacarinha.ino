#include <LiquidCrystal.h>

// Inicializa o LCD com os números de pinos corretos.
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte fullChar[] = {
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11111  // 11111 em binário
};

// Define o caractere original com padrão em triângulo.
byte triangleChar[] = {
  B00001, // 00001 em binário
  B00011, // 00011 em binário
  B00111, // 00111 em binário
  B01111, // 01111 em binário
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11111  // 11111 em binário
};

// Define o caractere espelhado horizontalmente.
byte mirroredChar[] = {
  B10000, // 10000 em binário
  B11000, // 11000 em binário
  B11100, // 11100 em binário
  B11110, // 11110 em binário
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11111  // 11111 em binário
};

// Define o caractere original espelhado verticalmente.
byte triangleCharFlipped[] = {
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B01111, // 01111 em binário
  B00111, // 00111 em binário
  B00011, // 00011 em binário
  B00001  // 00001 em binário
};

// Define o caractere espelhado horizontalmente e também verticalmente.
byte mirroredCharFlipped[] = {
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11111, // 11111 em binário
  B11110, // 11110 em binário
  B11100, // 11100 em binário
  B11000, // 11000 em binário
  B10000  // 10000 em binário
};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, triangleChar);          // Carrega o caractere original
  lcd.createChar(1, mirroredChar);          // Carrega o caractere espelhado horizontalmente
  lcd.createChar(2, triangleCharFlipped);   // Carrega o caractere original espelhado verticalmente
  lcd.createChar(3, mirroredCharFlipped);   // Carrega o caractere espelhado horizontal e verticalmente
  lcd.createChar(4, fullChar);        
}

void loop() {
  lcd.clear();
  // Exibe o primeiro conjunto de caracteres na primeira linha
  lcd.setCursor(3, 0);
  lcd.write(byte(0)); // Caractere original
  lcd.setCursor(4, 0);
  lcd.write(byte(1)); // Caractere espelhado horizontalmente

  // Exibe o segundo conjunto de caracteres na primeira linha com espaçamento de 6 caracteres
  lcd.setCursor(11, 0);
  lcd.write(byte(0)); // Caractere original
  lcd.setCursor(12, 0);
  lcd.write(byte(1)); // Caractere espelhado horizontalmente

  // Exibe o primeiro conjunto de caracteres na segunda linha
  lcd.setCursor(3, 1);
  lcd.write(byte(2)); // Caractere original espelhado verticalmente
  lcd.setCursor(4, 1);
  lcd.write(byte(3)); // Caractere espelhado horizontal e verticalmente

  // Exibe o segundo conjunto de caracteres na segunda linha com espaçamento de 6 caracteres
  lcd.setCursor(11, 1);
  lcd.write(byte(2)); // Caractere original espelhado verticalmente
  lcd.setCursor(12, 1);
  lcd.write(byte(3)); // Caractere espelhado horizontal e verticalmente
  
  // Exibe o primeiro conjunto de caracteres na segunda linha
  lcd.setCursor(6, 1);
  lcd.write(byte(2)); // Caractere original espelhado verticalmente
  lcd.setCursor(9, 1);
  lcd.write(byte(3)); // Caractere espelhado horizontal e verticalmente
  
   // Exibe o primeiro conjunto de caracteres na segunda linha
  lcd.setCursor(7, 1);
  lcd.write(byte(4)); // Caractere original espelhado verticalmente
  lcd.setCursor(8, 1);
  lcd.write(byte(4)); // Caractere espelhado horizontal e verticalmente
  

  delay(2000); // Espera 2 segundos
}
