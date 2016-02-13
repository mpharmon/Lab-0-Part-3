#ifndef XC_H_
#define XC_H_
#include <xc.h>
#endif

#ifndef HWINIT_H_
#define HWINIT_H_
#include "HWInit.h"
#endif

#define TRISx_INPUT 1
#define TRISx_OUTPUT 0

#define LATx_HIGH 1
#define LATx_LOW 0

#define CNPUx_ACTIVE 1
#define CNPUx_INACTIVE 0

void initLEDs(){
  // Set tristate registers to output for LED's
  TRISDbits.TRISD0 = TRISx_OUTPUT;
  TRISDbits.TRISD1 = TRISx_OUTPUT;
  TRISDbits.TRISD2 = TRISx_OUTPUT;
  
  // Set Latch to Low (Off)
  LATDbits.LATD0 = LATx_LOW;
  LATDbits.LATD1 = LATx_LOW;
  LATDbits.LATD2 = LATx_LOW;
}

void initSWs(){
  // Set Tristate Registers to Input for Switches
  TRISDbits.TRISD6 = TRISx_INPUT;
  // Enable Pull-Up Resistor
  CNPUDbits.CNPUD6 = CNPUx_ACTIVE;
  // Enable Change Notification on Port
  CNCONDbits.ON = 1;
  // Enable Change Notification on Pin
  CNENDbits.CNIED6 = 1;
  // Turn Flag Down
  IFS1bits.CNDIF = 0;
  // Enable Interrupt
  IEC1bits.CNDIE = 1;
  // Set Priority (Default)
  IPC8bits.CNIP = 1;
}