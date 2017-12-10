/******************************************************************************
 *
 * Copyright:
 *    (C) 2000 - 2009 Embedded Artists AB
 *
 * Description:
 *    Calibrate app.
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/


#include <stdlib.h> 
#include <string.h>
#include "touch.h"
#include "calibrate.h"
#include "ea_lcd/lcd_grph.h"
#include "delay.h"


/******************************************************************************
 * Defines, macros, and typedefs
 *****************************************************************************/

#define BACK_COLOR WHITE
#define FORE_COLOR BLACK

/******************************************************************************
 * Public variables
 *****************************************************************************/


/******************************************************************************
 * Local variables
 *****************************************************************************/


static int calibPoint = 0;
static tTouchPoint refPoint1 = { 15,  300};
static tTouchPoint refPoint2 = {120, 80};
static tTouchPoint refPoint3 = {220, 280};
static tTouchPoint scr1 = {0, 0};
static tTouchPoint scr2 = {0, 0};
static tTouchPoint scr3 = {0, 0};
static tBool releaseNeeded = FALSE;
static tBool touchReleased = FALSE;


/******************************************************************************
 * Local functions
 *****************************************************************************/

static void
paintMessage(char* pMsg)
{
  tU16 msgLen = strlen((char *)pMsg);
  tU16 x = 0;
  tU16 y = 20;
  
  lcd_fillRect(0, 0, DISPLAY_WIDTH,
      40, BACK_COLOR);
  
  lcd_fontColor(FORE_COLOR,
                BACK_COLOR);
  
  // each character is 6 pixels wide
  x = (DISPLAY_WIDTH / 2) - (msgLen*6/2);
      
  lcd_putString(x, y, (tU8*)pMsg);
}


static void
drawCalibPoint(tU16 x, tU16 y)
{  
  lcd_fillScreen(BACK_COLOR);
  paintMessage("Calibrating, touch marked box...");
  lcd_drawRect(x-5, y-5, x+5, y+5, BLACK);
}

/******************************************************************************
 * Implementation of public functions
 *****************************************************************************/

void
calibrateStart(void) 
{
  tS32 x, y, z = 0;

  tBool calibrated = FALSE;
  releaseNeeded = FALSE;
  calibPoint = 0;
  
  drawCalibPoint(refPoint1.x, refPoint1.y);

  touch_xyz(&x, &y, &z);
    
  while (!calibrated) {

    mdelay(100);

    touch_xyz(&x, &y, &z);


    if (z == 0)
    {
      touchReleased = TRUE;
      continue;
    } 
    
    if (releaseNeeded && !touchReleased)
      continue;
    
    touchReleased = FALSE;
    
    
    switch (calibPoint++)
    {
    case 0:
      scr1.x = x;
      scr1.y = y;
      drawCalibPoint(refPoint2.x, refPoint2.y);

      releaseNeeded = TRUE;
      break;
    case 1:
      scr2.x = x;
      scr2.y = y;
      drawCalibPoint(refPoint3.x, refPoint3.y);

      releaseNeeded = TRUE;
      break;
    case 2:
      scr3.x = x;
      scr3.y = y;
      lcd_fillScreen(BACK_COLOR);
      paintMessage("Calibrated!");

      releaseNeeded = TRUE;
      touch_calibrate(refPoint1, refPoint2, refPoint3, scr1, scr2, scr3);

      calibrated = TRUE;
      break;
      
    }
  }

}

