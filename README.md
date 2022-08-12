# avr-ledrgb
Programa para controlar la intensidad y el color del LED RGB el cual será utilizado mediante un kit con un microcontrolador AVR Atmega 328p a 16MHz y para interactuar con el usuario el mismo cuenta con un terminal. 
Con el terminal el usuario podrá seleccionar un color especifico asignando 3 valores RGB (con rango desde 0 a 255 siendo 255 el máximo), con los cuales se generaran 3 señales PWM (para simular rangos de tensión entre 0-5 V) que encenderán el LED con dicho color. El kit también cuenta con un potenciómetro con el cual el usuario podrá regular la intensidad de luz del LED.

El archivo de Proteus realizado en Proteus 8 Professional 8.10 SP0.

Debido a limitaciones fisicas, el LED RGB esta conectado a los siguientes puertos:
| COLOR | PIN |
| ------------- | ------------- |
| RED    | PB5  |
| GREEN  | PB2  |
| BLUE   | PB1  |

Para simular la onda PWM, se configura el PB3 como PWM y por medio de interrupciones se copia la onda a PB5.
