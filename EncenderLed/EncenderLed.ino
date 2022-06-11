//definir el numero del pin
int ledPin = 13;
void setup()
{
  //hacer que el pin sea de salida
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  //poner el pin en alto para encender el led
  digitalWrite(ledPin, HIGH);
  //esperar 1 segundo
  delay(1000);
  //apagar el led
  digitalWrite(ledPin, LOW);
  //esperar 1seg
  delay(1000);
}
