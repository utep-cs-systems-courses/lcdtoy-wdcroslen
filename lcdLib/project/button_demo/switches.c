#include <msp430.h>

#include "switches.h"

#include "led.h"

#include "buzzer.h"

#include "statemachines.h"

#include "soundStates.h"

//#include "soundStates.s"

int sans[] = {100,3405,3405,1700.3,0,2273,0,0,2408,0,2551,0,2863,0,3405,2863,2551,3822,3822,1700.3,0,2273,0,0,2408,0,2551,0,2863,0,3405,2863,2551,4050,4050,1700.3,0,2273,0,0,2408,0,2551,0,2863,0,3405,2863,2551,4290,4290,1700.3,0,2273,0,0,2408,0,2551,0,2863,0,3405,2863,2551};//,3405,3405,1700.3,0,2273,0,0,2408,0,2551,0,2863,0,3405,2863,2551,3822,3822,1700.3,0,2273,0,0,2408,0,2551,0,2863,0,3405,2863,2551,4050,4050,1700.3,0,2273,0,0,2408,0,2551,0,2863,0,3405,2863,2551,4290,4290,1700.3,0,2273,0,0,2408,0,2551,0,2863,0,3405,2863,2551};

int tetris[] = {0,3034,3034,0,4050,0,3822,0,3405,0,3034,3405,3822,0,4050,0,4545,4545,4545,0,4545,0,3822,0,3034,3034,3034,0,3405,0,3822,0,4050,4050,4050,0,4050,0/*Limit?*/,3822,0,3405,3405,3405,0,3034,3034,3034,3034,3822,3822,0,0,4545,4545,0,0,4545,4545,4545,0,0,0,/**/3405,3405,0,2863,0,2273,2273,2273,0,2551,0,2863,0,3034,3034,3034,0,0,3822,0,3034,3034,3034,0,3405,0,3822,0,4050,4050,4050,0,4050,0,3822,0,3405,3405,0,0,3034,3034,0,0,3822,3822,0,0,4545,4545,4545,0,4545,4545,4545,0,0};

int st,tet = 0;

int mario[] = {0};

int cont,cont2,secondSpeed = 0;

char state, switch_state_down, switch_state_down2, switch_state_down3,switch_state_down4, switch_state_changed; /* effectively boolean */

static char
switch_update_interrupt_sense()

{

  char p2val = P2IN;

  /* update switch interrupt to detect changes from current buttons */

  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */

  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */

  return p2val;

}

void switch_init()/* setup switch */

{

  P2REN |= SWITCHES;/* enables resistors for switches */

  P2IE = SWITCHES;/* enable interrupts from switches */

  P2OUT |= SWITCHES;/* pull-ups for switches */

  P2DIR &= ~SWITCHES;/* set switches' bits for input */

  //Need same logic for P2

  switch_update_interrupt_sense();

  led_update();

}
void switch_interrupt_handler()

{

  char p2val = switch_update_interrupt_sense();

  switch_state_down = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */

  switch_state_down2 = (p2val & SW2) ? 0 : 1;

  switch_state_down3 = (p2val & SW3) ? 0 : 1;

  switch_state_down4 = (p2val & SW4) ? 0 : 1;

  switch_state_changed = 1;

  // if(state == 12){

  //  state = 0;

  // }



  led_update();



  //int notes[] = {293, 293, 587};

  //Switch color and play tune with SW1

  if (switch_state_down){

    cont2 = 0;

    cont = ~cont; //global variable to turn off sound the next time you hit SW1

    state = 0;

    advanceSounds();

  }
  if (!switch_state_down){

    buzzer_set_period(0);

  }

  //dim lights with switch 3

  if (switch_state_down3){

    //advanceSounds(state);

    buzzer_set_period(0);

    if(green_on){

      P1REN = ~SWITCHES;

    }

    else{

      P1REN = 1;

    }

  }

  //undim lights if you arent pressing switch 3

  if (!switch_state_down3){

    P1REN = 0;

  }

  //4th state to make lights blink super fast

  if (switch_state_down4){

    cont2 = ~cont2;

    cont = 0;

    state_advance();

    newTune();

    state=0;

  }

  //alternate speeds every press

  if (!switch_state_down4){

    if(secondSpeed==1){

      secondSpeed = 0;

    }

    else{

      secondSpeed = 1;

    }

  }

  int get_elem(int song[]){

    return song[state];

  }

}
