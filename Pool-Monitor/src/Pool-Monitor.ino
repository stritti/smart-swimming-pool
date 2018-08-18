/**
   ESP8266 Monitor der Temperaturen für Pool:
   - ESP8266 Contoller
   - LiquidCrystal I2C 16*2 Anzeige

   Wird über MQTT-Messages von Poolsteuerung gesteuert.
*/
#include <Arduino.h>
#include <ESPBASE.h>

#include <ESP8266mDNS.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//WiFiServer TelnetServer(23);  // Optional in case you want to use telnet as Monitor
//WiFiClient Telnet;            // Optional in case you want to use telnet as Monitor

ESPBASE Esp;

WiFiClient wifiClient;

//MQTT settings
const char* MQTT_SERVER = "192.168.178.25";
String DEVICE_NAME = "ESP8266-POOL-MONITOR";
PubSubClient mqttClient(wifiClient);

LiquidCrystal_I2C lcd(0x27, 16, 2); //set the LCD address to 0x27 for a 16 chars and 2 line display


/**
    Connect MQTT Server
*/
void connectMQTT() {
  Serial.printf("Attempting MQTT connection to %s ...\n", MQTT_SERVER);
  // Attempt to connect
  if (mqttClient.connect(DEVICE_NAME.c_str())) {
    Serial.println(F("MQTT connected."));
    
    mqttClient.subscribe( "/sensor/pool/temperature");
    mqttClient.subscribe( "/sensor/solar/temperature");

  } else {
    Serial.printf("failed, rc=%s\n", mqttClient.state());
    // Print to know why the connection failed
    // See http://pubsubclient.knolleary.net/api.html#state for the failure code and its reason
    switch (mqttClient.state()) {
      case -4:
        Serial.println(F("MQTT_CONNECTION_TIMEOUT - the server didn't respond within the keepalive time"));
        break;
      case -3:
        Serial.println(F("MQTT_CONNECTION_LOST - the network connection was broken"));
        break;
      case -2:
        Serial.println(F("MQTT_CONNECT_FAILED - the network connection failed"));
        break;
      case -1:
        Serial.println(F("MQTT_DISCONNECTED - the client is disconnected cleanly"));
        break;
    }
  }
}

/**
     on MQTT message
*/
void onMqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.println("] ");

  String command = String((char*)topic);

  Serial.println(command);

  Serial.println((char*) payload);
  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.parseObject((char*) payload);

  const char* sensor = root["sensor"];
  Serial.print("sensor: ");
  Serial.println(sensor);

  const char* type = root["type"];
  Serial.print("type: ");
  Serial.println(type);

  const char* value = root["value"];
  Serial.print("value: ");
  Serial.println(value);

  if (strcmp("temperature", type) == 0) {
    // Turn off the backlight.
    lcd.noBacklight();

    if (strcmp("pool", sensor) == 0 ) {
      lcd.setCursor(8, 0);
    } else if (strcmp("solar", sensor) == 0) {
      lcd.setCursor(8, 1);
    } else {
      Serial.println("unhandled sensor");
    }

    lcd.print(value);
    lcd.print(" ");
    lcd.print(char(223)); //Grad-Zeichen
    lcd.print("C  ");

    // Turn on the backlight.
    lcd.backlight();
  } else {
    Serial.println("unhandled type");
  }
}

void setup() {
  
  Serial.begin(115200);
  Esp.initialize();

  WiFi.hostname(config.DeviceName.c_str());     //not working here
  
  if (MDNS.begin(config.DeviceName.c_str())) { // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
    // Add service to MDNS-SD
    MDNS.addService("arduino", "tcp", 8266);
    MDNS.addService("http", "tcp", 80);
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

//  TelnetServer.begin();            // Optional in case you want to use telnet as Monitor
//  TelnetServer.setNoDelay(true);   // Optional in case you want to use telnet as Monitor

  // put your setup code here, to run once:

  Serial.println(F("-------------------------------------"));
  Serial.println(F(" Temperature Monitor                 "));
  Serial.println(F("-------------------------------------"));

  mqttClient.setServer(MQTT_SERVER, 1883);
  mqttClient.setCallback(onMqttCallback);

  // The begin call takes the width and height. This
  // Should match the number provided to the constructor.
  lcd.begin(16, 2);
  lcd.init();

  // Move the cursor characters to the right and
  // zero characters down (line 1).
  lcd.setCursor(1, 0);
  lcd.print("Pool:");

  lcd.setCursor(1, 1);
  lcd.print("Solar:");

  // Turn on the backlight.
  lcd.backlight();

  Serial.println(F("Device started"));
}


void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(millis());

  // OTA request handling
  ArduinoOTA.handle();

  //  WebServer requests handling
  server.handleClient();

  //  feed de DOG :)
  customWatchdog = millis();

  // activate telnet service to act as output console

//  if (TelnetServer.hasClient()) {           // Optional in case you want to use telnet as Monitor
//    if (!Telnet || !Telnet.connected()) {
//      if (Telnet) Telnet.stop();
//      Telnet = TelnetServer.available();
//    } else {
//      TelnetServer.available().stop();
//    }
//  }

  //**** Normal Skecth code here ...
  if( Esp.WIFI_connected) {
    if (!mqttClient.connected()) {
      connectMQTT();

    }
    mqttClient.loop();
  }

}
