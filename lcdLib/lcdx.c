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

int sans[] = {100,3405,3405,1700.3,0,2273,0,0,2408,0,2551,0,2863,0,3405,2863,2551,3822,3822,1700.3,0,2273,0,0,2408,0,2551,0,2863,0,3405,2863,2551,4050,4050,1700.3,0,2273,0,0,2408,0,2551,0,2863,0,3405,2863,2551,4290,4290,1700.3,0,2273,0,0,2408,0,2551,0,2863,0,3405,2863,2551};

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
    u_int switches = p2sw_read(), i;
    char str[5];
    // for (i = 0; i < 4; i++){
      
      // str[0] = (switches & (1<<i)) ? '-' :'Y'+i;
    // }
    
   
    if(switch_state_down && switch_state_down4){
      clearScreen(COLOR_WHITE);
      drawString5x7(30,20, "cat sucks", COLOR_BLACK, COLOR_WHITE);
   drawString5x7(45,5, "TETRIS", COLOR_PURPLE, COLOR_WHITE);
  
   unsigned char j = 0;
   unsigned char i =0;
 /*Border*/
 for( i =0; i <= 150; i=i+10){
   fillRectangle(0,i, 10, 10, COLOR_BLACK); 
   fillRectangle(9,i, 10, 10, COLOR_BLACK);
   fillRectangle(109,i, 10, 10, COLOR_BLACK);
   fillRectangle(119,i, 10, 10, COLOR_BLACK);
 }
 /*I-block Cyan Piece */
 fillRectangle(19,150, 10, 10, COLOR_CYAN); 
 fillRectangle(29,150, 10, 10, COLOR_CYAN);
 fillRectangle(39,150, 10, 10, COLOR_CYAN);
 fillRectangle(49,150, 10, 10, COLOR_CYAN);
  for (i=19; i<= 59; i=i+10){
    for(j=0; j<10; j++){
      drawPixel(i,150+j,COLOR_BLACK);
      if (i<59){
      drawPixel(j+i,150,COLOR_BLACK);
	}
    }
  }
 /**/
 /*L-block Orange Piece*/
 fillRectangle(59,150, 10, 10, COLOR_ORANGE); 
 fillRectangle(69,150, 10, 10, COLOR_ORANGE);
 fillRectangle(79,150, 10, 10, COLOR_ORANGE);
 fillRectangle(79,140, 10, 10, COLOR_ORANGE);
  for (i=59; i<= 79; i=i+10){
    for(j=0; j<10; j++){
      drawPixel(i,150+j,COLOR_BLACK);
      if (i<79){
      drawPixel(j+i,150,COLOR_BLACK);
	}
    }
  }
   for(i = 0; i<20; i++){
    drawPixel(79,140 +i,COLOR_BLACK);
    // drawPixel(89,140 +i,COLOR_BLACK);
  }
   for(i = 0; i<10; i++){
    drawPixel(79+i,140,COLOR_BLACK);
    drawPixel(79+i,150,COLOR_BLACK);
  }
  
   /**/

   /*J-block BLUE Piece*//*
   fillRectangle(89,130, 10, 10, COLOR_BLUE); 
   fillRectangle(89,140, 10, 10, COLOR_BLUE);
   fillRectangle(89,150, 10, 10, COLOR_BLUE);
   fillRectangle(99,150, 10, 10, COLOR_BLUE);
   for (i=99; i<= 109; i=i+10){
     for(j=0; j<10; j++){
       drawPixel(i,150+j,COLOR_BLACK);
     }
   }
			 */
    }

   else if(switch_state_down){
      clearScreen(COLOR_RED);
      str[0] = 'Y';
      str[1] = 'e';
      str[2] = 'e';
      str[3] = 't';
      drawString5x7(20,20, str, COLOR_BLACK, COLOR_RED);
    }
   else if(switch_state_down2){
      clearScreen(COLOR_ORANGE);
      str[0] = 'F';
      str[1] = 'e';
      str[2] = 'e';
      str[3] = 't';
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
      blink = 0;
      state = 0;
      drawString5x7(20,20, str, COLOR_BLACK, COLOR_YELLOW);
    }
   else if(switch_state_down4){
      clearScreen(COLOR_GREEN);
      str[0] = 'M';
      str[1] = 'e';
      str[2] = 'a';
      str[3] = 't';
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
      if (state > 120){
	state = 0;
      }
      buzzer_set_period(tetris[state]);
      state++;
      //newTune();
      blink =0 ;
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
   CCR0 += 50000;
   if(++blink == 20){
     // newTune();
     state++;
     clearScreen(COLOR_BLUE);
   }









    
    /*
    if(!switch_state_down && !switch_state_down2 && !switch_state_down3 && !switch_state_down4)
      {
     str[0] = '-';
    str[1] = '-';
    str[2] = '-';
    str[3] = '-';
    }
   */
    
    // if(switches & (4)){
    //  clearScreen(COLOR_GREEN);
    // }
    
    /*
      str[0] = (switches & (8)) ? '-' :'Y';
      str[1] = (switches & (4)) ? '-' : 'e';
      str[2] = (switches & (2)) ? '-' : 'e';
      str[3] = (switches & (1)) ? '-' : 't';
    */
    
    str[4] = 0;
    // drawString5x7(20,20, str, COLOR_BLACK, COLOR_WHITE);
    // }
    //WDT();
  }
}

// u_char width = screenWidth, height = screenHeight;
 /*
  clearScreen(COLOR_WHITE);
  u_char i;  /*
  for(i = 0; i <32; i++){
    drawPixel(i,i,COLOR_BLACK);
    drawPixel(128-i,i,COLOR_BLACK);
  }
  */
  /*Draw Triangle */
  /* u_char j;
  i = 0;
  /*
  for(j=0; j < 40; j++){
    drawPixel(j/2,j,COLOR_BLACK);
    drawPixel(0,i,COLOR_BLACK);
    drawPixel(i/2,40,COLOR_BLACK);
    i++;
  }
  */

    /* ***************************  */
  /*j = 0;
  u_char k= 0;
  for(j = 18; j>=10; j--){
    for(i = 52; i<72; i++){
      //  if(i < 82-k && i > 42 - k){
      drawPixel(i,50-j,COLOR_BLACK);
      // }
    }
    // k=k+2;
  }
  
  for(j=10; j<=20; j++){
   for(i = 42; i<52; i++){
     if( i > 42 + k){
       drawPixel(i,50-j,COLOR_BLACK);
     } 
    }
   k++;
  }
  k = 0;
  
  for(j=10; j<=20; j++){
   for(i = 72; i<82; i++){
     if( i < 82 - k){
       drawPixel(i,50-j,COLOR_BLACK);
     } 
    }
   k++;
  }
      



  
  /*
  for(i = 0; i<30; i++){
    drawPixel(89,140+i,COLOR_BLACK);
    drawPixel(99,140 +i,COLOR_BLACK);
  }
  */			  
   //  for(i = 0; i<10; i++){
   // drawPixel(89,140,COLOR_BLACK);
    //drawPixel(89,150,COLOR_BLACK);
    // drawPixel(89,130,COLOR_BLACK);
  // }
  
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
/*
void newTune(int st){
 buzzer_set_period(tetris[state]);
 state++;
}
*/
