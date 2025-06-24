#include <Servo.h>

Servo servoPan;   // Horizontal
Servo servoTilt;  // Vertical

const int PAN_PIN = 9;
const int TILT_PIN = 10;

// Ángulos de referencia
int centroPan = 90;
int centroTilt = 90;

void setup() {
  servoPan.attach(PAN_PIN);
  servoTilt.attach(TILT_PIN);
  
  // Posición inicial
  servoPan.write(centroPan);
  servoTilt.write(centroTilt);
  delay(1000);
}

void loop() {
  // PAN IZQUIERDA
  moverSuave(servoPan, centroPan, centroPan - 45, 10);
  delay(500);

  // TILT ARRIBA
  moverSuave(servoTilt, centroTilt, centroTilt - 30, 10);
  delay(500);

  // TILT ABAJO
  moverSuave(servoTilt, centroTilt - 30, centroTilt + 30, 10);
  delay(500);

  // TILT CENTRO
  moverSuave(servoTilt, centroTilt + 30, centroTilt, 10);
  delay(500);

  // PAN DERECHA
  moverSuave(servoPan, centroPan - 45, centroPan + 45, 10);
  delay(500);

  // TILT ARRIBA
  moverSuave(servoTilt, centroTilt, centroTilt - 30, 10);
  delay(500);

  // TILT ABAJO
  moverSuave(servoTilt, centroTilt - 30, centroTilt + 30, 10);
  delay(500);

  // TILT CENTRO
  moverSuave(servoTilt, centroTilt + 30, centroTilt, 10);
  delay(1000);

  // PAN al centro
  moverSuave(servoPan, centroPan + 45, centroPan, 10);
  delay(2000); // Espera antes de repetir
}

// Función para mover suavemente
void moverSuave(Servo &servo, int desde, int hasta, int paso) {
  if (desde < hasta) {
    for (int i = desde; i <= hasta; i += paso) {
      servo.write(i);
      delay(50);
    }
  } else {
    for (int i = desde; i >= hasta; i -= paso) {
      servo.write(i);
      delay(50);
    }
  }
}