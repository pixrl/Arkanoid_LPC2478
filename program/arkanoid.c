#include "arkanoid.h"
#include <printf_P.h>

Point setPoint(tU16 x, tU16 y)
{
	Point newPoint;
	newPoint.x = x;
	newPoint.y = y;
	return newPoint;
}
Game gameInit()
{
	Game newGame;
	racketInit(&newGame.racket);
	ballInit(&newGame.ball);
	blocksInit(newGame.blocks);
	playerInit(&newGame.player);
	return newGame;
}
void playerInit(Player *newPlayer)
{	
	newPlayer->score	= 0;
	//strncpy(name, newPlayer->name, MAX_NAME_LENGTH);
}
void racketInit(Racket *newRacket)
{
	tU16 coordinateRacket_x0 = WIDTH/2 + LENGTH_OF_RACKET_X/2;
	tU16 coordinateRacket_y0 = DISTANCEFROMTHEBOTTOMEDGE + LENGTH_OF_RACKET_Y;
	tU16 coordinateRacket_x1 = WIDTH/2 - LENGTH_OF_RACKET_X/2;
	tU16 coordinateRacket_y1 = DISTANCEFROMTHEBOTTOMEDGE;
	newRacket->points[UPPERRIGHT]	= setPoint(coordinateRacket_x0, coordinateRacket_y0);
	newRacket->points[LOWERLEFT]	= setPoint(coordinateRacket_x1, coordinateRacket_y1);
	newRacket->color				= COLOR_OF_RACKET;
	newRacket->id					= ID_RACKET;
}
void ballInit(Ball *newBall)
{
	tU16 coordinateBall_x0	= WIDTH/2;
	tU16 coordinateBall_y0	= DISTANCEFROMTHEBOTTOMEDGE + LENGTH_OF_RACKET_Y + BALL_RADIUS;
	newBall->center			= setPoint(coordinateBall_x0, coordinateBall_y0);
	newBall->radius			= BALL_RADIUS;
	newBall->direction		= UP_LEFT;
	newBall->color			= COLOR_OF_BALL;
	newBall->id				= ID_BALL;
}
void blocksInit(Block *newBlock)
{
	tU16 blockIndex = 0;
	tU16 initBlock_x0	= DISTANCEFROMTHELEFTEDGE + LENGTH_OF_BLOCK_X;
	tU16 initBlock_y0	= HEIGHT - DISTANCEFROMTHEUPEDGE - LENGTH_OF_BLOCK_Y;
	tU16 initBlock_x1	= DISTANCEFROMTHELEFTEDGE;
	tU16 initBlock_y1	= HEIGHT - DISTANCEFROMTHEUPEDGE;
	tU16 coordinateBlock_x0 = initBlock_x0;
	tU16 coordinateBlock_y0 = initBlock_y0;
	tU16 coordinateBlock_x1 = initBlock_x1;
	tU16 coordinateBlock_y1 = initBlock_y1;
	
	for(blockIndex = 0; blockIndex < NUM_OF_BLOCKS; ++blockIndex)
	{
		newBlock[blockIndex].points[UPPERRIGHT]	= setPoint(coordinateBlock_x0, coordinateBlock_y0);
		newBlock[blockIndex].points[LOWERLEFT]	= setPoint(coordinateBlock_x1, coordinateBlock_y1);
		newBlock[blockIndex].color				= COLOR_OF_BLOCK;
		newBlock[blockIndex].isDestroyed		= NO;
		newBlock[blockIndex].id					= ID_BLOCK;
		if((coordinateBlock_x0 + LENGTH_OF_BLOCK_X + DISTANCE_BETWEEN_BLOCKS) < WIDTH)
		{
			coordinateBlock_x0 += LENGTH_OF_BLOCK_X + DISTANCE_BETWEEN_BLOCKS;
			coordinateBlock_x1 += LENGTH_OF_BLOCK_X + DISTANCE_BETWEEN_BLOCKS;
		}
		else
		{
			coordinateBlock_x0	= initBlock_x0;
			coordinateBlock_y0	-= (LENGTH_OF_BLOCK_Y + DISTANCE_BETWEEN_BLOCKS);
			coordinateBlock_x1	= initBlock_x1;
			coordinateBlock_y1	-= (LENGTH_OF_BLOCK_Y + DISTANCE_BETWEEN_BLOCKS);
		}
	}
}
void moveBall(Game* inputGame)
{
	moveCheck(inputGame);
	switch(inputGame->ball.direction)
	{
		case UP_RIGHT:
			moveUpRight(&inputGame->ball);
			break;
		case UP_LEFT:
			moveUpLeft(&inputGame->ball);
			break;
		case DOWN_RIGHT:
			moveDownRight(&inputGame->ball);
			break;
		case DOWN_LEFT:
			moveDownLeft(&inputGame->ball);
			break;
	}
}
void moveUpRight(Ball *inputBall)
{
	inputBall->center.x += 1;
	inputBall->center.y += 1;
}
void moveUpLeft(Ball *inputBall)
{
	inputBall->center.x -= 1;
	inputBall->center.y += 1;
}
void moveDownRight(Ball *inputBall)
{
	inputBall->center.x += 1;
	inputBall->center.y -= 1;
}
void moveDownLeft(Ball *inputBall)
{
	inputBall->center.x -= 1;
	inputBall->center.y -= 1;
}
void moveCheck(Game *inputGame)
{
	switch(inputGame->ball.direction)
	{
		case UP_RIGHT:
			// check if move is possible
			moveCheckBlock(inputGame);
			moveCheckEdge(inputGame);
			break;
		case UP_LEFT:
			// check if move is possible
			moveCheckBlock(inputGame);
			moveCheckEdge(inputGame);
			break;
		case DOWN_RIGHT:
			// check if move is possible
			moveCheckRacket(inputGame);
			moveCheckBlock(inputGame);
			moveCheckEdge(inputGame);
			break;
		case DOWN_LEFT:
			// check if move is possible
			moveCheckRacket(inputGame);
			moveCheckBlock(inputGame);
			moveCheckEdge(inputGame);
			break;
	}
}
tU16 moveCheckEdge(Game *inputGame)
{
	Point ballCenter	= inputGame->ball.center;
	tU16 ballRadius		= inputGame->ball.radius;
	switch(inputGame->ball.direction)
	{
		case UP_RIGHT:
			// check if move is possible
			if(ballCenter.x + ballRadius < RIGHT_EDGE && ballCenter.y + ballRadius < UPPER_EDGE)
				return 1;
			else
			{
				if(ballCenter.y + ballRadius >= UPPER_EDGE)
					inputGame->ball.direction = DOWN_RIGHT;
				else
					inputGame->ball.direction = UP_LEFT;
			}
			break;
		case UP_LEFT:
			// check if move is possible
			if(ballCenter.x + ballRadius > LEFT_EDGE && ballCenter.y + ballRadius < UPPER_EDGE)
				return 1;
			else
			{
				if(ballCenter.y + ballRadius >= UPPER_EDGE)
					inputGame->ball.direction = DOWN_LEFT;
				else
					inputGame->ball.direction = UP_RIGHT;
			}
			break;
		case DOWN_RIGHT:
			// check if move is possible
			if(ballCenter.x + ballRadius < RIGHT_EDGE && ballCenter.y + ballRadius > 0)
				return 1;
			else
			{
				if(ballCenter.y + ballRadius <= 0)
					inputGame->ball.direction = UP_LEFT;
				else
					inputGame->ball.direction = DOWN_LEFT;
			}
			break;
		case DOWN_LEFT:
			// check if move is possible
			if(ballCenter.x + ballRadius > LEFT_EDGE && ballCenter.y + ballRadius > 0)
				return 1;
			else
			{
				if(ballCenter.y + ballRadius <= 0)
					inputGame->ball.direction = UP_RIGHT;
				else
					inputGame->ball.direction = DOWN_RIGHT;
			}
			break;
	}
	return 0;
}

void moveCheckBlock(Game *inputGame)
{
	tU16	blockIndex 	= 0;
	Point	ballCenter	= inputGame->ball.center;
	tU16	ballRadius	= inputGame->ball.radius;
	for(blockIndex 	= 0; blockIndex < NUM_OF_BLOCKS; ++blockIndex)
	{
		if(inputGame->blocks[blockIndex].isDestroyed == YES)
			continue;
		if(ballCenter.x + ballRadius >= inputGame->blocks[blockIndex].points[LOWERLEFT].x 
		&& ballCenter.x + ballRadius <= inputGame->blocks[blockIndex].points[UPPERRIGHT].x
		&& ballCenter.y + ballRadius <= inputGame->blocks[blockIndex].points[LOWERLEFT].y
		&& ballCenter.y + ballRadius >= inputGame->blocks[blockIndex].points[UPPERRIGHT].y)
		{
			destroyBlock(inputGame, blockIndex);
		}
	}
	return;
}
void moveCheckRacket(Game *inputGame)
{
	Point	ballCenter	= inputGame->ball.center;
	tU16	ballRadius	= inputGame->ball.radius;
	if(ballCenter.y + ballRadius <= inputGame->racket.points[UPPERRIGHT].y + LENGTH_OF_RACKET_Y
	&& ballCenter.x + ballRadius <= inputGame->racket.points[UPPERRIGHT].x
	&& ballCenter.y + ballRadius >= inputGame->racket.points[LOWERLEFT].y + LENGTH_OF_RACKET_Y
	&& ballCenter.x + ballRadius >= inputGame->racket.points[LOWERLEFT].x)
	{
		printf("MOVECHECKRACKET");
		if(inputGame->ball.direction == DOWN_LEFT)
			inputGame->ball.direction = UP_LEFT;
		else
			inputGame->ball.direction = UP_RIGHT;
	}
	return;
}
void moveRacket(Game *inputGame, tU16 joystickDirection)
{
	switch(joystickDirection)
	{
		case RACKET_MOVE_RIGHT:
		if(inputGame->racket.points[UPPERRIGHT].x + 1 >= WIDTH);
		else
		{
			inputGame->racket.points[UPPERRIGHT].x	+= 1;
			inputGame->racket.points[LOWERLEFT].x	+= 1;
		}
		break;
		
		case RACKET_MOVE_LEFT:
		if(inputGame->racket.points[LOWERLEFT].x - 1 <= BOTTOM);
		else
		{
			inputGame->racket.points[UPPERRIGHT].x	-= 1;
			inputGame->racket.points[LOWERLEFT].x	-= 1;
		}
		break;
	}
}
void destroyBlock(Game *inputGame, tU16 blockIndexToDestroy)
{
	inputGame->blocks[blockIndexToDestroy].isDestroyed	= YES;
	inputGame->blocks[blockIndexToDestroy].color		= BLACK;
	switch(inputGame->ball.direction)
	{
		case UP_RIGHT:
		inputGame->ball.direction = DOWN_RIGHT;
		break;
		case UP_LEFT:
		inputGame->ball.direction = DOWN_LEFT;
		break;
		case DOWN_RIGHT:
		inputGame->ball.direction = UP_RIGHT;
		break;
		case DOWN_LEFT:
		inputGame->ball.direction = UP_LEFT;
		break;
	}
	inputGame->player.score++;
	return;
}
