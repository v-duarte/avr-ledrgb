/*
 * ATMega328P-tp4.c
 *
 * Created: 11/7/2022 15:12:12
 * Author : Barcala
 */ 

#include <avr/io.h>
#include "main.h"

static char msj_error[]= "Comando no valido\n\r";
static char msj_red[]= "Para comenzar, ingrese el valor de la componente R (entre 0 y 255) \n\r";
static char msj_green[]= "Ingrese el valor de la componente G (entre 0 y 255) \n\r";
static char msj_blue[]= "Ingrese el valor de la componente B (entre 0 y 255) \n\r";
static char msj_fin[]= "Se encendera el LED con el color correspondiente a los valores ingresados. Para cambiar el color, presione ENTER. \n\r";

char cadena[3]=""; //en esta variable se va a guardar la cadena ingresada por el usuario
uint8_t r,g,b,valor,raux,gaux,baux;

uint8_t Conversion(void){
	uint8_t resolucion = 0; //Aqui se pasa el valor de cadena en vector de char a un valor tipo uint8
	for( char* ptr = cadena; *ptr; ++ptr )
	{
		resolucion *= 10;
		resolucion += *ptr - '0';
	}
	//resolucion = 255 - resolucion; //Invertimos el valor para 255 sea el maximo brillo y 0 minimo brillo dado que la conexion esta invertida.
	return resolucion;
}

void SeleccionarColor(void){
	/* Configuracion de RGB LED*/
	SerialPort_Send_String(msj_red);
	memset(cadena, '0', 3); //Reinicio el vector para evitar problemas con posible basura que haya quedado
	while (get_flag_enter() == 0); //espera hasta que el usuario ingrese un valor y enter otra vez.
	set_flag_enter(0); //reinicio el flag de enter
	
	//Rojo
	SerialPort_Get_String_From_Buffer(cadena);
	r = Conversion();
	set_flag_enter(0);
	memset(cadena, '0', 3); //Reinicio el vector para evitar problemas con posible basura que haya quedado
	
	//Verde
	SerialPort_Send_String(msj_green);
	while (get_flag_enter() == 0); //espera hasta que el usuario ingrese un valor y enter otra vez.
	SerialPort_Get_String_From_Buffer(cadena);
	g = Conversion();
	set_flag_enter(0); 
	memset(cadena, '0', 3);                    //Reinicio el vector para evitar problemas con posible basura que haya quedado
	
	//Azul
	SerialPort_Send_String(msj_blue);
	while (get_flag_enter() == 0);             //espera hasta que el usuario ingrese un valor y enter otra vez.
	SerialPort_Get_String_From_Buffer(cadena);
	b = Conversion();
	set_flag_enter(0);
	memset(cadena, '0', 3);                     //Reinicio el vector para evitar problemas con posible basura que haya quedado
	
	SerialPort_Send_String(msj_fin);      /*Asignacion de valores al LED*/
}

void ActualizarPotenciometro(void){
	ADC_Lectura();	                                        //Se lee el valor del potenciometro y se guarda.
	if(get_flag_adc())                               //Se confirma si se leyo el valor del potenciometro correctamente
	{
		valor = get_adc_data();                             //Leo el valor del potenciometro
		valor = ((valor * 100) / 256);                      //Convierto valor en porcentaje
		set_flag_adc(0);	                                //Se reinicia el flag del potenciometro
		Ingreso_R(ActualizarValor(r,valor));
		Ingreso_G(ActualizarValor(g,valor));
		Ingreso_B(ActualizarValor(b,valor));
	}
}

uint8_t ActualizarValor(uint8_t color, uint8_t ref){ //color es el valor del color ingresado por usuario y ref es cuanto hay que cambiar el brillo
	return (color * ref) / 100;
}

/* main con ADC */

int main(void)
{

	/* Inicializacion */
	//DDRB = 0xFF;								//Configuro Port B como salida  ¿Para?
	ledrgb_init();
	PWM_timer1_init();
	PWM_timer2_init();
	
	SerialPort_Init(0x67);						//Configuro el UART 9600bps, 8 bit data, 1 stop @ F_CPU = 16MHz.
	SerialPort_TX_Enable();						//Inicio el transmisor
	SerialPort_TX_Interrupt_Enable();
	
	SerialPort_RX_Enable();						//Inicio el receptor
	SerialPort_RX_Interrupt_Enable();
	
	ADC_Init();									//Inicio el potenciometro
	sei();										//Activo el flag global para interrupciones
	
	mostrarMenu();								//Muestro el menu principal
	
	
	SeleccionarColor();
    while (1) 
    {		
		if (get_flag_enter())
		{
			set_flag_enter(0); //reinicio el flag de enter
			SeleccionarColor();
		}
		else 
			ActualizarPotenciometro();
	}
}