/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

//#define M_PI 3.14159265358979323846
#include <libTimer.h>
#include "lcdx.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include <math.h>
//#include "p2switches.h"

int sans[] = {0};
int tetris[] = {0,3034,3034,0,4050,0,3822,0,3405,0,3034,3405,3822,0,4050,0,4545,4545,4545,0,4545,0,3822,0,3034,3034,3034,0,3405,0,3822,0,4050,4050,4050,0,4050,0/*Limit?*/,3822,0,3405,3405,3405,0,3034,3034,3034,3034,3822,3822,0,0,4545,4545,0,0,4545,4545,4545,0,0,0,/**/3405,3405,0,2863,0,2273,2273,2273,0,2551,0,2863,0,3034,3034,3034,0,0,3822,0,3034,3034,3034,0,3405,0,3822,0,4050,4050,4050,0,4050,0,3822,0,3405,3405,0,0,3034,3034,0,0,3822,3822,0,0,4545,4545,4545,0,4545,4545,4545,0,0};

int st,tet = 0;

int mario[] = {0};

int cont,cont2,secondSpeed = 0;

char state, switch_state_down, switch_state_down2, switch_state_down3,switch_state_down4, switch_state_changed;

/* Dimensions = 160 x 128 */
/*TETRIS = 20 x 10 blocks */
/*140 x 70 */
/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  p2sw_init(15);
  switch_init();
  buzzer_init();
  //or_sr(0x8);/* GIE (enable interrupts) */
  // state =0;
  // WDT();
  //method();
  enableWDTInterrupts();
  // method();
  clearScreen(COLOR_GOLD);
  drawString5x7(20,20,"Goodbye!",COLOR_BLACK,COLOR_GOLD);
  method();
  or_sr(0x18);
  
}

static char
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */

  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */

  return p2val;

}

void
switch_init()/* setup switch */
{
  P2REN |= SWITCHES;/* enables resistors for switches */
  P2IE = SWITCHES;/* enable interrupts from switches */
  P2OUT |= SWITCHES;/* pull-ups for switches */
  P2DIR &= ~SWITCHES;/* set switches' bits for input */

  switch_update_interrupt_sense();
}

void

switch_interrupt_handler()

{

  char p2val = switch_update_interrupt_sense();
  // Determine which button is pressed down

  switch_state_down = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */

  switch_state_down2 = (p2val & SW2) ? 0 : 1; /* 0 when SW2 is up */

  switch_state_down3 = (p2val & SW3) ? 0 : 1; /* 0 when SW3 is up */

  switch_state_down4 = (p2val & SW4) ? 0 : 1; /* 0 when SW4 is up */

}


void method(){
  clearScreen(COLOR_BLUE);

  drawString5x7(10,10, "switches:", COLOR_GREEN, COLOR_BLUE);
  int a = 1;
  int blink = 0;
  while (a) {
     char p2val = P2IN;
     switch_state_down = (p2val & SW1) ? 0 : 1;
     switch_state_down2 = (p2val & SW2) ? 0 : 1;
     switch_state_down3 = (p2val & SW3) ? 0 : 1;
     switch_state_down4 = (p2val & SW4) ? 0 : 1;
    u_int switches = p2sw_read(), q;
    char str[5];
     unsigned char j = 0;
     unsigned char i =0;
     
    if(switch_state_down && switch_state_down4){
       clearScreen(COLOR_BLACK);
       // drawString5x7(30,20, "cat sucks", COLOR_BLACK, COLOR_WHITE);
   drawString5x7(45,5, "TETRIS", COLOR_PURPLE, COLOR_BLACK);
  
   //unsigned char j = 0;
   //unsigned char i =0;
 /*Border*/
  
 /*I-block Cyan Piece */
 fillRectangle(65,70, 10, 10, COLOR_PINK); 
 fillRectangle(55,80, 10, 10, COLOR_PINK);
 fillRectangle(65,80, 10, 10, COLOR_PINK);
 fillRectangle(75,80, 10, 10, COLOR_PINK);
  for (i=45; i<= 85; i=i+10){
    for(j=0; j<10; j++){
      drawPixel(i,80+j,COLOR_BLACK);
      if (i<85){
      drawPixel(j+i,80,COLOR_BLACK);
	}
    }
  }
 /**/
 
  }

   else if(switch_state_down){
      clearScreen(COLOR_RED);
      str[0] = 'Y';
      str[1] = 'e';
      str[2] = 'e';
      str[3] = 't';
       /*I-block Cyan Piece */
 fillRectangle(19,90, 10, 10, COLOR_CYAN); 
 fillRectangle(29,90, 10, 10, COLOR_CYAN);
 fillRectangle(39,90, 10, 10, COLOR_CYAN);
 fillRectangle(49,90, 10, 10, COLOR_CYAN);
  for (i=19; i<= 59; i=i+10){
    for(j=0; j<10; j++){
      drawPixel(i,90+j,COLOR_BLACK);
      if (i<59){
      drawPixel(j+i,90,COLOR_BLACK);
      drawPixel(j+i,100,COLOR_BLACK);
      }
    }
  }

      drawString5x7(20,20, str, COLOR_BLACK, COLOR_RED);
    }
   else if(switch_state_down2){
      clearScreen(COLOR_ORANGE);
      str[0] = 'F';
      str[1] = 'e';
      str[2] = 'e';
      str[3] = 't';
      fillRectangle(69,40, 10, 10, COLOR_YELLOW); 
      fillRectangle(69,50, 10, 10, COLOR_YELLOW);
      fillRectangle(79,40, 10, 10, COLOR_YELLOW);
      fillRectangle(79,50, 10, 10, COLOR_YELLOW);
      for(i=0; i<30; i+=10){
	for(j=0; j<20; j+=1){
	  drawPixel(69+i,40+j,COLOR_BLACK);
	  drawPixel(69+j,40+i,COLOR_BLACK);
	}
      }
      

  
      drawString5x7(20,20, str, COLOR_BLACK, COLOR_ORANGE);
      // buzzer_set_period(tetris[tet]);
      // tet++;
    }
   else if(switch_state_down3){
      clearScreen(COLOR_YELLOW);
      str[0] = 'B';
      str[1] = 'e';
      str[2] = 'a';
      str[3] = 't';
      fillRectangle(59,110, 10, 10, COLOR_ORANGE); 
 fillRectangle(69,110, 10, 10, COLOR_ORANGE);
 fillRectangle(79,110, 10, 10, COLOR_ORANGE);
 fillRectangle(79,100, 10, 10, COLOR_ORANGE);
  for (i=59; i<= 79; i=i+10){
    for(j=0; j<10; j++){
      drawPixel(i,110+j,COLOR_BLACK);
      if (i<79){
      drawPixel(j+i,110,COLOR_BLACK);
	}
    }
  }
  /*L-block Orange Piece*/

   for(i = 0; i<20; i++){
    drawPixel(79,100 +i,COLOR_BLACK);
    drawPixel(89,100 +i,COLOR_BLACK);
  }
   for(i = 0; i<10; i++){
    drawPixel(79+i,100,COLOR_BLACK);
    drawPixel(79+i,110,COLOR_BLACK);
    drawPixel(59+i,120,COLOR_BLACK);
    drawPixel(69+i,120,COLOR_BLACK);
    drawPixel(79+i,120,COLOR_BLACK); 
  }
      blink = 0;
      state = 0;


/********DRAW TRIANGLE **********/
/*  for (i = 0; i <= 15; i+=1){
    u_char l = 15-i;
    u_char r = 15;
    for(j=l; j <=r; j+=1){
      drawPixel(30-j,30-i,COLOR_RED);
      drawPixel(j+30,30-i,COLOR_RED);
      drawPixel(j+30,i+30,COLOR_RED);
      drawPixel(30-j,i+30,COLOR_RED);
    }
  }
*/

      
      drawString5x7(20,20, str, COLOR_BLACK, COLOR_YELLOW);
    }
   else if(switch_state_down4){
      clearScreen(COLOR_GREEN);
      str[0] = 'M';
      str[1] = 'e';
      str[2] = 'a';
      str[3] = 't';
 fillRectangle(49,50, 10, 10, COLOR_PURPLE); 
 fillRectangle(49,40, 10, 10, COLOR_PURPLE);
 fillRectangle(59,40, 10, 10, COLOR_PURPLE);
 fillRectangle(59,30, 10, 10, COLOR_PURPLE);
  for (i=49; i<= 59; i=i+10){
    for(j=0; j<10; j++){
      drawPixel(i,40+j,COLOR_BLACK);
      if (i<59){
      drawPixel(j+i,40,COLOR_BLACK);
	}
    }
  }
  /*z-block Green Piece*/

   for(i = 0; i<20; i++){
    drawPixel(59,30 +i,COLOR_BLACK);
    drawPixel(69,30 +i,COLOR_BLACK);
    drawPixel(49,40 +i,COLOR_BLACK);
    drawPixel(59,40 +i,COLOR_BLACK);
  }
   for(i = 0; i<10; i++){
    drawPixel(59+i,30,COLOR_BLACK);
    drawPixel(59+i,40,COLOR_BLACK);
    drawPixel(49+i,60,COLOR_BLACK);
    drawPixel(49+i,50,COLOR_BLACK);
    drawPixel(59+i,50,COLOR_BLACK); 
  }

      blink = 0;
      drawString5x7(20,20, str, COLOR_BLACK, COLOR_GREEN);
    }
   if(switch_state_down && switch_state_down2){
      clearScreen(COLOR_BLACK);
      or_sr(0x10);
      
      and_sr(~10);
    }
   if(switch_state_down3 && switch_state_down2){
      clearScreen(COLOR_BLACK);
      a=0;
    }

   if (!switch_state_down){
	buzzer_set_period(0);
      }
   if(switch_state_down4 && ++blink == 2){// && ++blink ==20){
      cont2 = ~cont2;
      cont = 0;
      //state_advance();
      //state++;
  
      
      //newTune();
      blink =0 ;
   }

   if(++blink==2){
     buzzer_set_period(tetris[state]);
     state++;
     if (state > 120){
	state = 0;
     }
     blink = 0;
   }
    //alternate speeds every press
    /*if (!switch_state_down4){
      if(secondSpeed==1){
	secondSpeed = 0;
      }
      else{
	secondSpeed = 1;
      }
    } */

    // if(switch_state_down4 && ++blink ==20){
    // newTune();
    // }
   // CCR0 += 50000;
   /* if(++blink == 20){
     // newTune();
     state++;
     clearScreen(COLOR_BLUE);
   }
   */
    str[4] = 0;
  }
}
  /*
   clearScreen(COLOR_YELLOW);
  /********DRAW TRIANGLE **********/
  /* for (i = 0; i <= 15; i+=1){
    u_char l = 15-i;
    u_char r = 15;
    for(j=l; j <=r; j+=1){
      drawPixel(30-j,30-i,COLOR_RED);
      drawPixel(j+30,30-i,COLOR_RED);
      drawPixel(j+30,i+30,COLOR_RED);
      drawPixel(30-j,i+30,COLOR_RED);
    }
  }
  /*********************/

  /*
 for(i=0;i<=10;i++){
    drawPixel(50+i,10+50,COLOR_BLUE);
    drawPixel(10+50,i+50,COLOR_BLUE);
    drawPixel(50,i+50,COLOR_BLUE);
    drawPixel(i+50,50,COLOR_BLUE);
  }
 // fillRectangle(50,50, 9, 10, COLOR_BLUE); 
 for(i=0;i<=10;i++){
    drawPixel(54+i,10+46,COLOR_BLUE);
    drawPixel(10+54,i+46,COLOR_BLUE);
    drawPixel(54,i+46,COLOR_BLUE);
    drawPixel(i+54,46,COLOR_BLUE);
  }
 for(i=0; i<=4;i++){
   drawPixel(50+i,60-i,COLOR_BLUE);//BL
   drawPixel(60+i,60-i,COLOR_BLUE);//BR
   drawPixel(50+i,50-i,COLOR_BLUE);//TL
   drawPixel(60+i,50-i,COLOR_BLUE);//TR
 }
 drawString5x7(38,20, "Cat Sucks!", COLOR_BLACK, COLOR_WHITE);*/
  //}
