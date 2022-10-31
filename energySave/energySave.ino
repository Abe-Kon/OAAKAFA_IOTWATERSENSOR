#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>
#include <Wire.h> 
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>

#define USE_SERIAL Serial
#define uS_TO_S_FACTOR 1000000ULL
#define TIME_TO_SLEEP  4*60
#define tankheight 100 //cm
#include "html.h"


void lcdprint(float distance__cm);
void check_tank(float distance__cm);
void sleep_wake();
void handleNotFound();
void handleRoot();
void autoOP();
void manStartOP();
void manStopOP();
// void tank_system();

WiFiMulti wifiMulti;
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//Pins
int trigger_pin = 5;
int echo_pin   = 18;
int led_pin = 23;
int Relaypin= 4;
int distance_cm;
int State = 0;

WebServer server(80);

void setup() {
  // declare pins as output
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(Relaypin, OUTPUT);
  delay(1000);

    USE_SERIAL.begin(115200);

    USE_SERIAL.println("-----------");

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

  wifiMulti.addAP("Ttbi", "yaakonadu1"); 

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
 

  server.on("/", handleRoot);
  server.on("/Automatic", autoOP);
  server.on("/Start", manStartOP);
  server.on("/Stop", manStopOP);

  server.onNotFound(handleNotFound);
  //server.on("/client", RQ);

  server.begin();
  Serial.println("Http server started");


  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  digitalWrite(Relaypin, HIGH);
  lcd.init(); // initialize LCD
  lcd.backlight();
  lcd.setCursor(0,0);//Set cursor value
  lcd.print("Distance reading!");
  delay(500);
  lcd.clear();
}
}

void loop() {
  server.handleClient();
  delay(2);
 // wait for WiFi connection
  if((wifiMulti.run() == WL_CONNECTED)) {
    digitalWrite(trigger_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_pin, LOW);
    
    long duration = pulseIn(echo_pin, HIGH);
    distance_cm = (duration / 2) / 29.09;

    lcdprint(distance_cm);

    HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        http.begin("http://192.168.136.233/iot/midsem_insert.php?owner_id=1&place=Abena&level="+String(distance_cm)); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been sent and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
        check_tank(distance_cm);
    }


}

// void tank_system(){

// }

void sleep_wake(){
      Serial.println("Going to sleep now");
      Serial.flush(); 
      delay(500);
      lcd.clear();
      lcd.noBacklight();
      esp_deep_sleep_start();

}
void lcdprint(float distance__cm){
  lcd.backlight(); //turn on backlight
  lcd.clear(); //clear lcd
  lcd.setCursor(0, 0);  // set cursor to first column, first row
  lcd.print("Water Level:"); // print message
  lcd.setCursor(0,1); // set cursor to first column, second row
  lcd.print(String(distance__cm));
  lcd.print("cm");
}

void check_tank(float distance__cm){

  if(State == 0){
    if (distance__cm<15.00) {
    digitalWrite(led_pin, HIGH);
    digitalWrite(Relaypin, LOW);

    if(distance__cm>=100.0){
    digitalWrite(led_pin, LOW);
    digitalWrite(Relaypin, HIGH);
    sleep_wake();  
    }
    }
   }

  else if (State == 1){
    digitalWrite(led_pin,HIGH);
    digitalWrite(Relaypin, LOW); 
  }

  else if (State == 2){
    digitalWrite(led_pin,LOW);
    digitalWrite(Relaypin, HIGH);
    //sleep_wake();  
  }

}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  }

 

  void handleRoot(){
    
    server.send(200, "text/html",page);
    }

  void autoOP (){
    State = 0;
  }

  void manStartOP (){
    State = 1;
  }

  void manStopOP(){
    State = 2;
  }

//   void LEDRfunct()
// { if (manualState == HIGH){
//   LEDR= !LEDR;
//   digitalWrite(LED_PIN, LEDR);
//   //counter++;
//   String str = "OFF";    //very little returned
//   if(LEDR == HIGH ) str = "ON";
//   server.send(200, "text/plain", str);
//   Serial.println("red");
// }
// }

// void manualfunct(){
//  if(manualState == HIGH){
// // manualState = !manualState
//    manualState = LOW;
// }
//  else{
//   manualState = HIGH;
//  }
//  }