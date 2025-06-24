#include <Servo.h>

// Pines del puente H
#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4
#define ENA 9
#define ENB 10

// Pines de los servos
#define SERVO_TILT_PIN 3
#define SERVO_PAN_PIN 2

Servo servoTilt;
Servo servoPan;

int vel = 150; // velocidad del carro

int tiltPos = 90;
int panPos = 90;

void setup() {
  // Motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Servos
  servoTilt.attach(SERVO_TILT_PIN);
  servoPan.attach(SERVO_PAN_PIN);
  servoTilt.write(tiltPos);
  servoPan.write(panPos);

  // Comunicación Serial (Bluetooth HC-05 usa Serial)
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    switch (cmd) {
      case 'F': // Adelante
        adelante();
        break;
      case 'B': // Atrás
        atras();
        break;
      case 'L': // Izquierda
        izquierda();
        break;
      case 'R': // Derecha
        derecha();
        break;
      case 'S': // Stop
        detener();
        break;
      case 'T': // Tilt arriba
        tiltPos = constrain(tiltPos + 5, 0, 180);
        servoTilt.write(tiltPos);
        break;
      case 'X': // Tilt abajo
        tiltPos = constrain(tiltPos - 5, 0, 180);
        servoTilt.write(tiltPos);
        break;
      case 'Y': // Pan izquierda
        panPos = constrain(panPos + 5, 0, 180);
        servoPan.write(panPos);
        break;
      case 'Z': // Pan derecha
        panPos = constrain(panPos - 5, 0, 180);
        servoPan.write(panPos);
        break;
    }
  }
}

// Funciones de movimiento
void adelante() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void atras() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void izquierda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void derecha() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void detener() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}