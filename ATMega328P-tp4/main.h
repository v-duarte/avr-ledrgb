/*
 * main.h
 *
 * Created: 11/7/2022 15:24:30
 *  Author: Barcala
 */ 


#ifndef MAIN_H_
#define MAIN_H_
#define F_CPU 16000000UL
#include <string.h>
#include "SerialPort.h"
#include "ledrgb.h"
#include "pwm.h"
#include "adc.h"

uint8_t Conversion(void);
void ActualizarPotenciometro(void);
uint8_t map(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max);
uint8_t ActualizarValor(uint8_t color, uint8_t ref);
#endif /* MAIN_H_ */