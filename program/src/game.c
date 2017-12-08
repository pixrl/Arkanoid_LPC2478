#include "game.h"

Game* newGame(tU16 m_width, tU16 m_height, tU16 m_numOfBlocks){
    Game *game = (Game*)malloc(sizeof(struct m_game));
    game->score = 0;
    game->width = m_width;
    game->height = m_height;
    game->numOfBlocks = m_numOfBlocks;
    game->edges[right] = RIGHT_EDGE;
    game->edges[left] = LEFT_EDGE;
    game->edges[bottom] = BOTTOM_EDGE;
    game->edges[top] = UPPER_EDGE;
    game->distanceFromEdge[right] = DISTANCEFROMTHERIGHTEDGE;
    game->distanceFromEdge[left] = DISTANCEFROMTHELEFTEDGE;
    game->distanceFromEdge[bottom] = DISTANCEFROMTHEBOTTOMEDGE;
    game->distanceFromEdge[top] = DISTANCEFROMTHEUPEDGE;
    game->addPointToGameScore = addPointToGameScore;
    game->getScore = getGameScore;
    game->getWidth = getGameWidth;
    game->getHeight = getGameHeight;
    game->getNumOfBlocks = getGameNumOfBlocks;
    game->getEdge = getGameEdge;
    game->getDistanceFromEdge = getGameDistanceFromEdge;
    game->moveBall = moveTheBall;
    Point* lowPoint = newPoint(game->width/2, game->height - (game->distanceFromEdge[top]));
    game->racketPtr = racketInit(game, *lowPoint, LENGTH_OF_RACKET_X, LENGTH_OF_RACKET_Y, PURPLE);
    game->ballPtr = ballInit(game, *lowPoint, LENGTH_OF_RACKET_Y, BALL_RADIUS, RED);
    blocksInit(game, m_numOfBlocks, LENGTH_OF_BLOCK_X, LENGTH_OF_BLOCK_Y, game->blockPtr);
    deletePoint(lowPoint);
    return game;
}
void deleteGame(Game* game){
    tU16 i = 0;
    deleteBall(game->ballPtr);
    deleteRacket(game->racketPtr);
    for(i = 0; i < game->numOfBlocks; i++)
        deleteBlock(game->blockPtr[i]);
    free(game);
}
void addPointToGameScore(Game* game){
    game->score++;
}
tU16 getGameScore(Game* game){
    return game->score;
}
tU16 getGameWidth(Game* game){
    return game->width;
}
tU16 getGameHeight(Game* game){
    return game->height;
}
tU16 getGameNumOfBlocks(Game* game){
    return game->numOfBlocks;
}
tU16 getGameEdge(Game* game, typeEdges edge){
    return game->edges[edge];
}
tU16 getGameDistanceFromEdge(Game* game, typeEdges edge){
    return game->distanceFromEdge[edge];
}
Ball* ballInit(Game* game, Point m_lowCenter, tU16 m_height, tU16 m_radius, tU16 m_color){
    Point* center = newPoint(m_lowCenter.x, m_lowCenter.y - (m_height + m_height + m_radius));
    Direction* customDirection = newDirection((rand() % 2 ? -1 : 1), -1);
    srand(time(NULL));
    Ball* ball = newBall(*center, m_radius, m_color, *customDirection, game);
    deleteDirection(customDirection);
    deletePoint(center);
    return ball;
}
void blocksInit(Game* game, tU16 numOfBlocks, tU16 blockWidth, tU16 blockHeight, Block** blocks){
    int i;
    Point* m_upperRight = newPoint((game->distanceFromEdge[left] + blockWidth), game->distanceFromEdge[bottom] + blockHeight);
    Point* m_lowerLeft = newPoint((game->distanceFromEdge[left]), game->distanceFromEdge[bottom]);
    tU16 numOfCols = 3;
    i = 0;
    for(i = 0; i < numOfBlocks; i++){
        blocks[i] = newBlock(*m_upperRight, *m_lowerLeft, PURPLE, game);
        m_upperRight->set_x(m_upperRight, m_upperRight->get_x(m_upperRight) + DISTANCE_BETWEEN_BLOCKS_X + blockWidth);
        m_lowerLeft->set_x(m_lowerLeft, m_lowerLeft->get_x(m_lowerLeft) + DISTANCE_BETWEEN_BLOCKS_X + blockWidth);
        if(i % numOfCols == 0)
        {
            m_upperRight->set_x(m_upperRight, game->distanceFromEdge[left] + blockWidth);
            m_lowerLeft->set_x(m_lowerLeft, game->distanceFromEdge[left]);
            m_upperRight->set_y(m_upperRight, m_upperRight->get_y(m_upperRight) + blockHeight + DISTANCE_BETWEEN_BLOCKS_Y);
            m_lowerLeft->set_y(m_lowerLeft, m_lowerLeft->get_y(m_lowerLeft) + blockHeight + DISTANCE_BETWEEN_BLOCKS_Y);
        }
    }
    deletePoint(m_upperRight);
    deletePoint(m_lowerLeft);
    return;
}
Racket* racketInit(Game* game, Point m_lowCenter, tU16 m_width, tU16 m_height, tU16 m_color){
    Point* m_upperRight = newPoint(m_lowCenter.x + m_width/2, HEIGHT - DISTANCEFROMTHEUPEDGE);
    Point* m_lowerLeft = newPoint(m_lowCenter.x - m_width/2, HEIGHT - (DISTANCEFROMTHEUPEDGE + m_height));
    Racket* racket = newRacket(*m_upperRight, *m_lowerLeft, m_color, game);
    deletePoint(m_upperRight);
    deletePoint(m_lowerLeft);
    return racket;
}
tU16 isIntersectingBlockBall(Block* block, Ball* ball){
	if(block->getIsDestroyed(block))
        return 0;
    return ((block->getUpperRight(block).x  >= (ball->getCenter(ball).x - ball->getRadius(ball)))
        && (block->getLowerLeft(block).x    <= (ball->getCenter(ball).x + ball->getRadius(ball)))
        && (block->getLowerLeft(block).y    <= (ball->getCenter(ball).y + ball->getRadius(ball)))
        && (block->getUpperRight(block).y   >= (ball->getCenter(ball).y - ball->getRadius(ball))));
}
/*         ballCenter.x + ballRadius >= inputGame->blocks[blockIndex].points[LOWERLEFT].x 
		&& ballCenter.x + ballRadius <= inputGame->blocks[blockIndex].points[UPPERRIGHT].x
		&& ballCenter.y + ballRadius <= inputGame->blocks[blockIndex].points[LOWERLEFT].y
		&& ballCenter.y + ballRadius >= inputGame->blocks[blockIndex].points[UPPERRIGHT].y)*/
tU16 isIntersectingRacketBall(Racket* racket, Ball* ball){
    return ((racket->getUpperRight(racket).x >= (ball->getCenter(ball).x - ball->getRadius(ball)))
        && (racket->getLowerLeft(racket).x   <= (ball->getCenter(ball).x + ball->getRadius(ball)))
        && (racket->getLowerLeft(racket).y   <= (ball->getCenter(ball).y + ball->getRadius(ball)))
        && (racket->getUpperRight(racket).y  >= (ball->getCenter(ball).y - ball->getRadius(ball))));
}
/*tU16 isIntersectingEdgeBall(Game* game, Ball* ball){
    return ((game->getEdge(game, right)  >= (ball->getCenter(ball).x - ball->getRadius(ball)))
        || (game->getEdge(game, left)    <= (ball->getCenter(ball).x + ball->getRadius(ball)))
        || (game->getEdge(game, bottom)  >= (ball->getCenter(ball).y + ball->getRadius(ball)))
        || (game->getEdge(game, top)     <= (ball->getCenter(ball).y - ball->getRadius(ball))));
}*/
void testCollisionEdgeBall(Game* game){
    /*if(!isIntersectingEdgeBall(game, game->ballPtr))
        return;*/
    if((game->ballPtr->center.x - game->ballPtr->radius) >= game->getEdge(game, left))
        game->ballPtr->direction.x *= -1;
    if((game->ballPtr->center.x + game->ballPtr->radius) <= game->getEdge(game, right))
        game->ballPtr->direction.x *= -1;
    if((game->ballPtr->center.y + game->ballPtr->radius) >= game->getEdge(game, top))
        game->ballPtr->direction.y *= -1;
    if((game->ballPtr->center.y - game->ballPtr->radius) <= game->getEdge(game, bottom))
        game->ballPtr->direction.y *= -1;
    return;
}
tU16 testCollisionBlockBall(Ball* ball, Block* block){
    if(!isIntersectingBlockBall(block, ball))
        return 0;
    if((ball->center.x + ball->radius) >= block->getLowerLeft(block).x){
        ball->direction.x *= -1;
    }
    if((ball->center.x - ball->radius) <= block->getUpperRight(block).x){
        ball->direction.x *= -1;
    }
    if((ball->center.y - ball->radius) >= block->getUpperRight(block).y){
        ball->direction.y *= -1;
    }
    if((ball->center.y + ball->radius) <= block->getLowerLeft(block).y){
        ball->direction.y *= -1;
    }
    return 1;
}
void testCollisionRacketBall(Ball* ball, Racket* racket){
    if(!isIntersectingRacketBall(racket, ball))
        return;
    if((ball->center.x - ball->radius) <= racket->getLowerLeft(racket).x)
        ball->direction.x *= -1;
    if((ball->center.x + ball->radius) >= racket->getUpperRight(racket).x)
        ball->direction.x *= -1;
    if((ball->center.y - ball->radius) >= racket->getUpperRight(racket).y)
        ball->direction.y *= -1;
    if((ball->center.y + ball->radius) <= racket->getLowerLeft(racket).y)
        ball->direction.y *= -1;
    return;
}
void moveTheBall(Game* game){
    tU16 i;
    testCollisionRacketBall(game->ballPtr, game->racketPtr);
    for(i = 0; i < game->numOfBlocks; i++){
        if(testCollisionBlockBall(game->ballPtr, game->blockPtr[i]))
        {
            game->blockPtr[i]->setIsDestroyed(game->blockPtr[i]);
            game->addPointToGameScore(game);
        }
    }
    testCollisionEdgeBall(game);
    game->ballPtr->moveBall(game->ballPtr);
    return;
}
/*void blocksInit(Block **newBlocks)
{
	tU16 blockIndex = 0;
	tU16 initBlock_x0	= DISTANCEFROMTHELEFTEDGE + LENGTH_OF_BLOCK_X;
	tU16 initBlock_y0	= DISTANCEFROMTHEBOTTOMEDGE + LENGTH_OF_BLOCK_Y;
	tU16 initBlock_x1	= DISTANCEFROMTHELEFTEDGE;
	tU16 initBlock_y1	= DISTANCEFROMTHEBOTTOMEDGE;
	tU16 coordinateBlock_x0 = initBlock_x0;
	tU16 coordinateBlock_y0 = initBlock_y0;
	tU16 coordinateBlock_x1 = initBlock_x1;
	tU16 coordinateBlock_y1 = initBlock_y1;
	Point *m_upperRight;
    Point *m_lowerLeft;
	for(blockIndex = 0; blockIndex < NUM_OF_BLOCKS; ++blockIndex){
        m_upperRight = newPoint(coordinateBlock_x0, coordinateBlock_y0);
        m_lowerLeft  = newPoint(coordinateBlock_x1, coordinateBlock_y1);
		newBlocks[blockIndex] = newBlock(*m_upperRight, *m_lowerLeft, COLOR_OF_BLOCK);
        deletePoint(m_upperRight);
        deletePoint(m_lowerLeft);
		if((coordinateBlock_x0 + LENGTH_OF_BLOCK_X + DISTANCE_BETWEEN_BLOCKS) < WIDTH){
			coordinateBlock_x0 += LENGTH_OF_BLOCK_X + DISTANCE_BETWEEN_BLOCKS;
			coordinateBlock_x1 += LENGTH_OF_BLOCK_X + DISTANCE_BETWEEN_BLOCKS;
		}
		else{
			coordinateBlock_x0	= initBlock_x0;
			coordinateBlock_y0	+= (LENGTH_OF_BLOCK_Y + DISTANCE_BETWEEN_BLOCKS);
			coordinateBlock_x1	= initBlock_x1;
			coordinateBlock_y1	+= (LENGTH_OF_BLOCK_Y + DISTANCE_BETWEEN_BLOCKS);
		}
	}
}*/
