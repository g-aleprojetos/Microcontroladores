// --- Bibliotecas Auxiliares ---
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
/************************************************************************************/
// --- Configuração da rede e dispositivo ---
#ifndef STASSID
#define STASSID "g.aleprojetos"
#define STAPSK  "a248314b"
#define DISPOSITIVO "dispositivo 01"
#define SENHADISPOSITIVO "004545"
#endif

/************************************************************************************/
// --- Constantes Auxiliares ---

/************************************************************************************/
// --- Protótipo das Funções ---
void startOTA();

/************************************************************************************/
// --- Variáveis Globais ---
const char* ssid = STASSID;
const char* password = STAPSK;
/************************************************************************************/
void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(2000);
 //   ESP.restart();
  }
  // --- Configuração do dispositivo ---

  startOTA();

}

void loop() {
  ArduinoOTA.handle();
}

// --- Desenvolvimento das Funções ---
void startOTA(){
  ArduinoOTA.setHostname(DISPOSITIVO);                              // Nome do dispositivo
  ArduinoOTA.setPassword(SENHADISPOSITIVO);                         // Senha do dispositivo
  
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 }//end startOTA
