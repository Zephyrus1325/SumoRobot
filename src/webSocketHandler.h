#pragma once

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

AsyncWebSocket ws("/ws");

// Handler de Mensagens recebidas do websocket
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;  
    //Checa se recebeu um websocket valido, eu acho que é isso que esse if faz
    if(info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT){
        // Transforma os dados recebidos (text) em um Json (Json)
        JsonDocument json; 
        DeserializationError err = deserializeJson(json, data);
        // Em caso de erro de serialização
        if(err){
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(err.c_str());
            return;
        }
  
        // Continuar codigo aqui!
        const char *command = json["command"];
        const char *value = json["value"];

        //if (strcmp(command, "calibrate_channel_1") == 0){
        //    receiver.resetCalibration(0);
        //} else if (strcmp(command, "calibrate_channel_2") == 0){
        //    receiver.resetCalibration(1);
        //} else if (strcmp(command, "calibrate_channel_3") == 0){
        //    receiver.resetCalibration(2);
        //} else if (strcmp(command, "calibrate_channel_4") == 0){
        //    receiver.resetCalibration(3);
        //} else if (strcmp(command, "calibrate_channel_5") == 0){
        //    receiver.resetCalibration(4);
        //} else if (strcmp(command, "calibrate_channel_6") == 0){
        //    receiver.resetCalibration(5);
        //} else if (strcmp(command, "calibrate_channel_7") == 0){
        //    receiver.resetCalibration(6);
        //}else if (strcmp(command, "calibrate_channel_8") == 0){
        //    receiver.resetCalibration(7);
        //}
    }
}

// Checa o que deve ser feito ao receber um evento do websocket
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            #ifdef DEBUG
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
            #endif
            break;
        case WS_EVT_DISCONNECT:
            #ifdef DEBUG
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            #endif
            break;
        case WS_EVT_DATA:
            handleWebSocketMessage(arg, data, len);
            break;
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
            break;
    }
}

void InitializeWebSocket(){
    ws.onEvent(onEvent);
}

// Envia todos os dados de controle do veiculo para o cliente web
void sendMetadata(){

}