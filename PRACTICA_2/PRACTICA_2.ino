#define LED 2
#define PULSADOR 3
int contador = 0;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("INICIADO");
  Serial.print("Número de interrupciones: ");
  Serial.println(contador);
  pinMode(LED, OUTPUT);
  pinMode(PULSADOR, INPUT_PULLUP);
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
}

void actualizar_contador()
{
  contador++;
  Serial.print("Número de interrupciones: ");
  Serial.println(contador);
}
