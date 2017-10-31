/******************************************************************************
 *
 * Copyright:
 *    (C) 2000 - 2008 Embedded Artists AB
 *
 *****************************************************************************/

#ifndef _LCD_GRPH_
#define _LCD_GRPH_

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <general.h>


/******************************************************************************
 * Typedefs and defines
 *****************************************************************************/

#define DISPLAY_WIDTH  240
#define DISPLAY_HEIGHT 320
#define COLOR_DEPTH_BITS 16

typedef tU16 lcd_color_t;

#define   BLACK			0x0000		/*   0,   0,   0 */
#define   NAVY			0x000F      /*   0,   0, 128 */
#define   DARK_GREEN	0x03E0      /*   0, 128,   0 */
#define   DARK_CYAN		0x03EF      /*   0, 128, 128 */
#define   MAROON		0x7800      /* 128,   0,   0 */
#define   PURPLE		0x780F      /* 128,   0, 128 */
#define   OLIVE			0x7BE0      /* 128, 128,   0 */
#define   LIGHT_GRAY	0xC618      /* 192, 192, 192 */
#define   DARK_GRAY		0x7BEF      /* 128, 128, 128 */
#define   BLUE			0x001F      /*   0,   0, 255 */
#define   GREEN			0x07E0      /*   0, 255,   0 */
#define   CYAN          0x07FF      /*   0, 255, 255 */
#define   RED           0xF800      /* 255,   0,   0 */
#define   MAGENTA		0xF81F      /* 255,   0, 255 */
#define   YELLOW		0xFFE0      /* 255, 255, 0   */
#define   WHITE			0xFFFF      /* 255, 255, 255 */

/******************************************************************************
 * Public functions
 *****************************************************************************/


void lcd_fillScreen(lcd_color_t color);

void lcd_point(tU16 x, tU16 y, lcd_color_t color);

void lcd_drawRect(tU16 x0, tU16 y0, tU16 x1, tU16 y1, lcd_color_t color);

void lcd_fillRect(tU16 x0, tU16 y0, tU16 x1, tU16 y1, lcd_color_t color);

void lcd_line(tU16 x0, tU16 y0, tU16 x1, tU16 y1, lcd_color_t color);

void lcd_circle(tU16 x0, tU16 y0, tU16 r, lcd_color_t color);

void lcd_fillcircle(tU16 x0, tU16 y0, tU16 r, lcd_color_t color);

tBool lcd_putChar(tU16 x, tU16 y, tU8 ch);

void lcd_putString(tU16 x, tU16 y, tU8 *pStr);

void lcd_fontColor(lcd_color_t foreground, lcd_color_t background);

void lcd_picture(tU16 x, tU16 y, tU16 width, tU16 height, tU16 *pPicture);





#endif /* _LCD_GRPH_ */
