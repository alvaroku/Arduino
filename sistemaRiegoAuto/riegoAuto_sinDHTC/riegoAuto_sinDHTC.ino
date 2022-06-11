#include <SPI.h>
#define humidity_sensor_pin A0
#define ldr_pin A5
//Bibliotecas para los módulos sensores usados necesarias
//Y definición de variables para los sensores de humedad y LDR en los pines A0 y A5
 
int ldr_value = 0;
int water_pump_pin = 3;
int water_pump_speed = 255;

void setup() {
  Serial.begin(9600);
}
void loop() {
  Serial.println("");
   
  int ground_humidity_value = map(analogRead(humidity_sensor_pin), 0, 1023, 100, 0);
  Serial.print("Humedad en suelo: ");
  Serial.print(ground_humidity_value);
  Serial.print("%");
  Serial.println("\n*******************************");
  int ldr_value = map(analogRead(ldr_pin), 1023, 0, 100, 0);
  Serial.print("Luz: ");
  Serial.print(ldr_value);
  Serial.print("%");
  Serial.println("\n*******************************");
 
//**************************************************************
// Condiciones de riego 
// Si la humedad en el suelo es igual o inferior al 60%, y la cantidad de luz sea menor al 80%,

// En caso de que no se  cumpla alguno o ninguno de los 2 requisitos anteriores,
// el sistema no riega
//**************************************************************

 if( ground_humidity_value <= 50 && ldr_value<=80) {//&& temperature<100
 digitalWrite(water_pump_pin, HIGH);
 Serial.println("Regando");
 analogWrite(water_pump_pin, water_pump_speed);
 
 }
 else{
 digitalWrite(water_pump_pin, LOW);
 Serial.println("Riego detenido");
 
 }
 delay (2000); 
// Ejecuta el código cada 2000 milisegundos, es decir, 2 segundos. Puedes variar la frecuencia de muestreo
}
