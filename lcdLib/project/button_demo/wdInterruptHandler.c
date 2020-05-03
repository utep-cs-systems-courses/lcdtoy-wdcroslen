#include <msp430.h>

#include "statemachines.h"

#include "switches.h"



void

__interrupt_vec(WDT_VECTOR) WDT(){ /* 250 interrupts/sec */

  static char blink_count = 0;

  //advance sounds

  st = sans[state];

  tet = tetris[state];

  if (cont && ++blink_count == 33) {

    if (state >64){

      state = 0;

    }

    advanceSounds(state);

    blink_count = 0;

  }

  /* if (cont2 && ++blink_count == 30) {

     if (state > 64){

      state = 0;

    }

    newTune(state);

    blink_count = 0;

    } */

  //advance the lights at different speeds

  if(switch_state_down4) {

    if(secondSpeed==1){

      if(++blink_count == 20){

	state_advance();

	newTune(state);

	blink_count = 0;

	if (state >120){

	  state = 0;



	}

      }

    }

    else{

      if(++blink_count == 100){

	state_advance();

	blink_count = 0;

      }

    }

  }

}
