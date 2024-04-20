#define TRIGGER 4
#define ECHO 5
#define PULSADOR 3
typedef enum{
  ESPERA,
  MEDICION,
  ENVIO
}sensor;
sensor estado = ESPERA;
long t;
long d;
const int tiempo_limite = 40;
long tiempo = 0;
long tiempo_aux1=0;
long tiempo_aux2=0;

void setup()
{
  Serial.begin(9600);
  pinMode(PULSADOR, INPUT_PULLUP);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIGGER, LOW);
  attachInterrupt(digitalPinToInterrupt(PULSADOR), medir, RISING);
}

void loop()
{
  switch (estado)
  {
    case ESPERA:
    Serial.println("Pulsar el boton para hacer una medicion");
    delay(2000);
    break;
    case MEDICION:
    digitalWrite(TRIGGER, HIGH);
    delay(10);
    digitalWrite(TRIGGER, LOW);
    t = pulseIn(ECHO, HIGH);
    d=t/69;
    if (tiempo_aux1==0)
    {
      tiempo_aux1=millis();
    }
    estado=ENVIO;
    break;
    case ENVIO:
    Serial.print("La distancia medida es de ");
    Serial.print(d);
    Serial.println(" cm.");
    tiempo_aux2=millis();
    if (tiempo_aux2-tiempo_aux1<5000)
    {
      estado=MEDICION;
    }
    else
    {
      tiempo_aux1=0;
      estado=ESPERA;
    }
    break;
  }
}

void medir()
{
  if (millis()-tiempo > tiempo_limite)
  {
    estado=MEDICION;
    Serial.println("Midiendo");
    tiempo=millis();
  }
}