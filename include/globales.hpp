// Variables globales del ESP32
// Remplazar con las credenciales de la red (STATION)
const char* ssid = "INFINITUM59W1_2.4"; // "INFINITUM37032" //INFINITUMD378 //INFINITUM59W1_2.4 //INFINITUMF69D
const char* password = "unJvpTX5Vp"; // "comcoatza123"    // Pm2Kj1Jg6j //unJvpTX5Vp       // 89r3X2Z7nJ
// ---------------------------------------------------
// Definiciones
// ---------------------------------------------------
#define WIFILED 12                                      //GPIO12 LED WIFI
#define MQTTLED 13                                      //GPIO13 LED MQTT
#define DHTPIN 2                                        // pin DHT  
#define BOTON2 34                                       // Botón de interrupción de alarma
#define SCREEN_WIDTH 128                                // Ancho   128 
#define SCREEN_HEIGHT 64                                // Alto     32 0 64
// ---------------------------------------------------
// Zona WEB de configuracion Dispositivo
// ---------------------------------------------------
char    device_old_user[15];        //Usuario para acceso al servidor Web
char    device_old_password[15];    //Contraseña del usuario servidor Web
uint8_t ip[4];                      //convierte de string a IP Variable función convertir string a IP
// ---------------------------------------------------
// Zona configuración WIFI modo Cliente
// ---------------------------------------------------
int wifi_mode = WIFI_AP_STA; 
char    device_config_serial[30];   //Numero de serie de cada Archivo de configuración unico

boolean wifi_ip_static;             //Uso de IP Estática DHCP
char    wifi_ssid[30];              //Nombre de la red WiFi
char    wifi_password[30];          //Contraseña de la Red WiFi
char    wifi_ipv4[15];              //Dir IPv4 Estático
char    wifi_gateway[15];           //Dir IPv4 Gateway
char    wifi_subnet[15];            //Dir Ipv4 Subred
char    wifi_dns_primary[15];       //Dir IPv4 DNS primario
char    wifi_dns_secondary[15];     //Dir IPv4 DNS secundario

// ---------------------------------------------------
// Zona configuración WIFI modo AP
// ---------------------------------------------------
boolean ap_mode;                    //Uso de Modo AP
char    ap_ssid[31];                //Nombre del SSID AP
char    ap_password[63];            //Contraseña del AP
int     ap_chanel;                  //Canal AP
int     ap_visibility;              //Es visible o no el AP (0 -  visible 1 - Oculto)
int     ap_connect;                 //Número de conexiones en el AP máx 8 conexiones
// ---------------------------------------------------
// Zona configuración MQTT
// ---------------------------------------------------
boolean mqtt_cloud_enable;          //Habilitar MQTT Broker
char    mqtt_cloud_id[30];          //Cliente ID MQTT Broker
char    mqtt_user[30];              //Usuario MQTT broker
char    mqtt_password[39];          //Contraseña del MQTT Broker
char    mqtt_server[39];            //Servidor del MQTT Broker
int     mqtt_port;                  //Puerto servidor MQTT Broker
boolean mqtt_retain;                //Habilitar mensajes retenidos
int     mqtt_qos;                   //Calidad del servicio
boolean mqtt_time_send;             //Habilitar envio de datos
int     mqtt_time_interval;         //Tiempo de envio por MQTT en segundos
boolean mqtt_status_send;           //Habilitar envio de estados

//-----------------------------------------------------------------
// Zona Temperaturas
//-----------------------------------------------------------------
float TCPU, hum, tempC;                      // Temperatura del CPU en °C


//-----------------------------------------------------------------
// Zona ALARMAS
//-----------------------------------------------------------------
bool normalizar=true;                               // Normalizar alarmas

//-----------------------------------------------------------------
// Zona tiempos
//-----------------------------------------------------------------

long lastTime1 = 0;         // aun sin usar Variable para tiempo de envio por WS
long lastTime2 = 0;         // a un sin usar variable para determinar si llego una señal
long lastTime3 = 0;         // para mostrar el display
long lastTime4 = 0;         // Tiempo de activacion de la alarmas ya que podria ser falsa
int mSerial = 5;      //tiempo en segundos que dura en volver a tranmitir
//-----------------------------------------------------------------
// Zona variables a enviar por esp now
//-----------------------------------------------------------------
int chanel; //canal wifi
//estructura del mensaje del esp now aun por agregar mas cosas

