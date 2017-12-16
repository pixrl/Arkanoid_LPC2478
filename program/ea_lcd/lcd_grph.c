/******************************************************************************
 *
 * Copyright:
 *    (C) 2000 - 2008 Embedded Artists AB
 * 
 * Description:
 *    Graphics library.
 *
 *****************************************************************************/


/******************************************************************************
 * Includes
 *****************************************************************************/

#include <printf_P.h>
#include "lpc24xx.h"
#include <general.h>
#include "lcd_hw.h"
#include "lcd_grph.h"
#include "font5x7.h"
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 * Local variables
 *****************************************************************************/

static lcd_color_t  foregroundColor = WHITE;
static lcd_color_t  backgroundColor = BLACK;
static tU8 const font_mask[8] 
  = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

/******************************************************************************
 * Implementation of local functions
 *****************************************************************************/

/*****************************************************************************
 *
 * Description:
 *    Draw a horizontal line
 *
 * Params:
 *    [in] x0 - x value for start point
 *    [in] y0 - y value for start point
 *    [in] x1 - x value for end point
 *    [in] color - color of the line
 *
 ****************************************************************************/
static void 
hLine(tU16 x0, 
      tU16 y0, 
      tU16 x1, 
      lcd_color_t color) 
{
  tU16 bak;

  if (x0 > x1) 						
  {
    bak = x1;
    x1 = x0;
    x0 = bak;
  }
  lcd_point(x0, y0, color);
  x0++;
   
  while(x1 >= x0)
  {
    lcd_point(x0, y0, color);
    x0++;
  }
  return;
}

/*****************************************************************************
 *
 * Description:
 *    Draw a vertical line
 *
 * Params:
 *    [in] x0 - x value for start point
 *    [in] y0 - y value for start point
 *    [in] y1 - y value for end point
 *    [in] color - color of the line
 *
 ****************************************************************************/
static void 
vLine(tU16 x0, 
      tU16 y0, 
      tU16 y1, 
      lcd_color_t color)
{
  tU16 bak;

  if(y0 > y1) 						
  {
    bak = y1;
    y1 = y0;
    y0 = bak;
  }

  while(y1 >= y0)
  {
    lcd_point(x0, y0, color);
    y0++;
  }
  return;
}

/*****************************************************************************
 *
 * Description:
 *    Fill the screen with a given color.
 *
 * Params:
 *    [in] color - color to fill the screen with
 *
 ****************************************************************************/
void 
lcd_fillScreen(lcd_color_t color)
{
  tU16 i = 0;
  tU16 j = 0;

  for(i=0; i < DISPLAY_HEIGHT; i++)
  {
    for(j=0; j<DISPLAY_WIDTH; j++)
    {
      lcd_point(j, i, color);
    }
  }
  return;
}

/*****************************************************************************
 *
 * Description:
 *    Draw a point.
 *
 * Params:
 *    [in] x - x value for the point
 *    [in] y - y value for the point
 *    [in] color - color for the point
 *
 ****************************************************************************/
void 
lcd_point(tU16 x, 
          tU16 y, 
          lcd_color_t color)
{
  if( x >= DISPLAY_WIDTH )  
  {
    return;
  }
  
  if(y >= DISPLAY_HEIGHT)
  {
    return;
  }
  *((tU16 *)(LCD_FRAME_BUFFER + x*2 + 240*2*y)) = color;

  return;
}

/*****************************************************************************
 *
 * Description:
 *    Draw a rectangle.
 *
 * Params:
 *    [in] x0 - x value for the upper left corner
 *    [in] y0 - y value for the upper left corner
 *    [in] x1 - x value for the lower right corner
 *    [in] y1 - y value for the lower right corner
 *    [in] color - color for rectangle
 *
 ****************************************************************************/
void 
lcd_drawRect(tU16 x0, 
             tU16 y0, 
             tU16 x1, 
             tU16 y1, 
             lcd_color_t color)
{  
  hLine(x0, y0, x1, color);
  hLine(x0, y1, x1, color);
  vLine(x0, y0, y1, color);
  vLine(x1, y0, y1, color);
}

/*****************************************************************************
 *
 * Description:
 *    Fill a rectangle.
 *
 * Params:
 *    [in] x0 - x value for the upper left corner
 *    [in] y0 - y value for the upper left corner
 *    [in] x1 - x value for the lower right corner
 *    [in] y1 - y value for the lower right corner
 *    [in] color - color for rectangle
 *
 ****************************************************************************/
void 
lcd_fillRect(tU16 x0, 
             tU16 y0, 
             tU16 x1, 
             tU16 y1, 
             lcd_color_t color)
{  
  tU16 i = 0;

  if(x0 > x1)
  {   
    i  = x0;
    x0 = x1;
    x1 = i;
  }

  if(y0 > y1)
  {   
    i  = y0;
    y0 = y1;
    y1 = i;
  }

  if(y0 == y1) 
  {  
    hLine(x0, y0, x1, color);
    return;
  }

  if(x0 == x1) 
  {  
    vLine(x0, y0, y1, color);
    return;
  }

  while(y0 <= y1)						
  {  
    hLine(x0, y0, x1, color);
    y0++;
  }
  return;
}

/*****************************************************************************
 *
 * Description:
 *    Draw a line.
 *
 * Params:
 *    [in] x0 - x value for the start point
 *    [in] y0 - y value for the start point
 *    [in] x1 - x value for the end point
 *    [in] y1 - y value for the end point
 *    [in] color - color of the line
 *
 ****************************************************************************/
void 
lcd_line(tU16 x0, 
         tU16 y0, 
         tU16 x1, 
         tU16 y1, 
         lcd_color_t color)
{  
  tS16   dx = 0, dy = 0;
  tS8    dx_sym = 0, dy_sym = 0;
  tS16   dx_x2 = 0, dy_x2 = 0;
  tS16   di = 0;

  dx = x1-x0;
  dy = y1-y0;


  if(dx == 0)			/* vertical line */ 
  {
    vLine(x0, y0, y1, color);
    return;
  }

  if(dx > 0)
  {    
    dx_sym = 1;
  }
  else
  { 
    dx_sym = -1;
  }

  if(dy == 0)			/* horizontal line */  
  {
    hLine(x0, y0, x1, color);
    return;
  }

  if(dy > 0)
  {    
    dy_sym = 1;
  }
  else
  { 
    dy_sym = -1;
  }

  dx = dx_sym*dx;
  dy = dy_sym*dy;

  dx_x2 = dx*2;
  dy_x2 = dy*2;

  if(dx >= dy)
  { 
    di = dy_x2 - dx;
    while(x0 != x1)
    {   
      lcd_point(x0, y0, color);
      x0 += dx_sym;
      if(di<0)
      {
        di += dy_x2;
      }
      else
      {
        di += dy_x2 - dx_x2;
        y0 += dy_sym;
      }
    }
    lcd_point(x0, y0, color);
  }
  else
  {
    di = dx_x2 - dy;
    while(y0 != y1)
    {   
      lcd_point(x0, y0, color);
      y0 += dy_sym;
      if(di < 0)
      { 
        di += dx_x2;
      }
      else
      {
        di += dx_x2 - dy_x2;
        x0 += dx_sym;
      }
    }
    lcd_point(x0, y0, color);
  }
  return; 
}

/*****************************************************************************
 *
 * Description:
 *    Draw a circle.
 *
 * Params:
 *    [in] x0 - x value for the center point
 *    [in] y0 - y value for the center point
 *    [in] r - the readius of the circle
 *    [in] color - color of the cicle
 *
 ****************************************************************************/
void 
lcd_circle(tU16 x0, 
           tU16 y0, 
           tU16 r, 
           lcd_color_t color)
{
  tS16 draw_x0, draw_y0;
  tS16 draw_x1, draw_y1;	
  tS16 draw_x2, draw_y2;	
  tS16 draw_x3, draw_y3;	
  tS16 draw_x4, draw_y4;	
  tS16 draw_x5, draw_y5;	
  tS16 draw_x6, draw_y6;	
  tS16 draw_x7, draw_y7;	
  tS16 xx, yy;
  tS16  di;

  if(r == 0)		  /* no radius */ 
  {
    return;
  }

  draw_x0 = draw_x1 = x0;
  draw_y0 = draw_y1 = y0 + r;
  if(draw_y0 < DISPLAY_HEIGHT)
  { 
    lcd_point(draw_x0, draw_y0, color);		/* 90 degree */
  }

  draw_x2 = draw_x3 = x0;
  draw_y2 = draw_y3 = y0 - r;
  if(draw_y2 >= 0)
  {
    lcd_point(draw_x2, draw_y2, color);    /* 270 degree */
  }

  draw_x4 = draw_x6 = x0 + r;
  draw_y4 = draw_y6 = y0;
  if(draw_x4 < DISPLAY_WIDTH)
  {
    lcd_point(draw_x4, draw_y4, color);		/* 0 degree */
  }

  draw_x5 = draw_x7 = x0 - r;
  draw_y5 = draw_y7 = y0;
  if(draw_x5>=0)
  {
    lcd_point(draw_x5, draw_y5, color);		/* 180 degree */
  }

  if(r == 1)
  {
    return;
  }

  di = 3 - 2*r;
  xx = 0;
  yy = r;
  while(xx < yy)
  {  
    if(di < 0)
    {
      di += 4*xx + 6;	      
    }
    else
    {  
      di += 4*(xx - yy) + 10;
      yy--;	  
      draw_y0--;
      draw_y1--;
      draw_y2++;
      draw_y3++;
      draw_x4--;
      draw_x5++;
      draw_x6--;
      draw_x7++;	 	
    }  
    xx++;   
    draw_x0++;
    draw_x1--;
    draw_x2++;
    draw_x3--;
    draw_y4++;
    draw_y5++;
    draw_y6--;
    draw_y7--;

    if( (draw_x0 <= DISPLAY_WIDTH) && (draw_y0>=0) )	
    {
      lcd_point(draw_x0, draw_y0, color);
    }

    if( (draw_x1 >= 0) && (draw_y1 >= 0) )	
    { 
      lcd_point(draw_x1, draw_y1, color);
    }

    if( (draw_x2 <= DISPLAY_WIDTH) && (draw_y2 <= DISPLAY_HEIGHT) )
    {
      lcd_point(draw_x2, draw_y2, color);
    }

    if( (draw_x3 >=0 ) && (draw_y3 <= DISPLAY_HEIGHT) )	
    {
      lcd_point(draw_x3, draw_y3, color);
    }

    if( (draw_x4 <= DISPLAY_HEIGHT) && (draw_y4 >= 0) )	
    {
      lcd_point(draw_x4, draw_y4, color);
    }

    if( (draw_x5 >= 0) && (draw_y5 >= 0) )
    {  
      lcd_point(draw_x5, draw_y5, color);
    }
    if( (draw_x6 <= DISPLAY_WIDTH) && (draw_y6 <= DISPLAY_HEIGHT) )	
    {
      lcd_point(draw_x6, draw_y6, color);
    }
    if( (draw_x7 >= 0) && (draw_y7 <= DISPLAY_HEIGHT) )	
    {  
      lcd_point(draw_x7, draw_y7, color);
    }
  }
  return;
}

/*****************************************************************************
 *
 * Description:
 *    Fill a circle.
 *
 * Params:
 *    [in] x0 - x value for the center point
 *    [in] y0 - y value for the center point
 *    [in] r - the readius of the circle
 *    [in] color - color of the cicle
 *
 ****************************************************************************/
void 
lcd_fillcircle(tU16 x0, 
           tU16 y0, 
           tU16 r, 
           lcd_color_t color)
{
  tS16 draw_x0, draw_y0;
  tS16 draw_x1, draw_y1;	
  tS16 draw_x2, draw_y2;	
  tS16 draw_x3, draw_y3;	
  tS16 draw_x4, draw_y4;	
  tS16 draw_x5, draw_y5;	
  tS16 draw_x6, draw_y6;	
  tS16 draw_x7, draw_y7;	
  tS16 fill_x0, fill_y0;
  tS16 fill_x1;
  tS16 xx, yy;
  tS16  di;

  if(r == 0)		  /* no radius */ 
  {
    return;
  }

  draw_x0 = draw_x1 = x0;
  draw_y0 = draw_y1 = y0 + r;
  if(draw_y0 < DISPLAY_HEIGHT)
  { 
    lcd_point(draw_x0, draw_y0, color);		/* 90 degree */
  }

  draw_x2 = draw_x3 = x0;
  draw_y2 = draw_y3 = y0 - r;
  if(draw_y2 >= 0)
  {
    lcd_point(draw_x2, draw_y2, color);    /* 270 degree */
  }

  draw_x4 = draw_x6 = x0 + r;
  draw_y4 = draw_y6 = y0;
  if(draw_x4 < DISPLAY_WIDTH)
  {
    lcd_point(draw_x4, draw_y4, color);		/* 0 degree */
    fill_x1 = draw_x4;
  }
  else
  {
    fill_x1 = DISPLAY_WIDTH;
  }

  fill_y0 = y0;
  fill_x0 = x0 - r;
  if(fill_x0<0)
    fill_x0 = 0;
  hLine(fill_x0, fill_y0, fill_x1, color);


  draw_x5 = draw_x7 = x0 - r;
  draw_y5 = draw_y7 = y0;
  if(draw_x5>=0)
  {
    lcd_point(draw_x5, draw_y5, color);		/* 180 degree */
  }

  if(r == 1)
  {
    return;
  }

  di = 3 - 2*r;
  xx = 0;
  yy = r;
  while(xx < yy)
  {  
    if(di<0)
	  {
      di += 4*xx + 6;
	  }
	  else
	  {
      di += 4*(xx - yy) + 10;
	    yy--;	  
		  draw_y0--;
		  draw_y1--;
		  draw_y2++;
		  draw_y3++;
		  draw_x4--;
		  draw_x5++;
		  draw_x6--;
		  draw_x7++;		 
	  }
	  
	  xx++;   
	  draw_x0++;
	  draw_x1--;
	  draw_x2++;
	  draw_x3--;
	  draw_y4++;
	  draw_y5++;
	  draw_y6--;
	  draw_y7--;

    if( (draw_x0 <= DISPLAY_WIDTH) && (draw_y0>=0) )	
    {
      lcd_point(draw_x0, draw_y0, color);
    }

    if( (draw_x1 >= 0) && (draw_y1 >= 0) )	
    { 
      lcd_point(draw_x1, draw_y1, color);
    }

	  if(draw_x1>=0)
	  {
      fill_x0 = draw_x1;
	    fill_y0 = draw_y1;
      if(fill_y0>DISPLAY_HEIGHT)
        fill_y0 = DISPLAY_HEIGHT;
      if(fill_y0<0)
        fill_y0 = 0; 
      fill_x1 = x0*2 - draw_x1;				
      if(fill_x1>DISPLAY_WIDTH)
        fill_x1 = DISPLAY_WIDTH;
      hLine(fill_x0, fill_y0, fill_x1, color);
    }

    if( (draw_x2 <= DISPLAY_WIDTH) && (draw_y2 <= DISPLAY_HEIGHT) )
    {
      lcd_point(draw_x2, draw_y2, color);
    }

    if( (draw_x3 >=0 ) && (draw_y3 <= DISPLAY_HEIGHT) )	
    {
      lcd_point(draw_x3, draw_y3, color);
    }

	  if(draw_x3>=0)
	  {
      fill_x0 = draw_x3;
      fill_y0 = draw_y3;
      if(fill_y0>DISPLAY_HEIGHT)
        fill_y0 = DISPLAY_HEIGHT;
      if(fill_y0<0)
        fill_y0 = 0;
      fill_x1 = x0*2 - draw_x3;				
      if(fill_x1>DISPLAY_WIDTH)
        fill_x1 = DISPLAY_WIDTH;
      hLine(fill_x0, fill_y0, fill_x1, color);
    }

    if( (draw_x4 <= DISPLAY_HEIGHT) && (draw_y4 >= 0) )	
    {
      lcd_point(draw_x4, draw_y4, color);
    }

    if( (draw_x5 >= 0) && (draw_y5 >= 0) )
    {  
      lcd_point(draw_x5, draw_y5, color);
    }

	  if(draw_x5>=0)
	  {
      fill_x0 = draw_x5;
	    fill_y0 = draw_y5;
      if(fill_y0>DISPLAY_HEIGHT)
        fill_y0 = DISPLAY_HEIGHT;
      if(fill_y0<0)
        fill_y0 = 0;
      fill_x1 = x0*2 - draw_x5;				
      if(fill_x1>DISPLAY_WIDTH)
        fill_x1 = DISPLAY_WIDTH;
      hLine(fill_x0, fill_y0, fill_x1, color);
    }

    if( (draw_x6 <= DISPLAY_WIDTH) && (draw_y6 <= DISPLAY_HEIGHT) )	
    {
      lcd_point(draw_x6, draw_y6, color);
    }
    if( (draw_x7 >= 0) && (draw_y7 <= DISPLAY_HEIGHT) )	
    {  
      lcd_point(draw_x7, draw_y7, color);
    }

	  if(draw_x7>=0)
	  {
      fill_x0 = draw_x7;
      fill_y0 = draw_y7;
      if(fill_y0>DISPLAY_HEIGHT)
        fill_y0 = DISPLAY_HEIGHT;
      if(fill_y0<0)
        fill_y0 = 0;
      fill_x1 = x0*2 - draw_x7;				
      if(fill_x1>DISPLAY_WIDTH)
        fill_x1 = DISPLAY_WIDTH;
      hLine(fill_x0, fill_y0, fill_x1, color);
    }
  }
  return;
}

/*****************************************************************************
 *
 * Description:
 *    Draw a character on the display.
 *
 * Params:
 *    [in] x - x value for the character
 *    [in] y - y value for the character
 *    [in] ch - the character
 *
 ****************************************************************************/
tBool 
lcd_putChar(tU16 x, 
            tU16 y, 
            tU8 ch)
{  
  tU8 data = 0;
  tU8 i = 0, j = 0;

  lcd_color_t color = BLACK;

  if((x >= (DISPLAY_WIDTH - 8)) || (y >= (DISPLAY_HEIGHT - 8)) )
  {
    return( FALSE );
  }

  if( (ch < 0x20) || (ch > 0x7f) )
  {
    ch = 0x20;		/* unknown character will be set to blank */
  }

  ch -= 0x20;
  for(i=0; i<8; i++)
  {
    data = font5x7[ch][i];
    for(j=0; j<6; j++)
    {
      if( (data&font_mask[j])==0 )
      {  
        color = backgroundColor;
      }
      else
      {
        color = foregroundColor;
      }
      lcd_point(x, y, color);       
      x++;
    }   
    y++;
    x -= 6;
  }
  return( TRUE );
}

/*****************************************************************************
 *
 * Description:
 *    Draw a string on the display.
 *
 * Params:
 *    [in] x - x value for the string
 *    [in] y - y value for the string
 *    [in] pStr - the string
 *
 ****************************************************************************/
void 
lcd_putString(tU16 x, 
              tU16 y, 
              tU8 *pStr)
{
  while(1)
  {      
	  if( (*pStr)=='\0' )
	  {
		  break;
	  }
	  if( lcd_putChar(x, y, *pStr++) == 0 )
	  {
  		break;
  	}
  	x += 6;
  }
  return;
}

/*****************************************************************************
 *
 * Description:
 *    Set foreground and background color for fonts
 *
 * Params:
 *    [in] foreground - the foreground color
 *    [in] background - the background color
 *
 ****************************************************************************/
void 
lcd_fontColor(lcd_color_t foreground, 
              lcd_color_t background)
{
  foregroundColor = foreground;
  backgroundColor = background;
  return;
}

/*****************************************************************************
 *
 * Description:
 *    Draw a picture in raw format on the display
 *
 * Params:
 *    [in] x - x value of the start point
 *    [in] y - y value of the start point 
 *    [in] width - width of the picture
 *    [in] height - height of the picture 
 *    [in] pPicture - picture data 
 *
 ****************************************************************************/
void lcd_picture(tU16 x, 
                 tU16 y, 
                 tU16 width, 
                 tU16 height, 
                 tU16 *pPicture)
{
  int i = 0;
  char* buf = (char*) LCD_FRAME_BUFFER;
  char* pic = (char*) pPicture;

    
  buf += (x*2 + DISPLAY_WIDTH*2*y);
  
  for (i = 0; i < height; i++)
  {     
    memcpy(buf, pic, width*2);
    buf += DISPLAY_WIDTH*2;
    pic += width*2;
  }
  
}
