#include <msp430.h>
#include "statemachines.h"
//#include "led.h"
#include "lcdx.h"
//#include "assembly.h"
/*
char toggle_red()/* always toggle! 
{
  char changed = 0;
  if (green_on && red_on) {
    red_on = 0;
    green_on = 0;
    changed = 1;
  }
  else if (green_on) {
    red_on = 1;
    green_on = 0;
    changed = 1;
  }
  return changed;
  /* always changes an led */
//}
/*
char toggle_green()/* only toggle green if red is on!  
{
  char changed = 0;
  if (!red_on) {
    green_on ^= 1;
    changed = 1;
  }
  if (red_on && green_on){
    green_on = 0;
    red_on = 0;
    changed = 1;
  }
  else if (red_on){
    green_on = 1;
    changed = 1;
  }
  return changed;
}
//creates the sound array and updates the state to continue through the tune

*/
void advanceSounds(int st){
  buzzer_set_period(sans[st]);
  state++;
}

void newTune(int st){
 buzzer_set_period(tetris[state]);
 state++;
}
/*
void state_advance(){/* alternate between toggling red & green */ 
/* char changed = 0;
  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }
  led_changed = changed;
  led_update();
}
*/
