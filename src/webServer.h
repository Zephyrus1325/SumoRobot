#pragma once
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <controlPage.h>
#include <webSocketHandler.h>
#include <ArduinoJson.h>
#include "defines.h"

AsyncWebServer server(80); // Declara o servidor web na porta 80

// O que retornar em caso de não encontrar o servidor
void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void InitializeServer(){
    WiFi.setSleep(false); // Desativar modo de economia de energia com o Wifi (adeus latencia!)
    WiFi.setTxPower(WIFI_POWER_19_5dBm);
    Serial.println();
    Serial.print("IP Address: ");
    #ifdef PROGRAMMING
        WiFi.mode(WIFI_STA);    // Inicia o ESP como um STATION (cliente de uma rede)
        WiFi.begin(ssid, password); // Inicia o WIFI com as credenciais de rede
        
        if (WiFi.waitForConnectResult() != WL_CONNECTED) {
            Serial.println("WiFi Failed!");
        return;
        Serial.println(WiFi.localIP());
    }
    #else
        WiFi.mode(WIFI_AP);    // Inicia o ESP como um ACCESS POINT (ponto de acesso)
        WiFi.softAP(ssid, password);
        Serial.println(WiFi.softAPIP());
    #endif
    InitializeWebSocket();
    server.addHandler(&ws);

    // Inicia o servidor em si
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", index_html);
    });

    server.onNotFound(notFound);
    server.begin();
}