/**********************************************************************/
/*                                                                    */
/*         Lecture: Programmation for Embedded Systems				  */
/*         Author:	Victor Rocha                                      */
/*																	  */
/*	This is a chronometer with interruption made for PIC 16F28A       */
/*                                                                    */
/**********************************************************************/

#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES INTRC                    //Internal RC Osc
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES MCLR                     //Master Clear pin enabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES RESERVED                 //Used to set the reserved FUSE bits

#Define A output_high(PIN_A0)
#Define B output_high(PIN_A1)
#Define C output_high(PIN_A2)
#Define D output_high(PIN_A3)
#Define E output_high(PIN_B3)
#Define F output_high(PIN_B1)
#Define G output_high(PIN_B2)
#Define nA output_low(PIN_A0)
#Define nB output_low(PIN_A1)
#Define nC output_low(PIN_A2)
#Define nD output_low(PIN_A3)
#Define nE output_low(PIN_B3)
#Define nF output_low(PIN_B1)
#Define nG output_low(PIN_B2)
#use delay(clock=4000000)

int contador,estadoPause;

#int_RB
void  RB_isr() 
{

 //Reset
 while(input(PIN_B6))
 {
  contador=0;
  nG;
  A;B;C;D;E;F;
 }

 //PlayPause
 if(input(PIN_B7))
	estadoPause = !estadoPause;
   
 //VerificaPlayPause
 if((estadoPause==1) && input(PIN_B6)) 
	nG;A;B;C;D;E;F;

}

void Output(int contador);

void main()
{
	//Microcontroller setup
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_ccp1(CCP_OFF);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   //enable_interrupts(INT_RTCC);
   enable_interrupts(INT_RB);
   enable_interrupts(GLOBAL);

   // INTOSC_OSC_NOCLKOUT;
   // Setup_Oscillator parameter not selected from Intr Oscillator Config tab
   // TODO: USER CODE!!
 
  contador=0;
  estadoPause=1;
  A;B;C;D;E;F;G;
  delay_ms(1000);
  nA;nB;nC;nD;nE;nF;nG;
  
  while(1)
  {
   if (!estadoPause)
   {
    contador++;
    if (contador>9) {contador=0;};
    Output(contador);
    delay_ms(1000);
   } 
  }
}

void Output(int contador)
{
  switch (contador) {
    case 0:A;B;C;D;E;F;nG;
           break;
    case 1:B;C;nA;nD;nE;nF;nG;
           break;
    case 2:A;B;G;E;D;nC;nF;
           break;
    case 3:A;B;G;C;D;nE;nF;
           break;
    case 4:F;G;B;C;nA;nD;nE;
           break;
    case 5:A;F;G;C;D;nB;nE;
           break;
    case 6:A;F;G;E;C;D;nB;
           break;
    case 7:A;B;C;nD;nE;nF;nG;
           break;
    case 8:A;B;C;D;E;F;G;
           break;
    case 9:A;B;C;F;G;nD;nE;
           break;
  }
}

