//definir el pin del led
int ledPin = 4;
//definir el pin del pulsador
int pulsador = 2;
//definir una variable en LOW
int estado = LOW;
void setup()
{
  //hacer que el pin sea de salida
  pinMode(ledPin, OUTPUT);
  //hacer que el pin sea de entrada
  pinMode(pulsador, INPUT);
}
void loop()
{
  while(digitalRead(pulsador)==LOW){
  }
  estado = digitalRead(ledPin);
  digitalWrite(ledPin,!estado);
  while(digitalRead(pulsador)==HIGH){
  }
        
}
