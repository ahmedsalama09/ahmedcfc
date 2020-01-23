/*
 * timer.c
 *
 * Created: 20-Jan-20 4:57:25 PM
 *  Author: ahmed
 */ 
#include "timers.h"

static En_timer2perscaler_t T2_PSC_READ;
static En_timer1perscaler_t T1_PSC_READ;
static En_timer0perscaler_t T0_PSC_READ;


void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t en_OC0,En_timer0perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, En_timer0Interrupt_t en_interruptMask)
{
	/*First set the FOC0 bit*/
	SET_BIT(TCCR0,FOC0);
	
	/*Choosing operation mode */
	TCCR0 = (TCCR0 & 0xB7 ) | (en_mode);
	
	/*choosing compare match mode*/
	TCCR0 = (TCCR0 & 0xCF) |   (en_OC0);
	
	/*choosing prescalled value*/
	TCCR0 = (TCCR0 & 0xF8)	| (en_prescal);
	T0_PSC_READ = en_prescal;
	
	/*choose init value of counting*/
	TCNT0 = u8_initialValue;
	
	/*write compare register*/
	OCR0 = u8_outputCompare;
	
	/*choose to enable irq or not*/
	TIMSK = (TIMSK & 0xFC) | (en_interruptMask);	
}

void timer0Set(uint8_t u8_value){
	
	/*set the timerCnt value*/
	TCNT0 = u8_value;
}

uint8_t timer0Read(void){
	
	/*read the counter current value*/
	return TCNT0;
}

void timer0Start(void){
	
	/*write the prescaller value to the timer*/
	TCCR0 = (TCCR0 & 0xF8)	| (T0_PSC_READ);
	
	/*start count from 0*/
	TCNT0 =0;
}

void timer0Stop(void){
	
	/*disable the prescaller by clearing the first 3BITS*/
	TCCR0 &= ~(0x05);
}

void timer0DelayMs(uint16_t u16_delay_in_ms){
	
	uint16_t u16_cont=0;
	uint8_t u8_outCMP=F_CPU/64000;
	
	timer0Init(T0_COMP_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,u8_outCMP,T0_POLLING);
	
	for(u16_cont=0;u16_cont<u16_delay_in_ms;u16_cont++){
		
		while(TCNT0 < u8_outCMP);
		TCNT0=0;
	}
}

void timer0DelayUs(uint32_t u32_delay_in_us){
	
	uint32_t u32_cont=0;
	
	timer0Init(T0_PRESCALER_NO,T0_OC0_DIS,T0_PRESCALER_NO,0,0,T0_POLLING);
		
	for(u32_cont=0;u32_cont<u32_delay_in_us;u32_cont++){
		
		while(TCNT0 < 1);
		TCNT0=0;
		while(TCNT0 < 1);
		TCNT0 =0;
		//if(1);
	}
	
	/*uint16_t u16_cont=0;
	uint8_t u8_outCMP=F_CPU/64000;
	
	timer0Init(T0_COMP_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,u8_outCMP,T0_POLLING);
	
	for(u16_cont=0;u16_cont<(u32_delay_in_us/1000);u16_cont++){
		
		while(TCNT0 < u8_outCMP);
		TCNT0=0;
	}*/
}

void timer0SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency){
	
	
	
	
}


void timer1Init(En_timer1Mode_t en_mode,En_timer1OC_t en_OC,En_timer1perscaler_t en_prescal, uint16_t u16_initialValue, uint16_t u16_outputCompareA, uint16_t u16_outputCompareB,uint16_t u16_inputCapture, En_timer1Interrupt_t en_interruptMask){
	
	/* set the two compare units to be at normal mode*/
	SET_BIT(TCCR1A,FOC1A);
	//SET_BIT(TCCR1A,FOC1B);
	
	/*Choosing operation mode */
	TCCR1 = (TCCR1 & 0xFFE7 ) | (en_mode);
	
	/*choosing OC mode*/
	TCCR1 = (TCCR1 & 0x3FFF) |  (en_OC);
	
	/*choosing prescaller*/
	TCCR1 = (TCCR1 & 0xFFF8) |  (en_prescal);
	T1_PSC_READ = en_prescal;
	
	/*write the initial value at TCNT1*/
	TCNT1 = u16_initialValue;
	
	/*write the output compare value*/
	OCR1A = u16_outputCompareA;
	
	/*write the output compare at B*/
	OCR1B = u16_outputCompareB;
	
	/*input compare A value*/
	ICR1 = u16_inputCapture;
	
	/*choose to enable irq or not*/
	TIMSK = (TIMSK & 0xC3) | (en_interruptMask);
}

/* Set the timer to the value you want to start from by writing to TCNT1*/
void timer1Set(uint16_t u16_value){
	
	/*the the timer to the value*/
	TCNT1 = u16_value;
}

/*reading the counter value at running time*/
uint16_t timer1Read(void){
	
	/*return the timer cnt value*/
	return TCNT1;
}

/*starting the timer by writing the psc value to it */
void timer1Start(void){
	
	/*write the prescaller value to the timer*/
	TCCR1 = (TCCR1 & 0xFFF8) |  (T1_PSC_READ);
	
	/*reinitialize it*/
	TCNT1 =0;
}

/*stop the timer by disabling the clock*/
void timer1Stop(void){
	
	/*write the pscalling bit to zero*/
	TCCR1 &= ~(0x0005);
	
	/*reinitialize it*/
	TCNT1 =0;
}

/*delay in MS function*/

/*Function to delay by ms*/
void timer1DelayMs(uint16_t u16_delay_in_ms){
	
		uint16_t u16_cont=0;
		
		uint16_t u16_outCMP=F_CPU/64000;
		
		/*TIMER1 Set:	Compare mode top	normal mode		Prescale 64		init value 0
		cmp at A			use polling		no irq*/
		timer1Init(T1_NORMAL_MODE,T1_OC1_DIS,T1_PRESCALER_64,0,0,0,0,T1_POLLING);
		
		for(u16_cont=0;u16_cont<u16_delay_in_ms;u16_cont++){
			
			while(TCNT1 < u16_outCMP);
			TCNT1=0;
		}
}

/*function that takes number of MicroSec to delay*/
void timer1DelayUs(uint32_t u32_delay_in_us){
	
	/*conter value to count each microSecond*/
	uint32_t u32_cont =0;
	
	/*init the timer*/
	timer1Init(T1_NORMAL_MODE,T1_OC1_DIS,T1_PRESCALER_NO,0,0,0,0,T1_POLLING);
	
	/*for loop to get the right value*/
	for(u32_cont=0;u32_cont<u32_delay_in_us;u32_cont++){
		
		/*compare the value with the first CNT to get microsecond*/
		while(TCNT1<1);
		TCNT1 = 0;
	}
}

void timer1SwPWM(uint8_t u8_dutyCycle,uint8_t u8_frequency){
	
	/*uint32_t u32_delayVal = 10000/u8_frequency;
	uint32_t u32_dutyVal  = u32_delayVal * u8_dutyCycle/100;
	
	uint32_t u32_delayTicks;
	
	Led_Init(LED_0);
	timer1Init(T1_NORMAL_MODE,T1_OC1_DIS,T1_PRESCALER_NO,0,0,0,0,T1_POLLING);
	
	Led_On(LED_0);
	for(u32_delayTicks = 0; u32_delayTicks< u32_delayVal ; u32_delayTicks++){
		
		
		if(u32_delayTicks > u32_dutyVal){
		Led_Off(LED_0);
		}
		while(TCNT1 < 1600);
		TCNT1 =0;
	}*/
}

void timer2Init(En_timer2Mode_t en_mode,En_timer2OC_t en_OC,En_timer2perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, uint8_t u8_assynchronous, En_timer2Interrupt_t en_interruptMask){
	
	/*choose the operating mode*/
	TCCR2 &= (TCCR2 & 0xB7) | (en_mode) ;
	
	/*choose compare mode*/
	TCCR2 &= (TCCR2 & 0xCF) | (en_OC);
	
	/*choose prescaller*/
	TCCR2 &= (TCCR2 & 0xF8) | (en_prescal);
	
	/*write it to be read back*/
	T2_PSC_READ = en_prescal;
	
	/*choose counting init value*/
	TCNT2 = u8_initialValue;
	
	/*write outputCMP value*/
	OCR2 = u8_outputCompare;
	
	/*write Assynch. Value*/
	ASSR = u8_assynchronous;
	
	/*write IRQ Status*/
	TIMSK = (0x3F & TIMSK) | (en_interruptMask);
}

void timer2Set(uint8_t u8_a_value){

	/*write the value to timer2 cnt*/
	TCNT2 = u8_a_value;	
}

/*return the timer2 cnt value*/
uint8_t timer2Read(void){
	
	return TCNT2;
}

/*clock the timer with the last PSC value*/
void timer2Start(void){
	
	TCCR2 = (TCCR2 & 0xF8)	| (T2_PSC_READ);
	
	/*reinitialize it*/
	TCNT2 = 0;
}

/*Stop the Current clock source*/
void timer2Stop(void){
	
	/*clear TCCR2*/
	TCCR2 = (TCCR2 & 0xF8);
}

void timer2DelayMs(uint16_t u16_delay_in_ms){
	
	uint16_t u16_cont=0;
		
	uint8_t u8_outCMP=F_CPU/64000;
		
	/*TIMER2 Set:normal mode		Prescale 64		init value 0
	Re_init at u8_outCMP			use polling		no irq*/
	timer2Init(T2_NORMAL_MODE,T2_OC2_DIS,T2_PRESCALER_64,0,0,0,T2_POLLING);
		
	for(u16_cont=0;u16_cont<u16_delay_in_ms;u16_cont++){
			
		while(TCNT2 < u8_outCMP);
		TCNT2=0;
		}
}

void timer2DelayUs(uint32_t u32_delay_in_us){

	/*conter value to count each microSecond*/
	uint32_t u32_cont =0;
		
	/*init the timer*/
	timer2Init(T2_NORMAL_MODE,T2_OC2_DIS,T1_PRESCALER_NO,0,0,0,T2_POLLING);
		
	/*for loop to get the right value*/
	for(u32_cont=0;u32_cont<u32_delay_in_us;u32_cont++){
			
			/*compare the value with the first CNT to get microsecond*/
		while(TCNT2<1);
		TCNT2 = 0;
		}
}