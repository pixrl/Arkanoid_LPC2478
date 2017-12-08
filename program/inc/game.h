#ifndef GAME_H
#define GAME_H

#include <assert.h>
#include <stdlib.h>
#include "symbols.h"
#include "general.h"
#include "point.h"
#include "block.h"
#include "racket.h"
#include "ball.h"

#define BLOCKS_MAX 20

#define NUM_OF_EDGES 4
#define NUM_OF_BLOCKS 3

typedef enum {
    right,
    left,
    bottom,
    top
} typeEdges;

struct m_game;

typedef struct m_game Game;

typedef Racket* (*racketInitFunc)(Game* game, Point m_lowCenter, tU16 m_width, tU16 m_height, tU16 m_color);
typedef Ball* (*ballInitFunc)(Point m_lowCenter, tU16 m_height, tU16 m_radius, tU16 m_color);
typedef Block** (*blocksInitFunc)(Game* game, tU16 numOfBlocks, tU16 blockWidth, tU16 blockHeight);
typedef void (*addPointToGameScoreFunc)(Game* game);
typedef tU16 (*getGameScoreFunc)(Game* game);
typedef tU16 (*getGameWidthFunc)(Game* game);
typedef tU16 (*getGameHeightFunc)(Game* game);
typedef tU16 (*getGameNumOfBlocksFunc)(Game* game);
typedef tU16 (*getEdgeFunc)(Game* game, typeEdges edge);
typedef tU16 (*getDistanceFromEdgeFunc)(Game* game, typeEdges edge);
typedef void (*moveTheBallFunc)(Game* game);

struct m_game{
    addPointToGameScoreFunc addPointToGameScore;
    getGameScoreFunc getScore;
    getGameWidthFunc getWidth;
    getGameHeightFunc getHeight;
    getGameNumOfBlocksFunc getNumOfBlocks;
    getEdgeFunc getEdge;
    getDistanceFromEdgeFunc getDistanceFromEdge;
    moveTheBallFunc moveBall;
    Ball* ballPtr;
    Block* blockPtr[BLOCKS_MAX];
    Racket* racketPtr;
    tU16 score;
    tU16 width;
    tU16 height;
    tU16 numOfBlocks;
    tU16 edges[NUM_OF_EDGES];
    tU16 distanceFromEdge[NUM_OF_EDGES];
};

Game* newGame(tU16 m_width, tU16 m_height, tU16 m_numOfBlocks);
void deleteGame(Game* game);
void addPointToGameScore(Game* game);
tU16 getGameScore(Game* game);
tU16 getGameWidth(Game* game);
tU16 getGameHeight(Game* game);
tU16 getGameNumOfBlocks(Game* game);
tU16 getGameEdge(Game* game, typeEdges edge);
tU16 getGameDistanceFromEdge(Game* game, typeEdges edge);
Racket* racketInit(Game* game, Point m_lowCenter, tU16 m_width, tU16 m_height, tU16 m_color);
void blocksInit(Game* game, tU16 numOfBlocks, tU16 blockWidth, tU16 blockHeight, Block** blocks);
Ball* ballInit(Game* game, Point m_lowCenter, tU16 m_height, tU16 m_radius, tU16 m_color);
tU16 isIntersectingBlockBall(Block* block, Ball* ball);
tU16 isIntersectingRacketBall(Racket* racket, Ball* ball);
tU16 isIntersectingEdgeBall(Game* game, Ball* ball); // <--- możliwe, że to można wywalić
void testCollisionEdgeBall(Game* game);
tU16 testCollisionBlockBall(Ball* ball, Block* block);
void testCollisionRacketBall(Ball* ball, Racket* racket);
void moveTheBall(Game* game);
#endif
