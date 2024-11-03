#include <ESP8266WiFi.h>
#include <ArduinoWebsockets.h> //https://github.com/gilmaimon/ArduinoWebsockets
#include <DHTesp.h>
#include <ArduinoJson.h> // ArduinoJson kütüphanesini eklemeyi unutmayın.

using namespace websockets;

const char* ssid = "infoTracker";
const char* password = "Lc%gutHJ,]}:H.MtMQ3ZCt9.KcY>1*Hyh=g@4X>h14X}t,5B24%U^i)_m~:Z@ep";
const char* websockets_server = "wss://haysaf.com/api"; // WebSocket sunucusu URL'si

WebsocketsClient client;
const int dhtPin = 5;  // DHT sensör pin numarası
DHTesp dht;

String deviceID = "";
uint8_t mac_address[6];

String secretKey = "dfdRWE6546754F";
String deviceType = "istiklal57";

// LED ve relay pinleri
const int led_wifi_connected = D6;
const int led_server_asked = D7;
const int led_server_answered = D8;
const int relay1Pin = D9; // Değişken tipi int olarak tanımlandı
bool relay1Status = 0;

unsigned long previousMillis = 0;
long interval = 1000; // Başlangıç interval değeri

unsigned long ledPreviousMillis = 0; // LED için zamanlayıcı
const long ledDelay = 100; // LED'in yanıp sönme süresi

void setup() {
  Serial.begin(115200);
  pinMode(led_wifi_connected, OUTPUT);
  pinMode(led_server_asked, OUTPUT);
  pinMode(led_server_answered, OUTPUT);
  pinMode(relay1Pin, OUTPUT);

  digitalWrite(led_wifi_connected, LOW);
  digitalWrite(led_server_asked, LOW);
  digitalWrite(led_server_answered, LOW);

  // Wi-Fi bağlantısını başlat
  WiFi.macAddress(mac_address);
  for (int i = 0; i < 6; ++i) {
    deviceID += String(mac_address[i], 16);
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    digitalWrite(led_wifi_connected, HIGH);
    Serial.print("Bağlanmaya çalışılıyor...");
    delay(50);
    digitalWrite(led_wifi_connected, LOW);
  }
  
  Serial.println("Wi-Fi bağlantısı başarılı!");
  digitalWrite(led_wifi_connected, HIGH);

  dht.setup(dhtPin, DHTesp::DHT11); // DHT sensörü ayarı
  connectWebSocket();  // WebSocket bağlantısını başlat

  // Gelen mesajlar için callback fonksiyonu
  client.onMessage(onMessageCallback);
}

void loop() {
  relay1Status = digitalRead(relay1Pin);
  
  // Wi-Fi bağlantısını kontrol et
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi bağlantısı kesildi, yeniden bağlanılıyor...");
    WiFi.reconnect();  // Wi-Fi'yi yeniden bağla
  }

  // WebSocket bağlantısını kontrol et
  if (!client.available()) {
    connectWebSocket();  // WebSocket bağlantısı kesilmişse yeniden bağlan
  }

  client.poll();  // Mesajları dinle

  // Her belirli aralıklarla ölçüm gönder
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();
    
    String jsonPayload = "{\"deviceType\":\"" + deviceType + "\",\"secretKey\":\"" + secretKey + "\",\"id\":\"" + deviceID +
                         "\",\"tmp\":" + String(temperature) + ",\"hum\":" + String(humidity) +
                         ",\"interval\":" + String(interval) + ",\"relay1\":" + String(relay1Status) + "}";

    if (client.send(jsonPayload)) {
      Serial.println("Mesaj gönderildi: " + jsonPayload);
      // LED'i yak
      digitalWrite(led_server_asked, HIGH);
      ledPreviousMillis = currentMillis; // LED zamanlayıcısını güncelle
    } else {
      Serial.println("Mesaj gönderilemedi.");
    }
  }

  // LED'in yanıp sönmesi için kontrol
  if (currentMillis - ledPreviousMillis < ledDelay) {
    digitalWrite(led_server_asked, LOW); // LED'i kapat
  }
}

void connectWebSocket() {
  if (client.connect(websockets_server)) {
    Serial.println("WebSocket bağlantısı kuruldu!");
  } else {
    Serial.println("WebSocket bağlantısı kurulamıyor! Yeniden denenecek...");
  }
}

// Gelen mesajları işlemek için callback fonksiyonu
void onMessageCallback(WebsocketsMessage message) {
  Serial.print("Gelen Mesaj: ");
  Serial.println(message.data());

  // Gelen mesajdan secretKey ve id'yi kontrol et
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, message.data());

  if (doc.containsKey("secretKey") && doc["secretKey"] == secretKey &&
      doc.containsKey("id") && doc["id"] == deviceID) {
    
    // Relay1 durumunu güncelle
    if (doc.containsKey("relay1")) {
      relay1Status = doc["relay1"]; // Yeni relay1 değeri al
      digitalWrite(relay1Pin, relay1Status); // Relay durumunu güncelle

      // Başarılı durumu serial'e yaz
      if (relay1Status == HIGH) {
        Serial.println("Röle 1 açıldı.");
      } else {
        Serial.println("Röle 1 kapandı.");
      }
    }

    // Interval değerini güncelle
    if (doc.containsKey("interval")) {
      interval = doc["interval"]; // Yeni interval değeri al
      previousMillis = millis(); // Zamanlayıcıyı sıfırla
      Serial.print("Yeni interval ayarlandı: ");
      Serial.println(interval);
    }
  } else {
    Serial.println("Gelen mesajın secretKey veya id değeri eşleşmedi.");
  }
}
