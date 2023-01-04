# Movimiento de prueba para Hexapod

Esta programación consiste en el movimiento de prueba para la plataforma robótica utilizando secuencias ya establecidas en el microcontrolador OpenCm 9.04 y controladas utilizando el ESP32 y Adafruit IO como intefaz gráfica.

Se utilizaron los siguientes archivos editados en ArduinoIDE:

## OpenCm 9.04

Mov_OpenCm.ino - Secuencias establecidas de caminar, retroceder, girar a la derecha e izquierda, parar y levantarse.

## ESP32

adafruitio_02_pubsub.ino - Conexión con AdafruitIO y recibo de datos desde la interfaz gráfica. (Ejemplo de adafruitio_pubsub.ino)

config.h - Establece la conexión WiFi y la llave para el dashboard de AdafruitIO.


### DynamixelWorkbench.h

Se utilizó para el control de los servos Dynamixel AX-12A y XL-320 en el microcontrolador OpenCm 9.04.

# Autor

Luis Roberto Salazar - 17337
