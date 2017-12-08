#include "block.h"

Block* newBlock(Point m_upperRight, Point m_lowerLeft, tU16 m_color, Game* m_gamePtr){
    assert(m_upperRight.x > m_lowerLeft.x && m_upperRight.y > m_lowerLeft.y);
    assert(m_color < 0xFFFF);
    Block* block = (Block*)malloc(sizeof(struct m_block));
    block->setUpperRight = setBlockUpperRight;
    block->setLowerLeft = setBlockLowerLeft;
    block->setColor = setBlockColor;
    block->setIsDestroyed = setBlockIsDestroyed;
    block->unsetIsDestroyed = unsetBlockIsDestroyed;
    block->getUpperRight = getBlockUpperRight;
    block->getLowerLeft = getBlockLowerLeft;
    block->getColor = getBlockColor;
    block->getIsDestroyed = getBlockIsDestroyed;
    block->getId = getBlockId;
    block->getWidth = getBlockWidth;
    block->getHeight = getBlockHeight;
    block->getSize = getBlockSize;
    block->upperRight = m_upperRight;
    block->lowerLeft = m_lowerLeft;
    block->color = m_color;
    block->isDestroyed = no;
    block->id = ID_BLOCK;
    block->gamePtr = m_gamePtr;
    return block;
}
void deleteBlock(Block *block){
    free(block);
}
void setBlockUpperRight(Block* block, Point m_upperRight){
    assert(m_upperRight.x > block->lowerLeft.x && m_upperRight.y > block->lowerLeft.y);
    block->upperRight.x = m_upperRight.x;
    block->upperRight.y = m_upperRight.y;
}
void setBlockLowerLeft(Block* block, Point m_lowerLeft){
    assert(block->upperRight.x > m_lowerLeft.x && block->upperRight.y > m_lowerLeft.y);
    block->lowerLeft.x = m_lowerLeft.x;
    block->lowerLeft.y = m_lowerLeft.y;
}
void setBlockColor(Block* block, tU16 m_color){
    assert(m_color < 0xFFFF);
    block->color = m_color;
}
void setBlockIsDestroyed(Block* block){
    block->isDestroyed = yes;
}
void unsetBlockIsDestroyed(Block* block){
    block->isDestroyed = no;
}
Point getBlockUpperRight(Block* block){
    return block->upperRight;
}
Point getBlockLowerLeft(Block* block){
    return block->lowerLeft;
}
tU16 getBlockColor(Block* block){
    return block->color;
}
typeDestroyed getBlockIsDestroyed(Block* block){
    return block->isDestroyed;
}
typeID getBlockId(Block* block){
    return block->id;
}
tU16 getBlockWidth(Block* block){
    return (block->upperRight.x - block->lowerLeft.x);
}
tU16 getBlockHeight(Block* block){
    return (block->upperRight.y - block->lowerLeft.y);
}
tU16 getBlockSize(Block* block){
    return (block->getWidth(block) * block->getHeight(block));
}