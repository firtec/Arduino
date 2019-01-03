# BMP280 + Qt + Arduino
Archivos base de una interfaz Qt para leer los datos de un sensor BMP280 mediante una conexión serial y una placa Arduino.
La aplicación envía el caracter "a" y espera recibir la temperatura, envía "b" y espera la presión.
El caracter "c" se utiliza como comando para limpiar los buffer's de la UART en la placa Arduino.
Los datos son enviados en formato texto como una simple cadena de caracteres.

www.firtec.com.ar
