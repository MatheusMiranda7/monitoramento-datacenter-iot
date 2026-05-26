#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"

// ======================================================
// WIFI
// ======================================================

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ======================================================
// MQTT
// ======================================================

const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

// ======================================================
// DHT22
// ======================================================

DHTesp dhtSensor;

const int DHT_PIN = 15;

// ======================================================
// RELÉ
// ======================================================

const int RELAY_PIN = 4;

// ======================================================
// FUNÇÃO WIFI
// ======================================================

void setup_wifi() {

  delay(10);

  Serial.println();
  Serial.print("Conectando ao WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado!");

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// ======================================================
// FUNÇÃO MQTT
// ======================================================

void reconnect() {

  while (!client.connected()) {

    Serial.print("Conectando MQTT...");

    if (client.connect("ESP32Client-Matheus")) {

      Serial.println(" conectado!");

    } else {

      Serial.print(" erro=");
      Serial.print(client.state());

      Serial.println(" tentando novamente em 2 segundos");

      delay(2000);
    }
  }
}

// ======================================================
// SETUP
// ======================================================

void setup() {

  Serial.begin(115200);

  // Relé
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);

  // Sensor DHT22
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  // WiFi
  setup_wifi();

  // MQTT
  client.setServer(mqtt_server, 1883);
}

// ======================================================
// LOOP PRINCIPAL
// ======================================================

void loop() {

  // Reconecta MQTT caso desconecte
  if (!client.connected()) {

    reconnect();
  }

  client.loop();

  // ======================================================
  // LEITURA SENSOR
  // ======================================================

  TempAndHumidity data = dhtSensor.getTempAndHumidity();

  float temperatura = data.temperature;
  float umidade = data.humidity;

  // ======================================================
  // SERIAL MONITOR
  // ======================================================

  Serial.println("==================================");

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");

  // ======================================================
  // MQTT PUBLICAÇÃO
  // ======================================================

  String tempString = String(temperatura);
  String humString = String(umidade);

  client.publish(
    "matheus/datacenter/temperatura",
    tempString.c_str()
  );

  client.publish(
    "matheus/datacenter/umidade",
    humString.c_str()
  );

  // ======================================================
  // CONTROLE DA VENTILAÇÃO
  // ======================================================

  if (temperatura > 30.0) {

    digitalWrite(RELAY_PIN, HIGH);

    Serial.println("VENTILAÇÃO LIGADA");

    client.publish(
      "matheus/datacenter/alerta",
      "Ventilacao ligada"
    );

  } else {

    digitalWrite(RELAY_PIN, LOW);

    Serial.println("VENTILAÇÃO DESLIGADA");

    client.publish(
      "matheus/datacenter/alerta",
      "Temperatura normal"
    );
  }

  // ======================================================
  // TEMPO ENTRE LEITURAS
  // ======================================================

  delay(3000);
}