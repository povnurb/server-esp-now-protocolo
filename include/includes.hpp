// en este archivo estaran todas las librerias y archivos a inclurir
#include <ArduinoJson.h>        //Manejador de archivos JSON
#include <SPIFFS.h>             //Manejador de archivos
#include <WiFi.h>
#include <esp_now.h>
/*Librerias agregadas para nuevas funcionalidades (LALO)*/
#include <Adafruit_Sensor.h>    //by Adafruit
#include <DHT.h>                //by Adafruit
#include <Adafruit_I2CDevice.h> //se pondran al final para ver si no causan conflicto
#include <Adafruit_SSD1306.h>   //se pondran al final para ver si no causan conflicto
#include "funciones.hpp"
#include "espnow.hpp"           //aqui adentro esta la biblioteca ESP NOW
#include "server.hpp"