#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include <math.h>
#include "p2switches.h"
#define SW1 BIT0//switch1 is p1.3
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 | SW2 | SW3 | SW4)

extern int sans[],pacman[],tetris[],mario[];
extern int cont,cont2,secondSpeed,st,tet;
extern char state,switch_state_down,switch_state_down2,switch_state_down3,switch_state_down4, switch_state_changed;
