#pragma once

// Variavel de Programação, usada pra quando estiver programando
// COMMENTAR ANTES DA LUTA!!!!!
#define PROGRAMMING

// Ativa Impressão de Dados de diagnóstico do robo
#define DEBUG

// Senha da rede para entrar quando o robo estiver sendo programado
// Senha da rede a ser criada pelo robo quando estiver sendo usado em luta
#ifdef PROGRAMMING
    const char* ssid = "LabMaker_Teste";
    const char* password = "LabMakerTeste";
#else
    const char* ssid = "LabMaker Sumo";
    const char* password = "LutchaLutcha";
#endif