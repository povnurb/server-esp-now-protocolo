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
void ProcessRequest(AsyncWebSocketClient * client, String request);
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
    int id;         //identificador de esp que envia
    float temp;     //Temperatura de la sala
    float hum;      //humedad de la sala
    float readingId;  //numero de envio ya no ahora es señal RSSI
} struct_message;

struct_message incomingReadings; //es una instancia de la estructura del mensaje que se recibe

StaticJsonDocument<220> board; //verificar con mas capacidad

AsyncWebServer server(80);
//AsyncWebSocket ws("/ws"); //se instancia ws sobre el puerto ochenta con el /ws
AsyncEventSource events("/events");


// callback funcion que se ejecuta cuando un dato es recivido
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
    String jsonString;
    // Copies the sender mac address to a string
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  //todos estos valores los envia el transmisor
  board["id"] = incomingReadings.id;
  board["temperature"] = incomingReadings.temp;
  board["humidity"] = incomingReadings.hum;
  board["readingId"] = incomingReadings.readingId; //aqui esta llegando la señal wiFi
  // la siguiente linea es para int (enteros)
  //board["readingId"] = String(incomingReadings.readingId);
  //hay que serealizar para convertir el objeto en cadena
  serializeJson(board,jsonString);
  events.send(jsonString.c_str(), "new_readings", millis());
  
  Serial.printf("Board ID %u: %u bytes\n", incomingReadings.id, len);
  Serial.printf("t value: %4.2f \n", incomingReadings.temp);
  Serial.printf("h value: %4.2f \n", incomingReadings.hum);
  Serial.printf("readingID value: %4.2f \n", incomingReadings.readingId);
  // para imprimir enteros
  //Serial.printf("readingID value: %d \n", incomingReadings.readingId);
  Serial.println();
} 
/*
// -------------------------------------------------------------------
// manejor de Eventos del Websocket de la libreria
// -------------------------------------------------------------------
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){ 
	if(type == WS_EVT_CONNECT){
		Serial.printf("[ INFO ] ws[%s][%u] connect\n", server->url(), client->id());
		client->printf("{\"ClientID\": %u }", client->id());  //muestra el id del cliente
		client->ping();  //para mantener la conexion
	} else if(type == WS_EVT_DISCONNECT){
		//Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
	} else if(type == WS_EVT_ERROR){
		//Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
	} else if(type == WS_EVT_PONG){
		//Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");
	} else if(type == WS_EVT_DATA){  //cuando llega una data
		AwsFrameInfo * info = (AwsFrameInfo*)arg;
		String msg = "";
		if(info->final && info->index == 0 && info->len == len){
			if(info->opcode == WS_TEXT){
				for(size_t i=0; i < info->len; i++) {
					msg += (char) data[i];
				}
			} else {
				char buff[3];
				for(size_t i=0; i < info->len; i++) {
					sprintf(buff, "%02x ", (uint8_t) data[i]);
					msg += buff ;
				}
			}
			if(info->opcode == WS_TEXT)
			   ProcessRequest(client, msg);			
		} else {
			//message is comprised of multiple frames or the frame is split into multiple packets
			if(info->opcode == WS_TEXT){
				for(size_t i=0; i < len; i++) {
					msg += (char) data[i];
				}
			} else {
				char buff[3];
				for(size_t i=0; i < len; i++) {
					sprintf(buff, "%02x ", (uint8_t) data[i]);
					msg += buff ;
				}
			}
			Serial.printf("%s\n",msg.c_str());

			if((info->index + len) == info->len){
				if(info->final){
					if(info->message_opcode == WS_TEXT)
					   ProcessRequest(client, msg);
				}
			}
		}
	}
}

// -------------------------------------------------------------------
// Inicializar el Websocket
// -------------------------------------------------------------------
void InitWebSockets(){
	ws.onEvent(onWsEvent);
	server.addHandler(&ws);
    Serial.println("[INFO:funciones.hpp ] Servidor WebSocket iniciado");
}
// -------------------------------------------------------------------
// Manejador de ordenes enviada por Websocket
// -------------------------------------------------------------------
void ProcessRequest(AsyncWebSocketClient * client, String request){    
	String command = request;
    command.trim();
	
}
// -------------------------------------------------------------------
// Función enviar JSON por Websocket 
// -------------------------------------------------------------------
void WsMessage(String msg, String icon, String Type){
	if(strcmp(Type.c_str(), "info") == 0){
		String response;
		StaticJsonDocument<300> doc;
		doc["id"] = incomingReadings.id;;
		doc["temperature"] = incomingReadings.temp;;
		doc["humidity"] = incomingReadings.hum;;
        doc["readingId"] = String(incomingReadings.readingId);;
		serializeJson(doc, response);
		ws.textAll(response);
		Serial.println(response);
		Serial.flush(); 
	}
}
*/