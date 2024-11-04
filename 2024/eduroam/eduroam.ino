#include <WiFi.h>
#include <esp_eap_client.h>
#include <ESPping.h>  
#include "SetupWifi.h"

char* remoteHost = "www.google.com";

void setup() {
  Serial.begin(115200);

  // Connect to WPA2 Enterprise network
  WiFi.disconnect(true);
  delay(1000);

  WiFi.mode(WIFI_STA);
  esp_eap_client_set_identity((uint8_t*)username, strlen(username));
  esp_eap_client_set_username((uint8_t*)username, strlen(username));
  esp_eap_client_set_password((uint8_t*)password, strlen(password));
  esp_wifi_sta_enterprise_enable();

  WiFi.begin(ssid);
  
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to eduroam!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
  Serial.println("\nPing em " + String(remoteHost) + "...");

  //Ping no remoteHost
  if (Ping.ping(remoteHost, 3)) {      //Parâmetros: (remoteHost, quantidade_pings (default=5))
    Serial.print(Ping.averageTime());  //Retorna o tempo médio dos pings
    Serial.println(" ms");
  } else {
    Serial.println("Erro.");
  }

  delay(3000);
}
