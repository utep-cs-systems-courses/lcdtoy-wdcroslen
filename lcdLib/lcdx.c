/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */
#define M_PI 3.14159265358979323846
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include <math.h>

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;
  
  clearScreen(COLOR_WHITE);
  u_char i;
  /*
  for(i = 0; i <32; i++){
    drawPixel(i,i,COLOR_BLACK);
    drawPixel(128-i,i,COLOR_BLACK);
  }
  */
  /*Draw Triangle */
  u_char j;
  i = 0;
  for(j=0; j < 20; j++){
    drawPixel(j,j,COLOR_BLACK);
    drawPixel(0,i,COLOR_BLACK);
    drawPixel(i,20,COLOR_BLACK);
    i++;
  }



  
  /* for(i = 0; i <30; i++){
    // drawPixel(sin(i),cos(i),COLOR_BLACK);
    printf("hi");
  }
*/
         /* Draw Circle  */
   /* ***************************  */


  /* def circle(center,rad):

 # Returns the coordinates of the points in a circle given center and radius
    n = int(4*rad*math.pi)
    t = np.linspace(0,6.3,n)
    x = center[0]+rad*np.sin(t)
    y = center[1]+rad*np.cos(t)
    return x,y
  */
    /* ***************************  */
  /* drawString5x7(38,20, "cat sucks", COLOR_BLACK, COLOR_BLUE);
   */

  
  // fillRectangle(32,32, 64, 64, COLOR_RED);
  
}
