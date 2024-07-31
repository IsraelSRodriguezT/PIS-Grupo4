#include <Servo.h>

// Pines de las fotorresistencias
const int SensorI1 = A0;
const int SensorD1 = A1;
const int SensorI2 = A2;
const int SensorD2 = A3;

// Pines de los servomotores
const int pinServoX = 9;
const int pinServoY = 10;

// Pin del interruptor
const int pinInterruptor = 11;

// Crear objetos Servo
Servo servoX;
Servo servoY;

// Variables para almacenar los valores de las fotorresistencias
int valorSensorI1, valorSensorD1, valorSensorI2, valorSensorD2;

// Ángulos actuales y objetivos de los servos
int anguloActualX = 0; // Inicializar en 0 grados
int anguloActualY = 0; // Inicializar en 0 grados
int anguloObjetivoX = 0;
int anguloObjetivoY = 0;

// Velocidades de movimiento de los servos
const int velocidadServo = 2; // Ajusta este valor para hacer el movimiento más lento o más rápido

// Umbral para detectar la falta de luz
const int umbralLuz = 100; // Ajusta este valor según el entorno

// Umbral para detectar el cambio significativo en el ángulo
const int umbralAngulo = 5; // Ajusta este valor para controlar la sensibilidad

// Variable para almacenar el estado del interruptor
int estadoInterruptor = 0;
int ultimoEstadoInterruptor = HIGH; // Para detectar el cambio de estado del interruptor

void setup() {
  // Inicializar el pin del interruptor como entrada con resistencia pull-up
  pinMode(pinInterruptor, INPUT_PULLUP);

  // Configurar los servos
  servoX.attach(pinServoX);
  servoY.attach(pinServoY);

  // Mover los servos lentamente a la posición inicial (0, 0) en el setup
  moverServosAPosicion(0, 0);

  // Inicializar la comunicación serial
  Serial.begin(9600);
  Serial.setTimeout(100); // Configurar el tiempo de espera para la lectura serial
}

void loop() {
  // Leer el estado del interruptor
  estadoInterruptor = digitalRead(pinInterruptor);

  // Detectar el cambio de estado del interruptor
  if (estadoInterruptor != ultimoEstadoInterruptor) {
    ultimoEstadoInterruptor = estadoInterruptor;
    // Mover los servos a la posición 0 de manera gradual antes de cambiar el modo
    moverServosAPosicion(0, 0);
  }

  if (estadoInterruptor == LOW) {
    Serial.println("El interruptor está ENCENDIDO (Control por Sensores)");

    // Leer los valores de las fotorresistencias
    valorSensorI1 = analogRead(SensorI1);
    valorSensorD1 = analogRead(SensorD1);
    valorSensorI2 = analogRead(SensorI2);
    valorSensorD2 = analogRead(SensorD2);

    // Calcular el promedio de los valores de las LDR a la izquierda y a la derecha
    int promIzq = (valorSensorI1 + valorSensorI2) / 2;
    int promDer = (valorSensorD1 + valorSensorD2) / 2;

    // Calcular la diferencia de luz entre izquierda y derecha
    int diferencia = promDer - promIzq;

    // Calcular los ángulos de los servos basados en la diferencia de luz
    int rangoAngulo = 180; // Rango total de ángulos para los servos

    anguloObjetivoX = constrain(map(diferencia, -1023, 1023, 0, rangoAngulo), 0, rangoAngulo);
    anguloObjetivoY = constrain(map(-diferencia, -1023, 1023, 0, rangoAngulo), 0, rangoAngulo);

    // Verificar si los valores de luz están por debajo del umbral
    if (promIzq < umbralLuz && promDer < umbralLuz) {
      anguloObjetivoX = 0;
      anguloObjetivoY = 0;
    }

    // Suavizar el movimiento de los servos
    moverServosSuavemente();
  } else {
    Serial.println("El interruptor está APAGADO (Control por Serial)");

    if (Serial.available() > 0) {
      // Leer los datos desde el puerto serial
      String datos = Serial.readStringUntil('\n');

      // Separar los valores
      int indiceEspacio = datos.indexOf(' ');
      if (indiceEspacio != -1) {
        String valXStr = datos.substring(0, indiceEspacio);
        String valYStr = datos.substring(indiceEspacio + 1);

        // Convertir los valores a enteros
        anguloObjetivoX = constrain(valXStr.toInt(), 0, 180);
        anguloObjetivoY = constrain(valYStr.toInt(), 0, 180);

        // Suavizar el movimiento de los servos
        moverServosSuavemente();
      } else {
        Serial.println("Error: Datos recibidos no válidos");
      }
    }
  }

  // Esperar un poco antes de la siguiente lectura
  delay(10);
}

// Función para mover los servos a una posición específica de manera suave
void moverServosAPosicion(int anguloX, int anguloY) {
  anguloObjetivoX = anguloX;
  anguloObjetivoY = anguloY;
  // Mover los servos a la posición objetivo suavemente
  while (abs(anguloActualX - anguloObjetivoX) > umbralAngulo || abs(anguloActualY - anguloObjetivoY) > umbralAngulo) {
    moverServosSuavemente();
    delay(1); // Ajustar el delay para controlar la velocidad de movimiento
  }
}

// Función para suavizar el movimiento de los servos hacia sus ángulos objetivos
void moverServosSuavemente() {
  if (anguloActualX < anguloObjetivoX) {
    anguloActualX += velocidadServo;
    if (anguloActualX > anguloObjetivoX) {
      anguloActualX = anguloObjetivoX;
    }
  } else if (anguloActualX > anguloObjetivoX) {
    anguloActualX -= velocidadServo;
    if (anguloActualX < anguloObjetivoX) {
      anguloActualX = anguloObjetivoX;
    }
  }

  if (anguloActualY < anguloObjetivoY) {
    anguloActualY += velocidadServo;
    if (anguloActualY > anguloObjetivoY) {
      anguloActualY = anguloObjetivoY;
    }
  } else if (anguloActualY > anguloObjetivoY) {
    anguloActualY -= velocidadServo;
    if (anguloActualY < anguloObjetivoY) {
      anguloActualY = anguloObjetivoY;
    }
  }

  // Mover los servos a los nuevos ángulos suavemente
  servoX.write(anguloActualX);
  servoY.write(anguloActualY);
}