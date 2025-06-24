#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>

// Selecciona el modelo AI Thinker
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// Credenciales WiFi
const char* ssid = "aleh";
const char* password = "12345678";

// Crear servidor en el puerto 80
WebServer server(80);

// Función para servir imagen JPEG
void handleCapture() {
  camera_fb_t* fb = esp_camera_fb_get();
  if (!fb) {
    server.send(500, "text/plain", "Error al capturar imagen");
    return;
  }

  WiFiClient client = server.client();

  // Enviar cabecera HTTP correctamente (solo una vez)
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: image/jpeg");
  client.println("Content-Length: " + String(fb->len));
  client.println(); // línea en blanco para terminar cabeceras

  // Enviar imagen
  client.write(fb->buf, fb->len);

  esp_camera_fb_return(fb);
}


// Página de prueba para la ruta "/"
void handleRoot() {
  server.send(200, "text/html", "<h1>ESP32-CAM funcionando</h1><p>Ir a <a href=\"/capture\">/capture</a> para ver imagen</p>");
}

// Inicia el servidor de la cámara
void startCameraServer() {
  server.on("/", handleRoot);
  server.on("/capture", HTTP_GET, handleCapture);
  server.begin();
}

// Configuración inicial
void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  // Configuración de la cámara
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_VGA;         // Resolución 640x480
  config.jpeg_quality = 12;                  // Calidad moderada para fluidez
  config.fb_count = 2;                       // Usar doble buffer
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.grab_mode = CAMERA_GRAB_LATEST;

  // Inicializar la cámara
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Error al iniciar cámara: 0x%x", err);
    return;
  }

  // Ajustes del sensor
  sensor_t* s = esp_camera_sensor_get();
  s->set_vflip(s, 1);       // Voltear verticalmente si es necesario
  s->set_brightness(s, 1);  // Subir brillo
  s->set_saturation(s, -1); // Reducir saturación

  // Conectar al WiFi
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Iniciar servidor web
  startCameraServer();
  Serial.println("Servidor iniciado. Accede a http://[IP]/ o http://[IP]/capture");
}

void loop() {
  server.handleClient(); // Atender peticiones web
}
