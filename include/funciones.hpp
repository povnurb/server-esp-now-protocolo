#include <Arduino.h>
#include "ESPAsyncWebServer.h"  //servidor en el esp32
#ifdef __cplusplus
extern "C"
{
#endif
    uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();
// -------------------------------------------------------------------
// Declaración de funciones de request
// -------------------------------------------------------------------
//funciones
/*
MAC de comunicación ESP-NOW
Cada procesador ESP disponen de dos direcciones MAC, para posibilitar las conexiones WiFi 
en los modos Access Point y Station. Las direcciones MAC son respectivamente AP MAC y STA MAC.
*/
// AP MAC
String miApMac(){
    return String(WiFi.softAPmacAddress());
}
//wifi MAC
String obtenerWifiMac(){
    return String(WiFi.macAddress());
}
typedef struct struct_message {
    String modoSend; //modo recibido
    int id;         //identificador de esp que envia
    String nameNodo; //nombre del nodo
    float temp;     //Temperatura de la sala
    float hum;      //humedad de la sala
    int readingId;  //numero de envio ya no ahora es señal RSSI
    float min;
    float max;
    //------------------------------------------------------------
    String alr1,alr2,alr3,alr4,alr5,alr6,alr7,alr8;
    bool  va1,va2,va3,va4,va5,va6,va7,va8;
    //------------------------------------------------------------
} struct_message;

struct_message incomingReadings; //es una instancia de la estructura del mensaje que se recibe

StaticJsonDocument<500> board; //verificar con mas capacidad

AsyncWebServer server(80);
AsyncEventSource events("/events");


// callback funcion que se ejecuta cuando un dato es recivido
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
    String jsonString;
    // Copies the sender mac address to a string
  char macStr[18];
  Serial.print("[INFO: funciones.hpp] Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  //todos estos valores los envia el transmisor
  board["modoSend"] = String(incomingReadings.modoSend);
  board["id"] = incomingReadings.id;
  board["nameNodo"] = String(incomingReadings.nameNodo);
  board["temperature"] = incomingReadings.temp;
  board["humidity"] = incomingReadings.hum;
  board["readingId"] = incomingReadings.readingId; //aqui esta llegando la señal wiFi
  board["min"] = incomingReadings.min; //temperatura min
  board["max"] = incomingReadings.max; //temperatura maxima
  //--------------------------------------------------------------
  board["alr1"] = incomingReadings.alr1; 
  board["alr2"] = incomingReadings.alr2;
  board["alr3"] = incomingReadings.alr3;
  board["alr4"] = incomingReadings.alr4;
  board["alr5"] = incomingReadings.alr5;
  board["alr6"] = incomingReadings.alr6;
  board["alr7"] = incomingReadings.alr7;
  board["alr8"] = incomingReadings.alr8;
  board["va1"] = incomingReadings.va1;
  board["va2"] = incomingReadings.va2;
  board["va3"] = incomingReadings.va3;
  board["va4"] = incomingReadings.va4;
  board["va5"] = incomingReadings.va5;
  board["va6"] = incomingReadings.va6;
  board["va7"] = incomingReadings.va7;
  board["va8"] = incomingReadings.va8;
  //--------------------------------------------------------------
  board["tmp"] = 0;
  // la siguiente linea es para int (enteros)
  //board["readingId"] = String(incomingReadings.readingId);
  //hay que serealizar para convertir el objeto en cadena
  Serial.println(incomingReadings.nameNodo);
  Serial.println(incomingReadings.modoSend);
  serializeJson(board,jsonString);
  events.send(jsonString.c_str(), "new_readings", millis());
  
  Serial.printf("Board ID %u: %u bytes\n", incomingReadings.id, len);
  Serial.println("Nombre del nodo: "+ incomingReadings.nameNodo);
  Serial.printf("t value: %4.2f \n", incomingReadings.temp);
  Serial.printf("h value: %4.2f \n", incomingReadings.hum);
  Serial.printf("readingID value: %4.2f \n", incomingReadings.readingId);
  Serial.printf("min value: %4.2f \n", incomingReadings.min);
  Serial.printf("max value: %4.2f \n", incomingReadings.max);
  // para imprimir enteros
  //Serial.printf("readingID value: %d \n", incomingReadings.readingId);
  Serial.println();
  
} 

