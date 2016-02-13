#ifndef XC_H_
#define XC_H_
#include <xc.h>
#endif
        
#ifndef TIMERINIT_H_
#define TIMERINIT_H_
#include "timerInit.h"
#endif

#define PRESCALE_256 3

void initTimer(){
  TMR1 = 0; // Initilaize Timer Register
  PR1 = 39062; // Initialize Period Register
  T1CONbits.TCKPS = PRESCALE_256; // Prescaler to 256
  IEC0bits.T1IE = 1; // Timer Enabled
  IFS0bits.T1IF = 0; // Interrupt Flag Down
  IPC1bits.T1IP = 7; // Default Timer Priority
  T1CONbits.ON = 1; // Turn Timer On
}