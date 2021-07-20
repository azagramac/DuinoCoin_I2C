/*
  DuinoCoin_ESP_Master.ino
  created 20/07/2021
  Update: AzagraMac
*/

#if ESP8266
#include <ESP8266WiFi.h> // Include WiFi library
#include <ESP8266mDNS.h> // OTA libraries
#include <WiFiUdp.h>
#endif

#if ESP32
#include <WiFi.h>
#endif

#include <ArduinoOTA.h>
#include <StreamString.h>

#define BLINK_SHARE_FOUND    1
#define BLINK_SETUP_COMPLETE 2
#define BLINK_CLIENT_CONNECT 3
#define BLINK_RESET_DEVICE   5

#if ESP8266
#define LED_BUILTIN 2
#define MINER "AVR I2C Miner v2.5.2"
#define JOB "AVR"
#endif

#if ESP32
#define LED_BUILTIN 2
#define MINER "AVR I2C Miner v2.5.2"
#define JOB "AVR"
#endif

const char* ssid          = "YOUR_SSID_WIFI";              // Change this to your WiFi SSID
const char* password      = "YOUR_PASSWORD_WIFI";          // Change this to your WiFi password
    //Set Static IP
    IPAddress local_IP(192, 168, 1, 3);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    IPAddress primaryDNS(1, 1, 1, 1);
    IPAddress secondaryDNS(1, 0, 0, 1);

const char* ducouser      = "YOUR_USERNAME_DUINOCOIN";    // Change this to your Duino-Coin username
const char* rigIdentifier = "ESP8266-I2C-0";              // Change this if you want a custom miner name


void handleSystemEvents(void) {
  ArduinoOTA.handle();
  yield();
}

void SetupWifi() {
  if(!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
        Serial.println(F("STA Failed to configure"));
    }
  Serial.println("Connecting to: " + String(ssid));
  WiFi.mode(WIFI_STA); // Setup ESP in client mode

  if (strcmp(ssid, "") == 0)
    WiFi.begin();
  else
    WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }

  Serial.println(F("\nConnected to WiFi!"));
  Serial.println("Local IP address: " + WiFi.localIP().toString());
}

void SetupOTA() {
  ArduinoOTA.onStart([]() { // Prepare OTA stuff
    Serial.println(F("Start"));
  });
  ArduinoOTA.onEnd([]() {
    Serial.println(F("\nEnd"));
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
        Serial.println(F(" Auth Failed"));
    else if (error == OTA_BEGIN_ERROR)
        Serial.println(F(" Begin Failed"));
    else if (error == OTA_CONNECT_ERROR)
        Serial.println(F(" Connect Failed"));
    else if (error == OTA_RECEIVE_ERROR)
        Serial.println(F(" Receive Failed"));
    else if (error == OTA_END_ERROR)
        Serial.println(F(" End Failed"));
  });

#if ESP8266
  char hostname[32];
  sprintf(hostname, "ESP8266-I2C-0-%06x", ESP.getChipId());
  ArduinoOTA.setHostname(hostname);
#endif

  ArduinoOTA.begin();
}

void blink(uint8_t count, uint8_t pin = LED_BUILTIN) {
  uint8_t state = HIGH;
  for (int x = 0; x < (count << 1); ++x) {
    digitalWrite(pin, state ^= HIGH);
    delay(50);
  }
}

void RestartESP(String msg) {
  Serial.println(msg);
  Serial.println(F("Resetting ESP..."));
  blink(BLINK_RESET_DEVICE);
  #if ESP8266
    ESP.reset();
  #endif
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.print(F("\nDuino-Coin"));
  Serial.println(F(MINER));

  wire_setup();

  SetupWifi();
  SetupOTA();

  blink(BLINK_SETUP_COMPLETE);
}

void loop() {
  ArduinoOTA.handle();
  clients_loop();
  if (runEvery(5000))
  {
    Serial.print(F("[∙∙∙∙∙]"));
    Serial.println(" FreeRam: " + String(ESP.getFreeHeap()) + " " + clients_string());
  }
}

boolean runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}
