#define PULSADOR1 2
#define PULSADOR2 3
volatile int contador=0;
int contador2=0;
const int tiempo_limite = 40;
long tiempo = 0;

void setup() 
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("INICIADO");
  Serial.print("Número de interrupciones: ");
  Serial.println(contador);
  pinMode(PULSADOR1, INPUT_PULLUP);
  pinMode(PULSADOR2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PULSADOR1), actualizar_contador, RISING);
  attachInterrupt(digitalPinToInterrupt(PULSADOR2), reiniciar_contador, RISING);
}

void loop() 
{
  if (contador2 != contador)
  {
    contador2=contador;
    if (contador2!=0)
    {
      Serial.print("Número de interrupciones: ");
    }
    else
    {
      Serial.println("Contador reiniciado");
      Serial.print("Número de interrupciones: ");
    }
    Serial.println(contador2);
  }
}

void actualizar_contador()
{
  if (millis()-tiempo > tiempo_limite)
  {
    contador++;
    tiempo=millis();
  }
}

void reiniciar_contador()
{
  if (millis()-tiempo > tiempo_limite)
  {
    contador=0;
  }
}