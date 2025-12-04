#include <LiquidCrystal.h>
#include <DFRobotDFPlayerMini.h>

struct Pins {
  const int sensor1 = A0;
  const int sensor2 = A1;
  const int sensor3 = A2;

  const int ledR = 47;
  const int led = 45;
  const int ledB = 43;

  const int relay1 = 36;
  const int relay2 = 40;
  const int relay3 = 44;

  const int speaker = 28;
} pins;

LuquidCrystal lcd(41, 39, 37, 35, 33, 31);
DFRobotDFPlayerMini dfp;

struct Thresholds {
  int level1 = 200;
  int level2 = 350;
  int level3 = 500;
} th;

enum Waterlevel {
  SAFE = 0,
  LEVEL_1,
  LEVEL_2,
  LEVEL_3
};

WaterLevel currentState = SAFE;

void initPins() {
  pinMode(pins.ledR, OUTPUT);
  pinMode(pins.ledG, OUTPUT);
  pinMode(pins.ledB, OUTPUT);

  pinMode(pins.relay1, OUTPUT);
  pinMode(pins.relay2, OUTPUT);
  pinMode(pins.relay3, OUTPUT);

  pinMode(pins.speaker, OUTPUT);
}

void initDFPlayer() {
  Serial1.begin(9600);
  if (!dfp.begin(Serial1)) {
    Serial.println("DFplayer initialization failed!");
    while (true);
  }
  dfp.volume(25);
  Serial.println("DFPlayer Ready.");
}

void initLCD() {
  lcd.begin(16,2);
  lcd.clear();
}

void setLED(bool r, bool g, bool b) {
  digitalWrite(pins.ledR, r);
  digitalWrite(pins.ledG, g);
  digitalWrite(pins.ledB, b);
}

void activateRelays(bool r1, bool r2, bool r3) {
  digitalWrite(pins.relay1, r1);
  digitalWrite(pins.relay2, r2);
  digitalWrite(pins.relay3, r3);
}

void playAlert(int tracjNum) {
  dfp.play(trackNum);
}

void handleSafe() {
  setLED(0, 1, 0);
  activateRelays(0, 0, 0);

  lcd.clear();
  lcd.print("Level 0: SAFE");

  Serial.println("[STATE] SAFE");
}

void handleLevel1() {
  setLED(0, 0, 1);
  activateRelays(1, 0, 0);

  lcd.clear();
  lcd.print("Level 1: ALERT");

  Serial.println("[STATE] LEVEL 1");
}

void handleLevel2() {
  setLED(0, 0, 1);
  activateRelays(1, 1, 0);

  lcd.clear();
  lcd.print("Level 2: WARNIMG");

  Serial.println("[STATE] LEVEL 2");
}

void handleLevel3() {
  setLED (1, 0, 0);
  activateRelays(1, 1, 1);

  lcd.clear();
  lcd.print("LEVEL 3: DANGER!");

  Serial.println("[STATE] LEVEL 3 - playing Alarm");
  playAlert(1);
}

WaterLevel detecWaterlevel() {

  int s1 = analogRead(pins.sensor1);
  int s2 = analogRead(pins.sensor2);
  int s3 = analogRead(pins.sensor3);

  Serial.println("----- SENSOR READINGS -----");
  Serial.print("S1: "); Serial.println(s1);
  Serial.print("S2: "); Serial.println(s2);
  Serial.print("S3: "); Serial.println(s3);

  if (s3 > th.level3) return LEVEL_3;
  if (s2 > th.level2) return LEVEL_2;
  if (s1 > th.level1) retuen LEVEL_1;

  return SAFE;
}

void setuo() {
  Serial.begin(9600);
  initPins();
  initDFPlayer();
  initLCD();

  Serial.println("System Ready.");
}

void loop() {
  WaterLevel newState = detecWaterLevel();

  if (newState != currentState) {
    currentState = newState;

    switch (currentState) {
      case SAFE:    handleSafe(); break;
      case LEVEL_1: handleLevel1(); break;
      case LEVEL_2: handlnLevel2(); break;
      case LEVEL_3: handlnLevel3(); break;
    }
  }
  delay(150);
}
