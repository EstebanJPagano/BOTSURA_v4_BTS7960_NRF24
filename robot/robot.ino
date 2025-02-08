#include <SoftwareSerial.h> // libreria que permite establecer pines digitales
#include "BTS7960.h"

//para servo
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);

unsigned int pos0 = 172; // ancho de pulso en cuentas para pocicion 0°
unsigned int pos180 = 565; // ancho de pulso en cuentas para la pocicion 180°
int servoPos = 90;
//para servo fin

//----- RF24
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10

//Variable con la dirección del canal que se va a leer
byte direccion[5] = {'c', 'a', 'n', 'a', 'l'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector para los datos recibidos
float datos[3];
//----- FIN RF24


// ----------- definir led
int PinLED1 = 47; //ADELANTE
int PinLED2 = 23;
int PinLED3 = 24;
int PinLED4 = 25; //Sierna
int PinLED5 = 26; // adelante izquierda
int PinLED6 = 27; //adelante derecha




// ---------- Sensor infrarrojo de obstaculos.
int IR = 33;
int valorSensor;

// lazer
int LAZER = 48;

// BTS7960 DEFINITION

//motor 1
const uint8_t EN_1 = 23;
const uint8_t L_PWM_1 = 2;
const uint8_t R_PWM_1 = 3;

//motor2
const uint8_t EN_2 = 24;
const uint8_t L_PWM_2 = 4;
const uint8_t R_PWM_2 = 5;

BTS7960 motor1(EN_1, L_PWM_1, R_PWM_1);
BTS7960 motor2(EN_2, L_PWM_2, R_PWM_2);
int speed = 254; // Valor entre 0 y 254
//FIN BTS

void setup()
{

  //deficiciones NRF24L01
  radio.begin(); //inicializamos el NRF24L01
  Serial.begin(9600);  //inicializamos el puerto serie
  radio.openReadingPipe(1, direccion); //Abrimos el canal de Lectura
  radio.startListening(); //empezamos a escuchar por el canal
  // FIN NRF24L01

  // LED
  pinMode(PinLED1, OUTPUT);
  pinMode(PinLED2, OUTPUT);
  pinMode(PinLED3, OUTPUT);
  pinMode(PinLED4, OUTPUT);
  pinMode(PinLED5, OUTPUT);
  pinMode(PinLED6, OUTPUT);


  // LAZER
  pinMode(LAZER, OUTPUT);

  // Sensor IR obstaculos
  pinMode(IR, INPUT);

  //servos
  servos.begin();
  servos.setPWMFreq(60); //Frecuecia PWM de 60Hz o T=16,66ms

}

void loop() {
brazo(44);

  uint8_t numero_canal;
  //if ( radio.available(&numero_canal) )
  if ( radio.available()) {
    //Leemos los datos y los guardamos en la variable datos[]
    radio.read(datos, sizeof(datos));

    //leemos los datos de cada posición del array
    //Serial.print("Dato0= " );
    //Serial.print(datos[0]);
    //Serial.print("velocidad= " );
    //Serial.print(datos[1]);
    //Serial.print("milisegundos= " );
    Serial.println(datos[2]);

    if (datos[2] == 0) {
      motor1.Stop();
      motor2.Stop();
    }
    else if (datos[2] == 1) {
      Forward();
      goLucesAdelante();
    }
    else if (datos[2] == 2) {
      Reverse();
      goLucesReversa();
    }
    else if (datos[2] == 3) {
      Left();
      goLucesIzquierda();
    }
    else if (datos[2] == 4) {
      Right();
      goLucesDerecha();
    }
    else if (datos[2] == 5) {
      derForward();
    }
    else if (datos[2] == 6) {
      derReverse();
    }
    else if (datos[2] == 7) {
      izqForward();
    }
    else if (datos[2] == 8) {
      izqReverse();
    }
    else if (datos[2] == 9) {
      danceDance();
    }
    else if (datos[2] == 14) {
      goLucesOff();
    }
    else if (datos[2] == 15) {
      goLuces();
    }
    else if (datos[2] == 16) {
      goLucesColor();
    }
    else if (datos[2] == 17) {
      goLucesOffColor();
    }
    else if (datos[2] == 10) {
      danceDance();
    }
    //brazo

    else if (datos[0] == 44) {
      brazo(datos[0]); // paso el dato al brazo
    }
    else if (datos[0] == 43) {
      brazo(datos[0]); // paso el dato al brazo
    }
    else if (datos[0] == 42) {
      brazo(datos[0]); // paso el dato al brazo
    }
    else if (datos[0] == 40) {
      brazo(datos[0]); // paso el dato al brazo
    }
    else if (datos[0] == 39) {
      brazo(datos[0]); // paso el dato al brazo
    }
    else if (datos[0] == 38) {
      brazo(datos[0]); // paso el dato al brazo
    }

    else if (datos[0] < 70) {
      speed = (datos[0]); // seteo la velocidad
    }
    else {
      motor1.Stop();
      motor2.Stop();
    }
    delay(10); // Espera un segundo antes de enviar el siguiente mensaje
  }
  else {

    motor1.Stop();
    motor2.Stop();
    Serial.println("No hay datos de radio disponibles");
  }
  delay(100);
}

void derForward() {
  Serial.println("derForward");
  motor1.Enable();
  motor2.Enable();
  motor1.TurnLeft(254);
  motor2.TurnRight(180);
}
void derReverse() {
  Serial.println("derReverse");
  motor1.Enable();
  motor2.Enable();
  motor1.TurnLeft(180);
  motor2.TurnRight(254);
}
void izqForward() {
  Serial.println("izqForward");
  motor1.Enable();
  motor2.Enable();
  motor1.TurnRight(254);
  motor2.TurnLeft(180);
}
void izqReverse() {
  Serial.println("izqReverse");
  motor1.Enable();
  motor2.Enable();
  motor1.TurnRight(180);
  motor2.TurnLeft(254);
}
void Forward() {
  Serial.println("Forward");
  motor1.Enable();
  motor2.Enable();
  motor1.TurnRight(speed);
  motor2.TurnLeft(speed);
}
void Reverse() {
  motor1.Enable();
  motor2.Enable();
  Serial.println("Reverse");
  motor1.TurnLeft(speed);
  motor2.TurnRight(speed);
}
void Left() {
  motor1.Enable();
  motor2.Enable();
  Serial.println("Left");
  motor1.TurnRight(speed);
  motor2.TurnRight(speed);
}
void Right() {
  motor1.Enable();
  motor2.Enable();
  Serial.println("Right");
  motor1.TurnLeft(speed);
  motor2.TurnLeft(speed);
}
void motorStop() {
  Serial.println("Stop");
  motor1.Stop();
  motor2.Stop();
}

// ----------------- LUCES  -----------------
void led_blink() {
  int var = 0;
  digitalWrite(PinLED1, HIGH);  delay(40);
  digitalWrite(PinLED2, HIGH);  delay(40);
  digitalWrite(PinLED3, HIGH);  delay(40);
  digitalWrite(PinLED4, HIGH);  delay(40);
  digitalWrite(PinLED5, HIGH);  delay(40);
  digitalWrite(PinLED6, HIGH);  delay(40);

  digitalWrite(PinLED1, LOW);  delay(40);
  digitalWrite(PinLED2, LOW);  delay(40);
  digitalWrite(PinLED3, LOW);  delay(40);
  digitalWrite(PinLED4, LOW);  delay(40);
  digitalWrite(PinLED5, LOW);  delay(40);
  digitalWrite(PinLED6, LOW);  delay(40);
  var ++;
}

void goLuces() {
  digitalWrite(PinLED1, HIGH); // adelante derecha
  digitalWrite(PinLED2, HIGH);
  digitalWrite(PinLED3, HIGH); //  atras
  digitalWrite(PinLED4, HIGH); // sirena
  digitalWrite(PinLED5, HIGH); // naranja
  digitalWrite(PinLED6, HIGH);  //adelante izq
}

void goLucesAdelante() {
  digitalWrite(PinLED1, HIGH);  // adelante derecha
  digitalWrite(PinLED2, HIGH); // adelante izquierda
}

void goLucesReversa() {
  digitalWrite(PinLED4, HIGH);  // adelante derecha
  digitalWrite(PinLED6, HIGH); // adelante izquierda
}

void goLucesIzquierda() {
  digitalWrite(PinLED2, HIGH);  // adelante derecha
}

void goLucesDerecha() {
  digitalWrite(PinLED1, HIGH);  // adelante derecha
}

void goLucesOff() {
  digitalWrite(LAZER, LOW);
  digitalWrite(PinLED1, LOW);
  digitalWrite(PinLED2, LOW);
  digitalWrite(PinLED3, LOW);
  digitalWrite(PinLED4, LOW);
  digitalWrite(PinLED5, LOW);
  digitalWrite(PinLED6, LOW);
}

void goLucesColor() {
  digitalWrite(PinLED2, HIGH);
  digitalWrite(PinLED4, HIGH);
}

void goLucesColorSirena() {
  digitalWrite(PinLED3, HIGH);
}

void goLucesOffColor() {
  digitalWrite(PinLED2, LOW);
  digitalWrite(PinLED4, LOW);
}

void danceDance() {
  led_blink();
  Right();
  delay(70);

  led_blink();
  Left();
  delay(70);

  led_blink();
  led_blink();
  Right();
  delay(70);

  led_blink();
  Left();
  delay(70);

  led_blink();
  motorStop();
}

//servo

void setServo(uint8_t n_servo, int angulo) {
  int duty;
  duty = map(angulo, 0, 180, pos0, pos180);
  servos.setPWM(n_servo, 0, duty);
}

void brazo(int dato) {

  if (dato == 44) {
    servoPos ++;
    Serial.println(servoPos);

    setServo(0, servoPos);
  }
  if (dato == 43) {
    servoPos --;
    Serial.println(servoPos);
    setServo(0, servoPos);
  }
  if (dato == 42) {
    servoPos ++;
    Serial.println(servoPos);
    setServo(1, servoPos);
  }
  if (dato == 40) {
    servoPos --;
    Serial.println(servoPos);
    setServo(1, servoPos);
  }
  if (dato == 39) {
    servoPos --;
    Serial.println(servoPos);
    setServo(2, servoPos);
  }
  if (dato == 38) {
    servoPos --;
    Serial.println(servoPos);
    setServo(2, servoPos);
  }
  /*
     BRAZO_CORTO_ADLANTE 44
    BRAZO_CORTO_ATRAS 43
    BRAZO_LARGO_ADLANTE 42
    BRAZO_LARGO_ATRAS 40
    GARRA_ABRIR 39
    GARRA_CERRAR 38
  */

}
