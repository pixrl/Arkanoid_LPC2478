#ifndef SYMBOLS_H
#define SYMBOLS_H

#ifndef NULL
#define NULL (0)
#endif

#define FALSE 0
#define TRUE  1

typedef unsigned char tU8;
typedef unsigned short tU16;
typedef unsigned int tU32;
typedef signed char tS8;
typedef signed short tS16;
typedef signed int tS32;
typedef unsigned char tBool;

// przekopiować tylko od tego momentu

enum ElementID{
    ID_BLANK,
    ID_RACKET,
    ID_BALL,
    ID_BLOCK
};

enum racketDirection{
    RACKET_MOVE_RIGHT   = 0,
    RACKET_MOVE_LEFT    = 1
};
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

/* 
 * Parametry i wielkość stołu do gry
 */ 
 
#define WIDTH 						240		// musi być parzyste
#define HEIGHT 						320		// musi być parzyste
#define BOTTOM 						0
#define DISTANCEFROMTHEBOTTOMEDGE 	10
#define DISTANCEFROMTHEUPEDGE		6
#define DISTANCEFROMTHELEFTEDGE 	40
#define DISTANCE_BETWEEN_BLOCKS		2

#define RIGHT_EDGE 					WIDTH - 1
#define LEFT_EDGE					12
#define UPPER_EDGE					HEIGHT - 1

/*
 * Parametry obiektów na stole
 */ 

#define LENGTH_OF_RACKET_X			50		// musi być parzyste
#define LENGTH_OF_RACKET_Y			10
#define SIZE_OF_RACKET				LENGTH_OF_RACKET_X * LENGTH_OF_RACKET_Y
#define COLOR_OF_RACKET				BLUE

#define	BALL_RADIUS					5
#define SIZE_OF_BALL				LENGTH_OF_BALL_X * LENGTH_OF_BALL_Y
#define COLOR_OF_BALL				RED


#define LENGTH_OF_BLOCK_X			60
#define LENGTH_OF_BLOCK_Y			10
#define SIZE_OF_BLOCK				LENGTH_OF_BLOCK_X * LENGTH_OF_BLOCK_Y
#define COLOR_OF_BLOCK				PURPLE

#define MAXNUMBEROFBLOCKS 			50

#define NUM_OF_EDGES				4	// Liczba krawędzi
#define NUM_OF_OBJECTS				11	// Liczba obiektów w grze
#define NUM_OF_BLOCKS				NUM_OF_OBJECTS - 2
#define NUM_OF_POINTS				2	// Liczba punktów które tworzą obiekt
#define MAX_NAME_LENGTH				4	// Maksymalna ilość znaków identyfikująca gracza

#endif // SYMBOLS_H