#include <SoftwareSerial.h> // libreria que permite establecer pines digitales

//liberias nRF24L01
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10

byte direccion[5] = { 'c', 'a', 'n', 'a', 'l' };  //Variable con la dirección del canal por donde se va a transmitir
RF24 radio(CE_PIN, CSN_PIN);                      //creamos el objeto radio (NRF24L01)
float datos[3];                                   //vector con los datos a enviar
//FIN nRF24L01


// CRUZETA
#define CRUZE_FORWARD 27
#define CRUZE_REVERSE 26
#define CRUZETA__LEFT 23
#define CRUZETA_RIGHT 24
#define LUCES 25
#define LUCESOFF 34
#define BAILA 28
#define LAZER 29
#define BTN_JOYSTICK_IZQ 33
#define LED 30

// FLECHAS
#define DER_FORWARD 49
#define DER_REVERSE 48
#define IZQ_FORWARD 47
#define IZQ_REVERSE 45

// FLECHAS
#define BRAZO_CORTO_ADLANTE 44
#define BRAZO_CORTO_ATRAS 43
#define BRAZO_LARGO_ADLANTE 42
#define BRAZO_LARGO_ATRAS 40
#define GARRA_ABRIR 39
#define GARRA_CERRAR 38

int POTport = A0;
long POTvalor = 0;
int estadoanteriorPOTvalor = 0;
int velocidad = 0;


void setup() {
  // NRF24L01
  radio.begin();                     //inicializamos el NRF24L01
  Serial.begin(9600);                //inicializamos el puerto serie
  radio.openWritingPipe(direccion);  //Abrimos un canal de escritura
  //FIN nRF24L01


  pinMode(CRUZE_FORWARD, INPUT_PULLUP);
  pinMode(CRUZE_REVERSE, INPUT_PULLUP);
  pinMode(CRUZETA__LEFT, INPUT_PULLUP);
  pinMode(CRUZETA_RIGHT, INPUT_PULLUP);

  pinMode(DER_FORWARD, INPUT_PULLUP);
  pinMode(DER_REVERSE, INPUT_PULLUP);
  pinMode(IZQ_FORWARD, INPUT_PULLUP);
  pinMode(IZQ_REVERSE, INPUT_PULLUP);
  
  pinMode(LUCES, INPUT_PULLUP);
  pinMode(LUCESOFF, INPUT_PULLUP);
  pinMode(LAZER, INPUT_PULLUP);
  pinMode(BAILA, INPUT_PULLUP);
  pinMode(BTN_JOYSTICK_IZQ, INPUT_PULLUP);


   pinMode(BRAZO_CORTO_ADLANTE, INPUT_PULLUP);
   pinMode(BRAZO_CORTO_ATRAS, INPUT_PULLUP);
   pinMode(BRAZO_LARGO_ADLANTE, INPUT_PULLUP);
   pinMode(BRAZO_LARGO_ATRAS, INPUT_PULLUP);
   pinMode(GARRA_ABRIR, INPUT_PULLUP);
   pinMode(GARRA_CERRAR, INPUT_PULLUP);


  pinMode(LED , OUTPUT);  //definir pin como salida

  

}

void loop() {
  digitalWrite(LED , HIGH);   // poner el Pin en HIGH

  //cargamos los datos en la variable datos[]
  datos[0] = analogRead(1) * (5.0 / 1023.0);
  datos[1] = millis();
  bool ok = radio.write(datos, sizeof(datos));//enviamos los datos

  //reportamos por el puerto serial los datos enviados
  // if (ok) {
  if (digitalRead(CRUZE_FORWARD) == LOW) {  // si se presiona PULSADOR1
    int msg = 1;
    datos[2] = msg;
    Serial.println("CRUZE_FORWARD");
  } else if (digitalRead(CRUZE_REVERSE) == LOW) {  // si se presiona PULSADOR1
    int msg = 2;
    datos[2] = msg;
    Serial.println("CRUZE_REVERSE");
  } else if (digitalRead(CRUZETA__LEFT) == LOW) {  // si se presiona PULSADOR1
    int msg = 3;
    datos[2] = msg;
    Serial.println("CRUZETA__LEFT");
  } else if (digitalRead(CRUZETA_RIGHT) == LOW) {  // si se presiona PULSADOR1
    int msg = 4;
    datos[2] = msg;
    Serial.println("CRUZETA_RIGHT");
  }  else if (digitalRead(DER_FORWARD) == LOW) {  // si se presiona PULSADOR1
    int msg = 5;
    datos[2] = msg;
    Serial.println("DER_FORWARD");
  } else if (digitalRead(DER_REVERSE) == LOW) {  // si se presiona PULSADOR1
    int msg = 6;
    datos[2] = msg;
    Serial.println("DER_REVERSE");
  } else if (digitalRead(IZQ_FORWARD) == LOW) {  // si se presiona PULSADOR1
    int msg = 7;
    datos[2] = msg;
    Serial.println("IZQ_FORWARD");
  } else if (digitalRead(IZQ_REVERSE) == LOW) {  // si se presiona PULSADOR1
    int msg = 8;
    datos[2] = msg;
    Serial.println("IZQ_REVERSE");
  } else if (digitalRead(BRAZO_CORTO_ADLANTE) == LOW) {  // si se presiona PULSADOR1
    int msg = 44;
    datos[2] = msg;
    Serial.println("BRAZO_CORTO_ADLANTE");
  } else if (digitalRead(BRAZO_CORTO_ATRAS) == LOW) {  // si se presiona PULSADOR1
    int msg = 43;
    datos[2] = msg;
    Serial.println("BRAZO_CORTO_ATRAS");
  } else if (digitalRead(BRAZO_LARGO_ADLANTE) == LOW) {  // si se presiona PULSADOR1
    int msg = 42;
    datos[2] = msg;
    Serial.println("BRAZO_LARGO_ADLANTE");
  } else if (digitalRead(BRAZO_LARGO_ATRAS) == LOW) {  // si se presiona PULSADOR1
    int msg = 40;
    datos[2] = msg;
    Serial.println("BRAZO_LARGO_ATRAS");
  }else if (digitalRead(GARRA_ABRIR) == LOW) {  // si se presiona PULSADOR1
    int msg = 39;
    datos[2] = msg;
    Serial.println("GARRA_ABRIR");
  }else if (digitalRead(GARRA_CERRAR) == LOW) {  // si se presiona PULSADOR1
    int msg = 38;
    datos[2] = msg;
    Serial.println("GARRA_CERRAR");
  }
    
  
  else if (digitalRead(LUCES) == LOW) {  // si se presiona PULSADOR1
    int msg = 15;
    datos[2] = msg;
    Serial.println("LUCES");
  }  else if (digitalRead(LUCESOFF) == LOW) {  // si se presiona PULSADOR1
    int msg = 14;
    datos[2] = msg;
    Serial.println("LUCESOFF");
  }  else if (digitalRead(LAZER) == LOW) {  // si se presiona PULSADOR1
    int msg = 10;
    datos[2] = msg;
    Serial.println("LAZER");
  } else if (digitalRead(BAILA) == LOW) {  // si se presiona PULSADOR1
    int msg = 10;
    datos[2] = msg;
    Serial.println("LAZER");
  } else if (digitalRead(BTN_JOYSTICK_IZQ) == LOW) {
    Serial.println("BTN_JOYSTICK_IZQ");
  } else {
    int msg = 0;
    datos[2] = msg;
  }

  Serial.print("Datos enviados: ");
  Serial.print(datos[0]);
  Serial.print(" , ");
  Serial.print(datos[1]);
  Serial.print(" , ");
  Serial.println(datos[2]);
  //  } else {
  //Serial.println("no se ha podido enviar");
  //  }
  delay(100);
}
