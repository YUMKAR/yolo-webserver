#include <DHT.h>

// === DHT 설정 ===
const int DHT_PIN = 12;
const int DHT_TYPE = DHT11;
DHT dht(DHT_PIN, DHT_TYPE);

// === LDR 설정 ===
const int LDR_PIN = A0; // LDR 연결 핀

// === 빗물센서 설정 ===
const int RAIN_PIN = A4; // 빗물센서 연결 핀

// === 시간 제어 ===
unsigned long previousMillis = 0;
int interval = 2000; // 2초마다 측정

// 센서 값 저장 변수
float h = 0.0;
float t = 0.0;
int lightLevel = 0;
int rainValue = 0;

void setup() {
    Serial.begin(9600);   // USB Serial (모니터 확인용)
    Serial1.begin(9600);  // HC-06 Bluetooth
    dht.begin();

    pinMode(RAIN_PIN, INPUT);
    pinMode(LDR_PIN, INPUT);
}

void loop() {
    // 시리얼 브리지 (USB ↔ 블루투스)
    if (Serial.available() > 0) {
        int data = Serial.read();
        Serial1.write(data);
    }

    if (Serial1.available() > 0) {
        int data = Serial1.read();
        Serial.write(data);
    }

    // 주기적 센서 읽기
    unsigned long currentMillis = millis();
    if ((currentMillis - previousMillis) >= interval) {
        previousMillis = currentMillis;

        // 센서 값 읽기
        h = dht.readHumidity();
        t = dht.readTemperature();
        lightLevel = analogRead(LDR_PIN);
        rainValue = analogRead(RAIN_PIN);

        // DHT 센서 읽기 실패 처리
        if (isnan(h) || isnan(t)) {
            Serial.println("Failed to read DHT values.");
            return;
        }

        // 빗물 감지 상태 계산
        String rainStatus;
        if (rainValue < 500) {          // 센서값 0~1023 (낮을수록 젖음)
            rainStatus = "비 감지됨";
        } else if (rainValue < 800) {
            rainStatus = "약한 습기";
        } else {
            rainStatus = "맑음";
        }

        // --- 시리얼 출력 ---
        Serial.print("Humidity: "); Serial.print(h); Serial.print("% ");
        Serial.print("Temp: "); Serial.print(t); Serial.print("°C ");
        Serial.print("Light: "); Serial.print(lightLevel); Serial.print(" ");
        Serial.print("Rain: "); Serial.print(rainValue); Serial.print(" (");
        Serial.print(rainStatus); Serial.println(")");

        // --- 블루투스로 전송 ---
        Serial1.print("H:"); Serial1.print(h); Serial1.print("%,");
        Serial1.print("T:"); Serial1.print(t); Serial1.print("C,");
        Serial1.print("L:"); Serial1.print(lightLevel); Serial1.print(",");
        Serial1.print("R:"); Serial1.print(rainValue); Serial1.print("(");
        Serial1.print(rainStatus); Serial1.println(")");
    }
}
