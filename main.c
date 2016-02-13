#ifndef XC_H_
#define XC_H_
#include <xc.h>
#endif

#ifndef HWINIT_H_
#define HWINIT_H_
#include "HWInit.h"
#endif

#ifndef TIMERINIT_H_
#define TIMERINIT_H_
#include "timerInit.h"
#endif

#ifndef CONFIG_H_
#define CONFIG_H_
#include "config.h"
#endif

#ifndef INTERRUPT_H_
#define INTERRUPT_H_
#include "interrupt.h"
#endif

#include <sys/attribs.h>

typedef enum STATEEnum{
  state1,
  state2,
  state3
}STATE;

#define LATx_HIGH 1;
#define LATx_LOW 0;

#define LED1 LATDbits.LATD0
#define LED2 LATDbits.LATD1
#define LED3 LATDbits.LATD2

volatile STATE FSM = state1;

int main(void){
  SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
  enableInterrupts();                   //This function is necessary to use interrupts.initLEDs();
  initLEDs();
  initTimer();
  while(1){
    switch(FSM){
      case state1:
        LED1 = LATx_HIGH;
        LED2 = LATx_LOW;
        LED3 = LATx_LOW;
        break;
      case state2:
        LED1 = LATx_LOW;
        LED2 = LATx_HIGH;
        LED3 = LATx_LOW;
        break;
      case state3:
        LED1 = LATx_LOW;
        LED2 = LATx_LOW;
        LED3 = LATx_HIGH;
        break;
    }
  }
}

void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt(void){
  IFS0bits.T1IF = 0; // Turn Interrupt Flag Off
  if(FSM == state1)FSM = state2;
  else if(FSM == state2)FSM = state3;
  else if(FSM == state3)FSM = state1;
}