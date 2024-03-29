/**********************************************************************/
/*                                                                    */
/*         Lecture: Programmation for Embedded Systems				  */
/*         Author:  Victor Rocha                                      */
/*																	  */
/*	This program controls a single LED with Pulse-Width Modulation	  */
/*																	  */
/**********************************************************************/

#include <16F877A.h>

#device adc=10

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES HS                    	//High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                 	//No Power Up Timer
#FUSES NOPROTECT             	//Code not protected from reading
#FUSES NODEBUG               	//No Debug mode for ICD
#FUSES BROWNOUT              	//Reset when brownout detected
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                 	//No EE protection
#FUSES NOWRT                 	//Program memory not write protected
#FUSES RESERVED              	//Used to set the reserved FUSE bits

#use delay(clock=20000000)


void main()
{
   //Microcontroller definitions
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_DIV_32);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_1,0,1);
   setup_ccp1(CCP_PWM);
   set_pwm1_duty(1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

	int Digital;
   
	while(1)
	{
        set_adc_channel(0);
        Digital = read_adc();
        delay_us(20);
        set_pwm1_duty(Digital);    
	}
}
