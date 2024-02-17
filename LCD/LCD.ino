#include <LiquidCrystal.h>

//Crear el objeto LCD con los números correspondientes (rs, en, d4, d5, d6, d7)

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  // Inicializar el LCD con el número de  columnas y filas del LCD
  lcd.begin(20,4);
  // Escribimos el Mensaje en el LCD
  lcd.setCursor(5,0);
  lcd.print("UCB TARIJA");
  lcd.setCursor(0,1);
  lcd.print("SISTEMAS EMBEBIDOS I");
  lcd.setCursor(3,2);
  lcd.print("LABORATORIO II");
}

void loop() {
  // Ubicamos el cursor en (columna:0) de la tercera línea(fila:3)
  lcd.setCursor(1,3);
  lcd.print("VICTOR CABALLERO");
  lcd.setCursor(18,3);
  lcd.print(millis()/1000);
}
