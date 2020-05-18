#include <msp430.h>
#include "statemachines.h"
#include "lcdutils.h"
#include "lcdx.h"



void

__interrupt_vec(WDT_VECTOR) WDT(){ /* 250 interrupts/sec */
  
  static char blink_count = 0;
  // static char sleep = 0;
  tet = tetris[state];
  redrawScreen = 1;
  if(++sleep == 250){
    clearScreen(COLOR_BLACK);
    
    redrawScreen=0;
    // sleep =0;
  }
  if (++blink_count == 200){
    //  clearScreen(COLOR_PURPLE);
    // redrawScreen=0;
    method();
    blink_count=0;
    if(switch_state_down){
      redrawScreen = 1;
      method();
    }
  }




  //advance the lights at different speeds
 
}
