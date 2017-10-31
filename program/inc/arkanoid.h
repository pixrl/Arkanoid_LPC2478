#ifndef ARKANOID_H
#define ARKANOID_H

#include "general.h"	// for typedefs
#include <printf_P.h>

//#include <lcd_grph.h>

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


/*
 * Zdefiniowanie kierunków w jakich może poruszać się piłka
 */ 
 
#define UP_RIGHT					0
#define UP_LEFT						1
#define DOWN_LEFT					2
#define DOWN_RIGHT					3

/* 
 * Zdefiniowanie identyfikatorów dla poszczególnych obiektów na stole
 */ 

#define ID_BLANK					0	// Puste miejsce
#define ID_RACKET					1	// Rakieta do gry
#define ID_BALL						2	// Piłka
#define ID_BLOCK					3	// Bloczek

#define NUM_OF_EDGES				4	// Liczba krawędzi
#define NUM_OF_OBJECTS				11	// Liczba obiektów w grze
#define NUM_OF_BLOCKS				NUM_OF_OBJECTS - 2
#define NUM_OF_POINTS				2	// Liczba punktów które tworzą obiekt
#define MAX_NAME_LENGTH				3	// Maksymalna ilość znaków identyfikująca gracza

#define	UPPERRIGHT	0
#define	LOWERLEFT	1

#define NO			0
#define YES			1

#define RACKET_MOVE_RIGHT	2
#define RACKET_MOVE_LEFT	3

typedef struct Point {
	tU16		x;
	tU16		y;
} Point;
typedef struct Player {
	tU16		score;
	tS8			name[MAX_NAME_LENGTH];
} Player;
typedef struct Racket {
	Point		points[NUM_OF_POINTS];	//upperRight, lowerLeft
	tU16		color;			//color of the object
	tU16		id;
} Racket;
typedef struct Block {
	Point		points[NUM_OF_POINTS];	//upperRight, lowerLeft
	tU16		color;			//color of the object
	tU16		isDestroyed;
	tU16		id;
} Block;
typedef struct Ball {
	Point		center;	//upperRight, upperLeft, lowerRight, lowerLeft
	tU16		radius;
	tU16		color;			//color of the object
	tU16		direction;
	tU16		id;
} Ball;
typedef struct Game {
	Racket		racket;
	Block		blocks[NUM_OF_BLOCKS];
	Ball		ball;
	Player		player;
} Game;
Point setPoint(tU16 x, tU16 y);
Game gameInit(); 
void playerInit(Player *newPlayer);
void racketInit(Racket *newRacket);
void ballInit(Ball *newBall);
void blocksInit(Block *newBlock);
void moveBall(Game* inputGame);
void moveUpRight(Ball *inputBall);
void moveUpLeft(Ball *inputBall);
void moveDownRight(Ball *inputBall);
void moveDownLeft(Ball *inputBall);
void moveCheck(Game *inputGame);
tU16 moveCheckEdge(Game *inputGame);
void moveCheckBlock(Game *inputGame);
void moveRacket(Game *inputGame, tU16 joystickDirection);
void destroyBlock(Game *inputGame, tU16 blockIndexToDestroy);
void moveCheckRacket(Game *inputGame);
#endif