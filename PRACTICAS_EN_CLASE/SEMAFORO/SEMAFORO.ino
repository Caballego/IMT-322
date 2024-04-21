int led_rojo=7;
int led_amarillo=8;
int led_verde=9;
int color=1;
typedef enum {
  ROJO,
  AMARILLO,
  VERDE
}Fsm;
Fsm estados = ROJO;

void setup() 
  {
  pinMode(led_rojo, OUTPUT);
  pinMode(led_amarillo, OUTPUT);
  pinMode(led_verde, OUTPUT);
  digitalWrite(led_rojo, LOW);
  digitalWrite(led_amarillo, LOW);
  digitalWrite(led_verde, LOW);
  }

void loop() 
{
  switch (estados)
  {
    case ROJO:
    digitalWrite(led_rojo, HIGH);
    delay(5000);
    estados=AMARILLO;
    break;
    case AMARILLO:
    digitalWrite(led_rojo, LOW);
    digitalWrite(led_verde, HIGH);
    delay(4000);
    estados=VERDE;
    break;
    case VERDE:
    digitalWrite(led_verde, LOW);
    digitalWrite(led_amarillo, HIGH);
    delay(1000);
    digitalWrite(led_amarillo, LOW);
    estados=ROJO;
    break;
  }
}