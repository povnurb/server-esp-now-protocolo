/**
 * https://randomnerdtutorials.com/esp32-esp-now-wi-fi-web-server/
*/
#include <Arduino.h>

void setupEspnow(){//en main.cpp     
  if (!esp_now_init()) {
    //si el resultado es un 0 la conexion ESP-NOW esta ok
    Serial.println("[INFO: espnow.hpp ] Conexion ESP-NOW inicializada.");
  }else{
    Serial.println("[INFO: espnow.hpp ] Conexion ESP-NOW no inicializada.");
    //podriamos forzarla
    ESP.restart();
  }
  Serial.print("[INFO: espnow.hpp ] ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());//formato String
  
}
