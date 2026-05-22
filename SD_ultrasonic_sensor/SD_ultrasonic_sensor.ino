#include <SPI.h>
#include <SD.h>

// -------- PIN CONFIG --------
#define CS   5
#define TRIG 12
#define ECHO 14

// -------- VARIABLES --------
bool objectPresent = false;
unsigned long lastChangeTime = 0;
const int debounceDelay = 2000;

int objCount = 1;   // 🔥 Object counter

File logFile;

// ---------- SENSOR ----------

float getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  return duration * 0.034 / 2;
}

// Take average for stable reading
float getStableDistance() {
  float sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += getDistance();
    delay(5);
  }
  return sum / 5.0;
}

// ---------- TIME ----------

String getTime() {
  unsigned long sec = millis() / 1000;
  int min = sec / 60;
  int s = sec % 60;

  char buf[10];
  sprintf(buf, "%02d:%02d", min, s);
  return String(buf);
}

// ---------- SD WRITE ----------

void writeLog(String msg) {
  logFile = SD.open("/log.txt", FILE_APPEND);

  if (logFile) {
    logFile.println(msg);
    logFile.close();
  } else {
    Serial.println("SD Write Error!");
  }
}

// ---------- SETUP ----------

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  Serial.println("Initializing SD Card...");

  if (!SD.begin(CS)) {
    Serial.println("SD Card Failed!");
    while (1);
  }

  Serial.println("SD Card Ready");

  // Create file if not exists
  if (!SD.exists("/ultrasonic2_log.txt")) {
    logFile = SD.open("/ultrasonic2_log.txt", FILE_WRITE);
    if (logFile) {
      logFile.println("Log Started");
      logFile.close();
    }
  }

  Serial.println("System Ready");
}

// ---------- LOOP ----------

void loop() {
  unsigned long now = millis();

  float d = getStableDistance();

  // Debug distance
  Serial.print("Distance: ");
  Serial.println(d);

  bool inRange = (d > 5 && d < 30);

  // -------- ENTRY --------
  if (inRange && !objectPresent && (now - lastChangeTime > debounceDelay)) {
    objectPresent = true;
    lastChangeTime = now;

    String msg = "Obj " + String(objCount) + " Entry " + getTime();
    Serial.println(msg);
    writeLog(msg);
  }

  // -------- EXIT --------
  else if (!inRange && objectPresent && (now - lastChangeTime > debounceDelay)) {
    objectPresent = false;
    lastChangeTime = now;

    String msg = "Obj " + String(objCount) + " Exit " + getTime();
    Serial.println(msg);
    writeLog(msg);

    objCount++;  
  }

  delay(300);
}