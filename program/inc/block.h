#ifndef BLOCK_H
#define BLOCK_H

#include <stdlib.h>
#include <assert.h>
#include "general.h"
#include "symbols.h"
#include "point.h"

typedef enum{
    no,
    yes
} typeDestroyed;

struct m_game;

typedef struct m_game Game;

struct m_block;

typedef struct m_block Block;

typedef void (*setBlockUpperRightFunc)(Block* block, Point m_upperRight);
typedef void (*setBlockLowerLeftFunc)(Block* block, Point m_upperRight);
typedef void (*setBlockColorFunc)(Block* block, tU16 m_color);
typedef void (*setBlockIsDestroyedFunc)(Block* block);
typedef void (*unsetBlockIsDestroyedFunc)(Block* block);
typedef Point (*getBlockUpperRightFunc)(Block* block);
typedef Point (*getBlockLowerLeftFunc)(Block* block);
typedef tU16 (*getBlockColorFunc)(Block* block);
typedef typeDestroyed (*getBlockIsDestroyedFunc)(Block* block);
typedef typeID (*getBlockIdFunc)(Block* block);
typedef tU16 (*getBlockWidthFunc)(Block* block);
typedef tU16 (*getBlockHeightFunc)(Block* block);
typedef tU16 (*getBlockSizeFunc)(Block* block);
struct m_block{
    setBlockUpperRightFunc setUpperRight;
    setBlockLowerLeftFunc setLowerLeft;
    setBlockColorFunc setColor;
    setBlockIsDestroyedFunc setIsDestroyed;
    unsetBlockIsDestroyedFunc unsetIsDestroyed;
    getBlockUpperRightFunc getUpperRight;
    getBlockLowerLeftFunc getLowerLeft;
    getBlockColorFunc getColor;
    getBlockIsDestroyedFunc getIsDestroyed;
    getBlockIdFunc getId;
    getBlockWidthFunc getWidth;
    getBlockHeightFunc getHeight;
    getBlockSizeFunc getSize;
    Point upperRight;
    Point lowerLeft;
    tU16 color;
    typeDestroyed isDestroyed;
    typeID id;
    Game* gamePtr;
};
Block* newBlock(Point m_upperRight, Point m_lowerLeft, tU16 m_color, Game* m_gamePtr);
void deleteBlock(Block *block);
void setBlockUpperRight(Block* block, Point m_upperRight);
void setBlockLowerLeft(Block* block, Point m_lowerLeft);
void setBlockColor(Block* block, tU16 m_color);
void setBlockIsDestroyed(Block* block);
void unsetBlockIsDestroyed(Block* block);
Point getBlockUpperRight(Block* block);
Point getBlockLowerLeft(Block* block);
tU16 getBlockColor(Block* block);
typeDestroyed getBlockIsDestroyed(Block* block);
typeID getBlockId(Block* block);
tU16 getBlockWidth(Block* block);
tU16 getBlockHeight(Block* block);
tU16 getBlockSize(Block* block);
#endif
