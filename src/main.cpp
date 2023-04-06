/**
 * este es complemento de web_malla_sensores
 * hay que agregar si es posible un DNS
*/
#include <Arduino.h>
#include "includes.hpp" //todas las librerias y archivos
#include "globales.hpp" //todas las variables globales
// recuerda que hay que compartir la direccion MAC de este dispositivo
//------------------------------------------------------------------------
// Zona OLED
// -----------------------------------------------------------------------
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  Serial.begin(115200); Serial.println();   
  // Set device as a Wi-Fi Station
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Setting as a Wi-Fi Station..");
  }
  Serial.print("Station IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Wi-Fi Channel: ");
  Serial.println(WiFi.channel());
  //inicializamos el OLED
  Serial.println("Inicializamos el display OLED");
  if(!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)){ // Dirección 0x3C
    Serial.println("OLED no encontrado");
    while(true);
  }
  OLED.clearDisplay();

  // Init ESP-NOW     
  setupEspnow(); //espnow.hpp
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  
  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 2000);
  });
  
  server.addHandler(&events);
  server.begin();
  
  
}
//---------------------------------------------------------------
// OLED
//---------------------------------------------------------------
void mostrarOled(){
   
    OLED.clearDisplay();
    OLED.setTextSize(1);
    OLED.setTextColor(WHITE);
    OLED.setCursor(0,0);
    OLED.println("MAC: ");
    OLED.println(obtenerWifiMac());
    OLED.println("Nodos conectados: ");
    OLED.display();
    
}

void loop() {
  
  int lastEventTime = millis();
  int EVENT_INTERVAL_MS = 2000;
  if ((millis() - lastEventTime) > EVENT_INTERVAL_MS) {
    
    //events.send("ping",NULL,millis()); //solo envia un ping para mostrar que sigue conectado
    lastEventTime = millis();
    
  }
  if ((millis() - lastTime3) > 1000){
    lastTime3 = millis();
    mostrarOled();
  }
}