#include "esp_camera.h"
#include <WiFi.h>

// ===== Настройки WiFi ===== //
const char* ssid = "urtos";
const char* password = "ssdskask2";

// ===== Выбор модели камеры ===== //
#define CAMERA_MODEL_AI_THINKER  // Для ESP32-CAM
//#define CAMERA_MODEL_WROVER_KIT  // Для ESP32 WROVER Kit с камерой

#include "camera_pins.h"

// ===== Веб-сервер ===== //
WiFiServer server(80);  // Порт 80 (HTTP)

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  // === Инициализация камеры === //
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
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // Разрешение (меньше = быстрее)
  if (psramFound()) {
    config.frame_size = FRAMESIZE_SVGA;  // 800x600
    config.jpeg_quality = 10;            // 0-63 (чем меньше, тем лучше качество)
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_CIF;   // 352x288
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // Запуск камеры
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Ошибка камеры: 0x%x", err);
    return;
  }

  // === Подключение к WiFi === //
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi подключён!");

  // Запуск сервера
  server.begin();
  Serial.print("Сервер запущен! IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Новый клиент подключён");
    String response = "HTTP/1.1 200 OK\r\nContent-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
    client.print(response);

    while (client.connected()) {
      camera_fb_t *fb = esp_camera_fb_get();
      if (!fb) {
        Serial.println("Ошибка захвата кадра");
        break;
      }

      client.print("--frame\r\n");
      client.print("Content-Type: image/jpeg\r\n\r\n");
      client.write(fb->buf, fb->len);
      client.print("\r\n");
      esp_camera_fb_return(fb);
    }
    client.stop();
    Serial.println("Клиент отключён");
  }
}