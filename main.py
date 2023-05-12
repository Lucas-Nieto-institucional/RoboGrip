# -*- coding: utf-8 -*-
"""
Created on Wed May 5  16:20:37 2023

ROBOGRIP Hand Tracker Module
ExpoAndes 2023-10

Librerías requeridas:

opencv-python | version 4.7.0.72
       cvzone | version 1.4.1
    mediapipe | version 0.9.3.0

@author: lucas
"""

import cv2
from cvzone.SerialModule import SerialObject
from cvzone.HandTrackingModule import HandDetector


def main():
    # Accede a la Webcam por defecto
    cap = cv2.VideoCapture(0)  # Si hay más webcams conectadas el parámetro será 1, 2, ...

    # Iniciar detector de manos
    detector = HandDetector(detectionCon=0.7, maxHands=1)

    # Iniciar comunicación con puerto serial
    mySerial = SerialObject("COM3", 9600, 1)  # (Puerto serial, tasa de transferencia en baudios, 1 dígito por
    # elemento del array)

    while True:
        success, img = cap.read()

        # Rastrear manos en la webcam
        img = detector.findHands(img)
        lmlist, bbox = detector.findPosition(img)

        if lmlist:
            # Array de dedos levantados
            fingers = detector.fingersUp()
            print(fingers)

            # Enviar el array por puerto serial
            mySerial.sendData(fingers)

        # Mostrar webcam
        cv2.imshow("ROBOGRIP Hand Tracker Module", img)

        # Comando de finalización: Tecla q
        if cv2.waitKey(1) == ord('q'):
            cap.release()
            cv2.destroyAllWindows()
            break


if __name__ == "__main__":
    main()
