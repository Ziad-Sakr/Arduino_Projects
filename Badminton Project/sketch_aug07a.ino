#include "MPU9250.h"
MPU9250 mpu;

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"
#define LED D0

const int flexPin_1 = D3;
const int flexPin_2 = D4;
const int PushPin   = D5;
const int AnalogPin = A0;
const int B_led     = D6;
const int R_led     = D7;
const int G_led     = D8;

int a = 0;

const char* ap_ssid = "ESP-AP"; //Access Point SSID
const char* ap_password = "12345678"; //Access Point Password
uint8_t max_connections = 8; //Maximum Connection Limit for AP
int current_stations = 0, new_stations = 0;
const float VCC = 3.3;      // voltage at Ardunio 5V line
const float R_DIV = 51000.0;  // resistor used to create a voltage divider
const float flatResistance = 25000.0; // resistance when flat
const float bendResistance = 100000.0;

ESP8266WebServer server(80);

float flex_1()
{
  digitalWrite(flexPin_1, HIGH);
  digitalWrite(flexPin_2, LOW);
  digitalWrite(PushPin, LOW);
  int ADCflex = analogRead(AnalogPin);
  float Vflex = ADCflex * VCC / 1023.0;
  float Rflex = R_DIV * (VCC / Vflex - 1.0);
  float angle = map(Rflex, flatResistance, bendResistance, 0, 90.0);
  String value1 = String(angle - 110);
  //server.send(200, "text/plane", value1);
  return (angle - 110);
}

float flex_2()
{
  digitalWrite(flexPin_1, LOW);
  digitalWrite(flexPin_2, HIGH);
  digitalWrite(PushPin, LOW);
  int ADCflex = analogRead(AnalogPin);
  float Vflex = ADCflex * VCC / 1023.0;
  float Rflex = R_DIV * (VCC / Vflex - 1.0);
  float angle = map(Rflex, flatResistance, bendResistance, 0, 90.0);
  String value2 = String(angle - 40);
  //server.send(200, "text/plane", value2);
  return (angle - 40);
}

float Push()
{
  digitalWrite(flexPin_1, LOW);
  digitalWrite(flexPin_2, LOW);
  digitalWrite(PushPin, HIGH);
  int ADCflex = analogRead(AnalogPin);
  float Vflex = ADCflex * VCC / 1023.0;
  float Rflex = R_DIV * (VCC / Vflex - 1.0);
  float angle = map(Rflex, flatResistance, bendResistance, 0, 90.0);
  String value3 = String(angle + 23);
  //server.send(200, "text/plane", value3);
  return (angle + 23);
}


void print_roll() {
  int value_1 = mpu.getRoll();
  //Serial.print(value_1);
  //Serial.print(" , ");
  String value1 = String(value_1);
  server.send(200, "text/plane", value1);
}

void print_pitch()
{
  int value_2 = mpu.getPitch();
  //Serial.print(value_2);
  //Serial.print(" , ");
  String value2 = String(value_2);
  server.send(200, "text/plane", value2);

}

void print_yaw()
{
  int value_3 = mpu.getYaw();
  //Serial.println(value_3);
  String value3 = String(value_3);
  server.send(200, "text/plane", value3);
}

void handleRoot()
{
  String s = webpage;
  server.send(200, "text/html", s);
}

void sensor() {
  String state = "0";
  if (a == 1)
  {
    state = "1";
    Serial.println(a);
  }
  else
  {
    state = "0";
    Serial.println(a);
  }
  server.send(200, "text/plane", state);
}

/////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  pinMode(flexPin_1, OUTPUT);
  pinMode(flexPin_2, OUTPUT);
  pinMode(PushPin,   OUTPUT);
  pinMode(AnalogPin, INPUT );
  pinMode(R_led,     OUTPUT);
  pinMode(G_led,     OUTPUT);
  pinMode(B_led,     OUTPUT);
  //////////////////////////////////////////
  /*
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network.
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    //////////////////////////////////////////
  */
  if (WiFi.softAP(ap_ssid, ap_password, 1, false, max_connections) == true)
  {
    Serial.print("Access Point is Created with SSID: ");
    Serial.println(ap_ssid);
    Serial.print("Max Connections Allowed: ");
    Serial.println(max_connections);
    Serial.print("Access Point IP: ");
    Serial.println(WiFi.softAPIP());
  }
  else
  {
    Serial.println("Unable to Create Access Point");
  }
  Serial.println(".");
  pinMode(LED, OUTPUT);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Wire.begin();
  if (!mpu.setup(0x68)) {  // change to your own address
    while (1) {
      Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
    }
  }
  mpu.verbose(true);
  mpu.calibrateAccelGyro();
  mpu.calibrateMag();
  mpu.verbose(false);


  server.on("/", handleRoot);
  server.on("/adcread1", print_roll);
  server.on("/adcread2", print_pitch);
  server.on("/adcread3", print_yaw);
  server.on("/adcread4", sensor);
  server.begin();
}
void loop() {
  float f_1 = flex_1();
  float f_2 = flex_2();
  float P  = Push()  ;

  if (mpu.update()) {
    static uint32_t prev_ms = millis();
    if (millis() > prev_ms + 25) {
      print_roll();
      print_pitch();
      print_yaw();
      if (f_1 > 15 && f_2 > 15 && P <= 40 && P >= -40)
      {
        digitalWrite(G_led, LOW);
        digitalWrite(R_led, LOW);
        digitalWrite(B_led, HIGH);
        a=1;
      }
      else
      {
        digitalWrite(G_led, LOW);
        digitalWrite(R_led, HIGH);
        digitalWrite(B_led, LOW);
        a=0;
      }
      prev_ms = millis();
    }
  }

  server.handleClient();
}
