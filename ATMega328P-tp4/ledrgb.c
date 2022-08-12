/*
 * ledrgb.c
 *
 * Created: 11/7/2022 15:24:07
 *  Author: Barcala
 */ 
#include "ledrgb.h"

void ledrgb_init(void){
	DDRB |= (1<<DDB1); //PIN PB1 como salida
	DDRB |= (1<<DDB2); //PIN PB2 como salida
	DDRB |= (1<<DDB3); //PIN PB3 como salida   Dado que este valor se copia abajo.
	DDRB |= (1<<DDB5); //PIN PB5 como salida	
}