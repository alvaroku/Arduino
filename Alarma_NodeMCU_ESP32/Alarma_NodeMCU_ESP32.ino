#include <WiFi.h>
#include <HTTPClient.h>

//String apiKey = "522344";              //Add your Token number that bot has sent you on WhatsApp messenger
//String phone_number = "+5219992658918"; //Add your WhatsApp app registered phone number (same number that bot send you in url)
String apiKey = "824731";              //Add your Token number that bot has sent you on WhatsApp messenger
String phone_number = "+5219919596720"; //Add your WhatsApp app registered phone number (same number that bot send you in url)

String url;

const char* ssid = "Telcel-HUAWEI_B311_A734";
const char* password = "EG9Q2N8453Q";
//const char* ssid = "INFINITUM6973";
//const char* password = "x3ERJ7zW6X";
#define pinLedAlarma 2       // Indicador de alarma LED rojo
#define pinTrig 4      // GPIO 14
#define pinEcho 5      // GPIO 12
#define pinLedOk 23 //indicador conexion a internet LED verde
void  message_to_whatsapp(String message)       // user define function to send meassage to WhatsApp app
{
  //adding all number, your api key, your message into one complete url
  url = "https://api.callmebot.com/whatsapp.php?phone=" + phone_number + "&apikey=" + apiKey + "&text=" + urlencode(message);

  postData(); // calling postData to run the above-generated url once so that you will receive a message.
}

void postData()     //userDefine function used to call api(POST data)
{
  int httpCode;     // variable used to get the responce http code after calling api
  HTTPClient http;  // Declare object of class HTTPClient
  http.begin(url);  // begin the HTTPClient object with generated url
  httpCode = http.POST(url); // Finaly Post the URL with this function and it will store the http code
  if (httpCode == 200)      // Check if the responce http code is 200
  {
    Serial.println("Sent ok."); // print message sent ok message
  }
  else                      // if response HTTP code is not 200 it means there is some error.
  {
    Serial.println("Error."); // print error message.
  }
  http.end();          // After calling API end the HTTP client object.
}

String urlencode(String str)  // Function used for encoding the url
{
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        encodedString+=code2;
      }
      yield();
    }
    return encodedString;
}

const float velsonido = 0.0343;

void activaTriguer()
  {  
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW); 
  }
void AlarmaESP()
 {
  activaTriguer();
  long unsigned tiempo = pulseIn(pinEcho, HIGH);
  float distancia = tiempo*velsonido/2;
  Serial.println(distancia);
  delay(300);
  if (distancia <= 100)
     { 
     digitalWrite(pinLedAlarma, HIGH);
     message_to_whatsapp("ALERTA");
     digitalWrite(pinLedAlarma, LOW);
     }
 }
void setup()
 {
  Serial.begin(115200);
  // Intenta conectarse a la red Wifi:
  Serial.print("Conectando a la red wifi... ");
  Serial.println(ssid);
  //Seteo de la red Wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("Conectado a la red wifi!!!");
  Serial.print("Dirección ip: ");
  Serial.println(WiFi.localIP());//Imprimimos la direción ip local
  pinMode(pinLedOk,OUTPUT);
  digitalWrite(pinLedOk,HIGH);
  
  pinMode(pinLedAlarma, OUTPUT);
  pinMode(pinTrig, OUTPUT); 
  pinMode(pinEcho, INPUT); 
 }

void loop()
{
 AlarmaESP(); 
} 
