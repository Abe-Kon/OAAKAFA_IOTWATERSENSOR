#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

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

  // WiFi.begin(ssid, password);
  // Serial.println("");
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println("");
  // Serial.print("IP address: ");
  // Serial.println(WiFi.localIP());

  // server.on("/", []() {
  //   page = "<head><meta http-equiv=\"refresh\" content=\"3\"></head><center><h1>Ultasonic Water Level Monitor</h1><h3>Current water level:</h3> <h4>" + String(distance_cm) + "</h4></center>";
  //   server.send(200, "text/html", page);
  // });
  // server.begin();
  // Serial.println("Web server started!");

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
  //Serial.println(distance_cm);
  lcdprint(distance_cm);
  empty_tank(distance_cm);

  // server.handleClient();
  delay(3000);
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