// ---------------- MOTOR PINS ----------------
#define M1 15
#define M2 14
#define M3 17
#define M4 16

// Enable pins (PWM)
#define ENA 3
#define ENB 9

// IR Sensors (BLACK = HIGH)
#define IR_LEFT 4
#define IR_RIGHT 5

// Ultrasonic
#define TRIG 6
#define ECHO 7

int speedVal = 160; // Motor speed (0–255)

// ---------------- SETUP ----------------
void setup() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);

  // Set motor speed
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);
}

// ---------------- MOTOR FUNCTIONS ----------------
void forward() {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  digitalWrite(M3, HIGH);
  digitalWrite(M4, LOW);
}

void left() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  digitalWrite(M3, HIGH);
  digitalWrite(M4, LOW);
}

void right() {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, HIGH);
}

void stopMotor() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);
}

// ---------------- ULTRASONIC ----------------
long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);
  long distance = duration * 0.034 / 2;

  return distance;
}

// ---------------- LOOP ----------------
void loop() {

  long distance = getDistance();
  Serial.println(distance);
  delay(100);

  // If obstacle detected → STOP
  if (distance < 10 && distance > 0) {
    stopMotor();
    return; // skip line following
  }

  // ---------------- LINE FOLLOWER ----------------
  int leftIR = digitalRead(IR_LEFT);
  int rightIR = digitalRead(IR_RIGHT);

  if (leftIR == LOW && rightIR == LOW) {
    forward();
  }
  else if (leftIR == LOW && rightIR == HIGH) {
    right();
  }
  else if (leftIR == HIGH && rightIR == LOW) {
    left();
  }
  else {
    stopMotor();
  }
}