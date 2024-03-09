#define LED 2
#define PULSADOR 3
#define LED2 4
int contador = 0;
bool estado_led = false;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("INICIADO");
  Serial.print("Número de interrupciones: ");
  Serial.println(contador);
  pinMode(LED, OUTPUT);
  pinMode(PULSADOR, INPUT_PULLUP);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED, LOW);
  attachInterrupt(digitalPinToInterrupt(PULSADOR), actualizar_contador, RISING);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(200);
  if (estado_led==true)
  {
    digitalWrite(LED2, HIGH);
  }
  else
  {
    digitalWrite(LED2, LOW);
  }
}

void actualizar_contador()
{
  contador++;
  estado_led=!estado_led;
  Serial.print("Número de interrupciones: ");
  Serial.println(contador);
}
