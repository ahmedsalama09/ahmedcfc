/*
 * registers.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */


#include "std_types.h"
#include "common_macros.h"

extern uint8_t PORTA_DATA;
extern uint8_t PORTB_DATA;
extern uint8_t PORTC_DATA;
extern uint8_t PORTD_DATA;

extern uint8_t PORTA_DIR;
extern uint8_t PORTB_DIR;
extern uint8_t PORTC_DIR;
extern uint8_t PORTD_DIR;

extern uint8_t PORTA_PIN;
extern uint8_t PORTB_PIN;
extern uint8_t PORTC_PIN;
extern uint8_t PORTD_PIN;

extern uint8_t TCCR1A_R;
extern uint8_t TCCR1B_R;
extern uint16_t TCNT1_R;
extern uint16_t ICR1_R;
extern uint8_t OCR1A_R;
extern uint8_t OCR1B_R;




#define		F_CPU		0
#define		COM1A0		0
#define		COM1A1		0
#define		COM1B1		0
#define		COM1B0		0
#define		FOC1B		0
#define		FOC1A		0
#define		WGM10		0
#define		WGM11		0
#define		WGM12		0
#define		WGM13		0
#define		F_CPU		0
