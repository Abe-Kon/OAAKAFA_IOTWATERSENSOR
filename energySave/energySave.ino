#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define USE_SERIAL Serial
#define uS_TO_S_FACTOR 1000000ULL
#define TIME_TO_SLEEP  4*60


void lcdprint(float distance__cm);
void empty_tank(float distance__cm);
void sleep_wake();
// void tank_system();

WiFiMulti wifiMulti;
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//Pins
int trigger_pin = 5;
int echo_pin   = 18;
int led_pin = 23;
int Relaypin= 4;
int distance_cm;

void setup() {
   USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

  wifiMulti.addAP("Ttbi", "yaakonadu1"); 
 // declare pins as output
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(Relaypin, OUTPUT);
  delay(1000);

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  lcd.init(); // initialize LCD
  lcd.setCursor(0,0);//Set cursor value
  lcd.print("Distance reading!");
  delay(1000);
  lcd.clear();
}

void loop() {
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
    empty_tank(distance_cm);
    delay(3000);

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
          
    }
  void sleep_wake();
}

// void tank_system(){

// }

void sleep_wake(){
      lcd.print("Sleeping...");
      //Serial.println("Going to sleep now");
      delay(1000);
      Serial.flush(); 
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

void empty_tank(float distance__cm){
  if(distance__cm<15.00) {
    digitalWrite(led_pin, HIGH);
    digitalWrite(Relaypin, LOW);
	
    if(distance__cm>=100.0){
    digitalWrite(led_pin, LOW);
    digitalWrite(Relaypin, HIGH);
    }
   
  }
  else{
    digitalWrite(led_pin,LOW);
    digitalWrite(Relaypin, HIGH);
  }
}