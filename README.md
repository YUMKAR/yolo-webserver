# 세이프 스탭 (Safe Step)

## 📌 프로젝트 소개

**세이프 스탭(Safe Step)**은 YOLO 모델을 활용해 **사용자의 입장·퇴장을 자동으로 감지**하고, 아두이노 센서(조도, 온도, 습도, 빗물 감지)를 통해 측정한 데이터를 **라즈베리파이와 블루투스 통신으로 전달**받아 **퇴장 시 조건별 음성 메시지를 출력**하는 스마트 환경 감지 시스템입니다.

본 프로젝트는 실내 환경 변화와 사용자 동작을 연결하여 보다 안전하고 편리한 공간을 구현하는 것을 목표로 합니다.

---

## 🚀 주요 기능

* 🧍‍♂️ **YOLO 기반 입장/퇴장 감지**
* 🌡️ **온도·습도 감지 (Arduino)**
* 💡 **조도(Light) 센서 측정**
* ☔ **비 감지 센서 측정**
* 📡 **아두이노 → 라즈베리파이 블루투스 통신**
* 🔊 **퇴장 감지 시 상황별 음성 메시지 재생**
* 🖥️ **라즈베리파이 기반 메인 애플리케이션 동작**

---

## 🛠 기술 스택

* **Python** — YOLO 모델 실행 및 전체 프로그램 제어
* **C++ / Arduino** — 센서 제어 및 블루투스 송신
* **Raspberry Pi** — 메인 컨트롤러, Python 실행 환경
* **Bottle** — 센서값 응답용 API
* **YOLO 모델 (ultralytics)** — 사람 감지 / 입장·퇴장 판단

---

## 🗂 프로젝트 구조 예시

```
SafeStep/
├─ MainApp.py
├─ weights/
│   └─ yolo_model.pt
├─ Arduino/
│   └─ sensor_code.ino
├─ bluetooth/
│   └─ SerialMonitor.py
├─ audio/
│   ├─ in.mp3
│   ├─ out.mp3
│   ├─ rain.mp3
│   └─ hot.mp3
└─ requirements.txt
```

---

## 🔧 설치 방법

### 1. 필수 패키지 설치

```
pip install -r requirements.txt
```

### 2. YOLO 모델 파일 준비

* `/weights` 폴더에 학습된 YOLO 모델(`.pt`) 파일을 위치시킵니다.

### 3. 아두이노 업로드

* Arduino IDE에서 `sensor_code.ino` 파일을 Arduino MegaUno에 업로드합니다.

---

## ▶️ 실행 방법

```
python MainApp.py
```

* 실행 시 YOLO 모델 로드
* 블루투스 데이터 수신 시작
* 입장/퇴장 감지 및 음성 메시지 출력 동작 시작

