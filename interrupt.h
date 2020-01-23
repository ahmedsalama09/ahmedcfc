/*
 * interrupt.h
 *
 *  Created on: Dec 9, 2019
 *      Author: ahmad
 */



#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "registers.h"

/*ProtoTypes of all IRQS*/
void INTO_irq(void) __attribute__((signal, interrupt));
void INT1_irq (void) __attribute__ ((signal, interrupt)) ;
void INT2_irq (void) __attribute__ ((signal, interrupt)) ;
void TIMER2_COMP_irq (void) __attribute__ ((signal,interrupt)) ;
void TIMER2_OVF_irq (void) __attribute__ ((signal,interrupt));
void TIMER1_CAPT_irq (void) __attribute__ ((signal,interrupt));
void TIMER1_COMPA_irq (void) __attribute__ ((signal,interrupt));
void TIMER1_COMPB_irq (void) __attribute__ ((signal,interrupt));
void TIMER1_OVF_irq (void) __attribute__ ((signal,interrupt));
void SPI_STC_irq (void) __attribute__ ((signal,interrupt));
void USART_RXC_irq (void) __attribute__ ((signal,interrupt));
void USART_UDRE_irq (void) __attribute__ ((signal,interrupt));
void USART_TXC_irq (void) __attribute__ ((signal,interrupt));
void ADC_irq (void) __attribute__ ((signal,interrupt));
void EE_RDY_irq (void) __attribute__ ((signal,interrupt));
void ANA_COMP_irq (void) __attribute__ ((signal,interrupt));
void TWI_irq (void) __attribute__ ((signal,interrupt));
void SPM_RDY_irq (void) __attribute__ ((signal,interrupt));


#define INTO_irq			__vector_1
#define INT1_irq			__vector_2
#define INT2_irq			__vector_3
#define TIMER2_COMP_irq		__vector_4
#define TIMER2_OVF_irq		__vector_5
#define TIMER1_CAPT_irq		__vector_6
#define TIMER1_COMPA_irq	__vector_7
#define TIMER1_COMPB_irq	__vector_8
#define TIMER1_OVF_irq		__vector_9
#define TIMER0_COMP_irq		__vector_10
#define TIMER0_OVF_irq		__vector_11
#define SPI_STC_irq			__vector_12
#define USART_RXC_irq		__vector_13
#define USART_UDRE_irq		__vector_14
#define USART_TXC_irq		__vector_15
#define ADC_irq				__vector_16
#define EE_RDY_irq			__vector_17
#define ANA_COMP_irq		__vector_18
#define TWI_irq				__vector_19
#define SPM_RDY_irq			__vector_20

//#define ISR(vector, ...)            \
   void vector (void) __attribute__ ((signal,interrupt)); \
   void vector (void)

#define sei()  __asm__ __volatile__ ("sei" ::)
#define cli()  __asm__ __volatile__ ("cli" ::)

#endif /* INTERRUPT_H_ */
