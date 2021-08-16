#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "config.h"


ESP8266WebServer server(80);
char TAG_WIFI[64];
char TAG_AP[64];
void initWIFI(char* TAG_WIFI, char* TAG_AP);
void aboutWIFI(char* TAG_WIFI, char* TAG_AP);
void homePage();
void handleNotFound();
void login();
void restrito();

//void led_ON();
//void led_OFF();

int temperatura = 0;
String humildade = "";
String dia = "";

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  
  pinMode(D4, OUTPUT);
  
  initWIFI(TAG_WIFI, TAG_AP);
  server.on("/", HTTP_GET,restrito);
  server.on("/login", HTTP_POST,login);
  server.onNotFound(handleNotFound);
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  digitalWrite(D4, HIGH);
  delay(1000);
  digitalWrite(D4, LOW);
  delay(1000);
  aboutWIFI(TAG_WIFI,TAG_AP);
  
}

void homepage(){
  dia = "No";
  humildade = "30%";
  temperatura = 24;
  char body[1088];
  sprintf(body, "<!DOCTYPE html><html lang='pt-br'><head><meta charset='utf-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Esp8266 WebServer</title><style>*{box-sizing: border-box;margin:0;padding:0;}html{max-width:400px;margin:0px auto;}body{background:skyblue;color:black;font-family: Arial;}.App{background: #ffffff;border:1px solid black;border-radius: 5px;padding:10px;margin:10px;}.App-title{text-align:left;padding-left:10px;padding:10px;}#action{background: #000000;border-radius:5px;padding:5px;color:#fff;text-decoration: none;position: relative;font-weight: 500;margin-left:10px;}.dt{color: black;margin-bottom:10px;padding:10px;}.temp{border:1px solid red;border-radius:5px;padding:10px;}</style></head><body><div class='App'><h1 class='App-title'> IOT - ESP8266</h1><br/><hr><br><div class='dt'><b><p class='temp'>Temperatura %d °C</p></b><br><b><p class='temp'>Humildade %s</p></b><br><b><p class='temp'>Dia %s</p></b><br><br></div></div></body></html>", temperatura, humildade, dia);
  server.send(200, "text/html", body);
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not Found");
}

void login(){
  if(!server.hasArg("username") || !server.hasArg("password") || server.hasArg("username") == NULL || server.hasArg("password") == NULL){
    server.send(400, "text/plain", "400: Invalid request");
    return;
  }

  if(server.arg("username") == "mvictor" && server.arg("password") == "susej_65564747" ){
    homepage();
  }
  else{
    server.send(401, "text/plain", "401: Unauthorized");
  }
}

void restrito(){
  server.send(200, "text/html", "<!DOCTYPE html><!DOCTYPE html><html><head><meta charset='utf-8'><meta name='viewport' content='width=device-width,initial-scale=1.0'><title>Login</title><style type='text/css'>*{box-sizing: border-box;margin:0;padding:0;}html{max-width:400px;margin:0px auto;}body{background:skyblue;color:black;font-family: Arial;}.App{background: #ffffff;border:1px solid black;border-radius: 5px;padding:10px;margin:10px;}form{width: 100%;}input{width: 100%;padding:10px;margin-top: 10px;text-align: center;}.title-App{text-align: center;}</style></head><body><div class='App'><h3 class='title-App'>Acesso Restrito</h3><form action='login' method='POST'><input type='text' name='username' placeholder='username'><br><input type='password' name='password' placeholder='password'><br><input type='submit' value='Login'><br></form></div></body></html>");
}

void initWIFI(char* TAG_WIFI, char* TAG_AP){
  
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(AP_SSID, AP_PASS, AP_CHANNEL, AP_HIDDEN, AP_MAX_CONN);
  
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  sprintf(TAG_WIFI, "WIFI %s", WIFI_SSID);
  Serial.print("Conectado ao WIFI...");
  Serial.println(TAG_WIFI);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void aboutWIFI(char* TAG_WIFI, char* TAG_AP){
  sprintf(TAG_AP, "ACESS POINT %s", AP_SSID);
  
  Serial.println();
  Serial.println("Conectado!");
  Serial.print("IP Address ");
  Serial.print(TAG_WIFI);
  Serial.print(": ");
  Serial.println(WiFi.localIP());
  Serial.print("IP Address ");
  Serial.print(TAG_AP);
  Serial.print(": ");
  Serial.print(WiFi.softAPIP());
  Serial.println();
  delay(1000);
}


/*
void led_ON(){
  digitalWrite(D4, HIGH);
}
void led_OFF(){
  digitalWrite(D4, LOW);
}*/
