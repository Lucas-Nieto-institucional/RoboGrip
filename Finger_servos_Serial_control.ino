#include <Servo.h>

Servo thumb;
Servo index;
Servo middle;
Servo ring;
Servo pinky;

#define numRecVals 5
// Se recibirán 5 valores, correspondientes 5 dedos.

#define digitsPerRecVals 1
// Cada dedo tendrá un únido dedo asociado

int RecVals[numRecVals];
// Crea un arreglo de valores enteros recibidos por puerto serial

int stringLength = numRecVals * digitsPerRecVals + 1;
// Formato del string: $00000

int iterator = 0;
bool iteratorStart = false;
// Para recorrer los caracteres del string

String receivedString;

void setup() {
  // put your setup code here, to run once:

  // Iniciar puerto serial a 9600 Baudios
  Serial.begin(9600);

  //Asignar servomotor de cada dedo a un pin del arduino
  thumb.attach(2);
  index.attach(4);
  middle.attach(7);
  ring.attach(8);
  pinky.attach(12);
}

void receiveData() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '$') {
      iteratorStart = true;
    }

    if (iteratorStart) {
      if (iterator < stringLength) {
        receivedString = String(receivedString + c);
        iterator++;
        // Recorrer los caractéres recibidos por puerto serial
      }
      if (iterator >= stringLength) {
        for (int i = 0; i < numRecVals; i++) {
          int num = (i * digitsPerRecVals) + 1;
          RecVals[i] = receivedString.substring(num, num + digitsPerRecVals).toInt();
          // Al obtener 5 dígitos, almacenarlos en el arreglo
        }

        receivedString = "";
        iterator = 0;
        iteratorStart = false;
        // Reiniciar el iterador después de obtener los 5 dígitos
      }
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  receiveData();
  if (RecVals[0] == 1){thumb.write(90);}else{thumb.write(180);}
  if (RecVals[1] == 1){index.write(90);}else{index.write(180);}
  if (RecVals[2] == 1){middle.write(90);}else{middle.write(180);}
  if (RecVals[3] == 1){ring.write(90);}else{ring.write(180);}
  if (RecVals[4] == 1){pinky.write(90);}else{pinky.write(180);}
}
