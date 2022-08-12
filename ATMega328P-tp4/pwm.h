/*
 * pwm.h
 *
 * Created: 26/7/2022 18:44:27
 *  Author: Victor
 */ 


#ifndef PWM_H_
#define PWM_H_

// Interrupciones del Microcontrolador
#include <avr/interrupt.h>

// Programa Principal    -Frecuencia etc.-
#include "main.h"

// Definiciones de la libreria
#define bled_pwm_threshold OCR1A
#define gled_pwm_threshold OCR1B
#define rled_pwm_threshold OCR2A
// -------- Prototipos de funciones Publicas ---------------
void PWM_timer1_init(void);
void PWM_timer2_init(void);
void Ingreso_R(uint8_t r);
void Ingreso_G(uint8_t g);
void Ingreso_B(uint8_t b);
#endif /* PWM_H_ */