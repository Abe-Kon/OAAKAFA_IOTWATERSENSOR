#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define uS_TO_S_FACTOR 1000000ULL
#define TIME_TO_SLEEP  4*60


void lcdprint(float distance__cm);
void empty_tank(float distance__cm);

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


int trigger_pin = 5;
int echo_pin   = 18;
int led_pin = 23;

// Replace with your network credentials
const char* ssid = "Ttbi";
const char* password = "yaakonadu1";

WebServer server(80);

String page = "";
int distance_cm;

void setup() {
  Serial.begin(115200);
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  delay(1000);

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  //LCD INITIALIZATION
    // initialize LCD
  lcd.init();

  //Set cursor value
  lcd.setCursor(0,0);
  lcd.print("Distance reading!");
  delay(1000);
  lcd.clear();
}

void loop() {
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
  Serial.println("Going to sleep now");
  Serial.flush(); 
  esp_deep_sleep_start();
}

void lcdprint(float distance__cm){
  //clear lcd
  lcd.clear(); 
   // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Water Level:");
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print(String(distance__cm));
  lcd.print("cm");
}

void empty_tank(float distance__cm){
  if(distance__cm<15.00) {
    digitalWrite(led_pin, HIGH);
    if(distance__cm>=100.0)
    digitalWrite(led_pin, LOW);
  }
  else{
    digitalWrite(led_pin,LOW);
  }
}