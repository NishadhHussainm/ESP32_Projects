#define TRIG_PIN 5
#define ECHO_PIN 18

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("Ultrasonic Sensor with ESP32");
}

void loop() {
  long duration;
  float distance;

  // Clear trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send 10us pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo time
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000);
}