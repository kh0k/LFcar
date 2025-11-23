#include "stm32f10x.h"
#include "key.h"
#include "pwm.h"
#include "mmgj.h"
#include "oled.h"
#include "delay.h"
#include "encoder.h"

/********************************************/

#define value_len 10

int16_t EvalueA = 0, EvalueB = 0;

int16_t SPDA=0,SPDB=0;

//uint8_t cnt=1;


/********************************************/

void loop_car(void);

/********************************************/

int main(void) {

	SystemInit();
	delay_init();
	KEY_SET();
	PWM_SET();
	OLED_SET();
	Encoder_PA_SET(&EvalueA, &EvalueB);
	OLED_Refresh();
	delay_ms(1000);

	HIGH(STBY);

	while (1) {
			loop_car();
			delay_ms(100);
	}
}

/********************************************/

void loop_car(void) {
	Set_PWMA(SPDA);
	Set_PWMB(SPDB);
	OLED_ShowString(6, 12, "SPDA", 12, 1);
	OLED_ShowString(70, 12, "SPDB", 12, 1);
	OLED_ShowNum(6, 12+10,SPDA,4,12,1);
	OLED_ShowNum(70,12+10,SPDB,4,12,1);
	OLED_ShowString(6, 12+20, "ECDA", 12, 1);
	OLED_ShowString(70,12+20, "ECDB", 12, 1);
	OLED_ShowNum(6, 12+30, EvalueA,4,12,1);
	OLED_ShowNum(70,12+30,EvalueB,4,12,1);

//	if (cnt)
//		OLED_DrawBoxLine(0,8,63,63,1);
//	else
//		OLED_DrawBoxLine(64,8,127,63,1);
//
//	if (KEY_Scan(1))
//		cnt=1-cnt;

	if (KEY_Scan(2)){
		SPDA+=1000;
		if (SPDA>=7199)
			SPDA-=7000;
		SPDB=SPDA;
	}
	if (KEY_Scan(3)){
		if ((SPDA/100)%10==9)
			SPDA-=900;
		else
			SPDA+=100;
		SPDB=SPDA;
	}
	if (KEY_Scan(4)){
		if ((SPDA/10)%10==9)
			SPDA-=90;
		else
			SPDA+=10;
		SPDB=SPDA;
	}

	OLED_Refresh();
	OLED_ClearRF();
}
