#define BLYNK_TEMPLATE_ID "xxxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "xxxxxxxxxxxxxxx" // Hidden beacuse of privacy issues
#define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxxx"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Motor pins
#define AIN1 14
#define AIN2 27
#define PWMA 33  

#define BIN1 26
#define BIN2 25
#define PWMB 32  

#define STBY 12

char ssid[] = "xxxx"; // Hidden beacuse of privacy issues
char pass[] = "xxxxxxx";


bool moveF = false, moveB = false, moveL = false, moveR = false;


#define PWM_CHANNEL_A 0
#define PWM_CHANNEL_B 1
#define PWM_FREQ 1000
#define PWM_RES 8

void setup() {
  Serial.begin(115200);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);

  
  ledcSetup(PWM_CHANNEL_A, PWM_FREQ, PWM_RES);
  ledcSetup(PWM_CHANNEL_B, PWM_FREQ, PWM_RES);

  ledcAttachPin(PWMA, PWM_CHANNEL_A);
  ledcAttachPin(PWMB, PWM_CHANNEL_B);

  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  if (moveF) {
    digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
    ledcWrite(PWM_CHANNEL_A, 200);
    ledcWrite(PWM_CHANNEL_B, 200);
  }
  else if (moveB) {
    digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH);
    ledcWrite(PWM_CHANNEL_A, 200);
    ledcWrite(PWM_CHANNEL_B, 200);
  }
  else if (moveL) {
    digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
    ledcWrite(PWM_CHANNEL_A, 180);
    ledcWrite(PWM_CHANNEL_B, 180);
  }
  else if (moveR) {
    digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH);
    ledcWrite(PWM_CHANNEL_A, 180);
    ledcWrite(PWM_CHANNEL_B, 180);
  }
  else {
    ledcWrite(PWM_CHANNEL_A, 0);
    ledcWrite(PWM_CHANNEL_B, 0);
  }
}

BLYNK_WRITE(V0) { moveF = param.asInt(); }
BLYNK_WRITE(V1) { moveB = param.asInt(); }
BLYNK_WRITE(V2) { moveL = param.asInt(); }
BLYNK_WRITE(V3) { moveR = param.asInt(); }
BLYNK_WRITE(V4) {
  moveF = false;
  moveB = false;
  moveL = false;
  moveR = false;
}