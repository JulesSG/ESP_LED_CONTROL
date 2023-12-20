#include <HTTPClient.h>
#include <WiFi.h>

const char* ssid = "GAMING";
const char* password = "JULIOXD098";

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);

  WiFi.begin(ssid, password);

  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("No se pudo conectar");
  }

  Serial.print("Conectado con éxito, mi IP es: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Obtener el estado actual del pin
    http.begin("http://192.168.8.107/ESP/control.php");
    int codigo_respuesta = http.GET();

    if (codigo_respuesta == 200) {
      String cuerpo_respuesta = http.getString();
      Serial.println("Estado actual del pin: " + cuerpo_respuesta);
      if(cuerpo_respuesta == "ON")
      {
        digitalWrite(2, HIGH);

      }
      else
      {
        digitalWrite(2, LOW);
      }
    } else {
      Serial.println("Error al obtener el estado del pin");
    }

    http.end();


 
  } else {
    Serial.println("Error en la conexión WIFI");
  }

  delay(100);
}