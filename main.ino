#include <WiFi.h>
#include <PubSubClient.h>

// Network & Telemetry Configuration
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "broker.hivemq.com"; // Public testing broker
const char* telemetry_topic = "bmw/adas/steering/touch";

WiFiClient espClient;
PubSubClient client(espClient);

// Hardware Pin Configuration
const int TOUCH_PIN = 4;        // ESP32 built-in capacitive touch pin
const int TOUCH_THRESHOLD = 30; // Calibration value for human skin capacitance

void setup_wifi() {
    delay(10);
    Serial.println("Connecting to network...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n[NETWORK METRIC] TCP/IP Layer Established.");
}

void reconnect_mqtt() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Assign a random client ID
        String clientId = "ESP32-ADAS-";
        clientId += String(random(0xffff), HEX);
        
        if (client.connect(clientId.c_str())) {
            Serial.println("[METRIC MET] MQTT Broker Connected.");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" retrying in 5 seconds");
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
}

void loop() {
    if (!client.connected()) {
        reconnect_mqtt();
    }
    client.loop();

    // 1. Data Ingestion: Read raw capacitive value
    int touchValue = touchRead(TOUCH_PIN);
    
    // 2. Noise Filtering & State Logic
    String driverState = "HANDS_OFF";
    if (touchValue < TOUCH_THRESHOLD) {
        // Capacitance drops when skin makes contact
        driverState = "HANDS_ON"; 
    }

    // 3. Construct JSON Telemetry Payload
    String payload = "{\"sensor\": \"steering_wheel\", \"capacitance\": " + String(touchValue) + ", \"state\": \"" + driverState + "\"}";

    // 4. Publish to MQTT Broker
    client.publish(telemetry_topic, payload.c_str());
    
    Serial.println("Published: " + payload);
    
    // Throttle transmission to 10Hz (100ms) to prevent network flooding
    delay(100); 
}