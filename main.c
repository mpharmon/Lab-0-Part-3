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

typedef enum STATEenum{
  state1,
  state2,
  state3
}STATE;

#define LATx_HIGH 1;
#define LATx_LOW 0;

#define LED0 c
#define LED1 LATDbits.LATD1
#define LED2 LATDbits.LATD2

#define PORTx_HIGH 1
#define PORTx_LOW 0

volatile STATE FSM = state1;

int main(void){
  SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
  enableInterrupts();                   //This function is necessary to use interrupts.initLEDs();
  initSWs();
  initLEDs();
  initTimer();
  while(1){
    switch(FSM){
      case state1:
        LATDbits.LATD0 = LATx_HIGH;
        LATDbits.LATD1 = LATx_LOW;
        LATDbits.LATD2 = LATx_LOW;
        break;
      case state2:
        LATDbits.LATD0 = LATx_LOW;
        LATDbits.LATD1 = LATx_HIGH;
        LATDbits.LATD2 = LATx_LOW;
        break;
      case state3:
        LATDbits.LATD0 = LATx_LOW;
        LATDbits.LATD1 = LATx_LOW;
        LATDbits.LATD2 = LATx_HIGH;
        break;
    }
  }
  return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
  PORTD;// Needed For Some Reason...
  IFS1bits.CNDIF = 0; // Turn Flag Down
  if(PORTDbits.RD6 == PORTx_LOW){// Button Pressed
    TMR1 = 0;
    T1CONbits.ON = 1;
  }else if(PORTDbits.RD6 == PORTx_HIGH){// Button Released
    if(T1CONbits.ON == 1){
      T1CONbits.ON = 0;
      TMR1 = 0;
      if(FSM == state1)FSM = state2;
      else if(FSM == state2)FSM = state3;
      else if(FSM == state3)FSM = state1;
    }else{
      if(FSM == state1)FSM = state3;
      else if(FSM == state2)FSM = state1;
      else if(FSM == state3)FSM = state2;
    }
  };
}

void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt(void){
  IFS0bits.T1IF = 0; // Turn Interrupt Flag Off
  T1CONbits.ON = 0; // Stop Timer
  TMR1 = 0; // Reset Timer Register
}