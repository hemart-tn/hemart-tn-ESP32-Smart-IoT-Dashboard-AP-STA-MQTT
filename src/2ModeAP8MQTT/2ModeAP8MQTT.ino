#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"

// ================= WIFI =================
#define WIFI_SSID "HiFi-13897"
#define WIFI_PASS "pssslemanale"

// ================= MQTT =================
const char* mqtt_server = "7f55e70e343b4baaada935114c7f9610.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "hemart";
const char* mqtt_pass = "Hemart123@";

// ================= PIN =================
#define trigPin 5
#define echoPin 18

#define RED_PIN   19
#define GREEN_PIN 21
#define BLUE_PIN  22

WiFiClientSecure espClient;
PubSubClient client(espClient);

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// ================= ULTRASONIC =================
int readDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if(duration == 0) return -1;

  return duration * 0.034 / 2;
}

// ================= RGB =================
void setRGB(int r, int g, int b){
  ledcWrite(RED_PIN, r);
  ledcWrite(GREEN_PIN, g);
  ledcWrite(BLUE_PIN, b);
}

// ================= MQTT CALLBACK =================
void callback(char* topic, byte* payload, unsigned int length) {

  String msg = "";
  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  Serial.print("MQTT: ");
  Serial.println(msg);

  int r, g, b;
  if (sscanf(msg.c_str(), "%d,%d,%d", &r, &g, &b) == 3) {
    setRGB(r, g, b);
  }
}

// ================= MQTT CONNECT =================
void reconnectMQTT() {

  if (WiFi.status() != WL_CONNECTED) return;

  if (!client.connected()) {
    Serial.print("Connecting MQTT...");

    if (client.connect("ESP32Client", mqtt_user, mqtt_pass)) {
      Serial.println("Connected!");
      client.subscribe("iot/esp32/rgb");
    } else {
      Serial.print("Failed rc=");
      Serial.println(client.state());
    }
  }
}

// ================= WEBSOCKET =================
void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
                     AwsEventType type, void *arg, uint8_t *data, size_t len) {

  if (type == WS_EVT_DATA) {
    String msg = "";

    for (size_t i = 0; i < len; i++) {
      msg += (char)data[i];
    }

    Serial.print("WS: ");
    Serial.println(msg);

    int r, g, b;
    if (sscanf(msg.c_str(), "%d,%d,%d", &r, &g, &b) == 3) {
      setRGB(r, g, b);
    }
  }
}

// ================= WIFI RECONNECT =================
void reconnectWiFi(){
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reconnecting WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
  }
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // PWM
  ledcAttach(RED_PIN, 5000, 8);
  ledcAttach(GREEN_PIN, 5000, 8);
  ledcAttach(BLUE_PIN, 5000, 8);

  setRGB(0,0,0);

  // WiFi mode
  WiFi.mode(WIFI_AP_STA);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting WiFi");

  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED && timeout < 10) {
    delay(1000);
    Serial.print(".");
    timeout++;
  }

  if(WiFi.status() == WL_CONNECTED){
    Serial.println("\nWiFi STA Connected");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nSTA Failed");
  }

  // AP fallback
  WiFi.softAP("ESP32_IoT", "12345678");
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  // MQTT
  espClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // LittleFS
  if(!LittleFS.begin()){
    Serial.println("LittleFS ERROR");
    return;
  }

  // Web server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });

  server.serveStatic("/", LittleFS, "/");

  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);

  server.begin();
  Serial.println("Web Server Started");
}

// ================= LOOP =================
unsigned long lastMsg = 0;

void loop() {

  reconnectWiFi();
  reconnectMQTT();
  client.loop();

  ws.cleanupClients(); // penting untuk stabilitas

  if (millis() - lastMsg > 1000) {
    lastMsg = millis();

    int jarak = readDistance();

    Serial.print("Jarak: ");
    Serial.println(jarak);

    if(jarak != -1){
      String data = String(jarak);

      client.publish("iot/esp32/jarak", data.c_str());
      ws.textAll(data);
    }
  }
}