/*
 * req9.h
 *
 * Created: 18-Jan-20 2:29:30 PM
 *  Author: ahmed
 */ 
typedef enum state_machine{
	GO,
	STOP,
	GETREADY,
	GO1
	}state_machine;
	
void app_Ledstate(state_machine en_machine);
void app_ledcycle(void);
