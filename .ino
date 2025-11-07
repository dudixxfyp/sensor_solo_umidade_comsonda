#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

// --- CONFIGURAÇÃO DO WI-FI ---
const char* ssid = "SEU_WIFI";         
const char* password = "SUA_SENHA";    

// --- CONFIGURAÇÃO DA API ---
const char* serverUrl = "http://SEU_IP:5000/dados"; // 

// --- PINOS DO SENSOR ---
#define SENSOR_ANALOGICO A0
#define SENSOR_DIGITAL D1

// --- CLIENTE NTP (para data/hora) ---
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", -3 * 3600, 60000); // GMT-3 (Brasil)

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_DIGITAL, INPUT);

  Serial.println("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  delay(1000);
}

void loop() {
  timeClient.update();

  // --- Obtém data e hora ---
  String horaAtual = timeClient.getFormattedTime();
  time_t epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);

  int dia = ptm->tm_mday;
  int mes = ptm->tm_mon + 1;
  int ano = ptm->tm_year + 1900;

  // --- Lê o sensor ---
  int valorAnalogico = analogRead(SENSOR_ANALOGICO);
  int valorDigital = digitalRead(SENSOR_DIGITAL);
  int umidadePercentual = map(valorAnalogico, 1023, 0, 0, 100);

  // --- Monta o JSON ---
  String jsonData = "{";
  jsonData += "\"data\":\"" + String(dia) + "/" + String(mes) + "/" + String(ano) + "\",";
  jsonData += "\"hora\":\"" + horaAtual + "\",";
  jsonData += "\"umidade_analogica\":" + String(valorAnalogico) + ",";
  jsonData += "\"umidade_percentual\":" + String(umidadePercentual) + ",";
  jsonData += "\"estado_digital\":\"" + String(valorDigital == HIGH ? "SECO" : "UMIDO") + "\"";
  jsonData += "}";

  // --- Envia os dados via HTTP POST ---
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      Serial.print("Dados enviados! Código: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Erro no envio: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Wi-Fi desconectado!");
  }

  Serial.println(jsonData);
  Serial.println("-----------------------------");

  delay(5000); // Envia a cada 5 segundos
}
