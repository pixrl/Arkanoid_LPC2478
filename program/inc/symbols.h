#ifndef SYMBOLS_H
#define SYMBOLS_H

/*
 * Zdefiniowanie kolorów
 */ 

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

typedef enum{
    ID_BLANK,                       /* 0 Puste miejsce */
    ID_RACKET,                      /* 1 Rakieta do gry */
    ID_BALL,                        /* 2 Piłka */
    ID_BLOCK                        /* 3 Bloczek */
} typeID;

#define WIDTH 						240		// musi być parzyste
#define HEIGHT 						320		// musi być parzyste
#define BOTTOM_EDGE 				0
#define DISTANCEFROMTHEBOTTOMEDGE 	10
#define DISTANCEFROMTHEUPEDGE		6
#define DISTANCEFROMTHELEFTEDGE 	40
#define DISTANCEFROMTHERIGHTEDGE 	40
#define DISTANCE_BETWEEN_BLOCKS_X	2
#define DISTANCE_BETWEEN_BLOCKS_Y   2
#define RIGHT_EDGE 					WIDTH - 1
#define LEFT_EDGE					12
#define UPPER_EDGE					HEIGHT - 1

#define LENGTH_OF_RACKET_X			50		// musi być parzyste
#define LENGTH_OF_RACKET_Y			10

#define	BALL_RADIUS					5
#define SIZE_OF_BALL				LENGTH_OF_BALL_X * LENGTH_OF_BALL_Y
#define COLOR_OF_BALL				RED

#define LENGTH_OF_BLOCK_X			60
#define LENGTH_OF_BLOCK_Y			10
#define SIZE_OF_BLOCK				LENGTH_OF_BLOCK_X * LENGTH_OF_BLOCK_Y
#define COLOR_OF_BLOCK				PURPLE

#endif
