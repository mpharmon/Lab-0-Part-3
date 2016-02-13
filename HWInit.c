#ifndef XC_H_
#define XC_H_
#include <xc.h>
#endif

#ifndef HWINIT_H_
#define HWINIT_H_
#include "HWInit.h"
#endif

#define TRISx_INPUT 1;
#define TRISx_OUTPUT 0;

#define LATx_HIGH 1;
#define LATx_LOW 0;

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
