#include "cell.h"

const SDL_FPoint cell::sizes = {32, 32};

void cell::reset()
{
    status = CLOSE;
    mineCounter = 0;
    type = EMPTY;
    sprite = {0,0,sizes.x,sizes.y};
}

cell::cell( SDL_FPoint pos)
{   
    mineCounter = 0;
    sprite = {0,0,sizes.x,sizes.y};
    this->position = pos;
    rect = {position.x, position.y,sizes.x,sizes.y};
    this->status = CLOSE;
    type = EMPTY;
}

bool cell::open()
{
    if(status!=OPEN && status != FLAG) {
        sprite.x += sizes.x*type;
    }
    else return false;
    status = OPEN;
    
    if(type == MINE) return true;
    return false;
}

void cell::incMineCounter()
{
    mineCounter++;
    type = (cellType)(mineCounter+1); 
}

int cell::getMineCounter()
{
    return mineCounter;
}

void cell::tag()
{
    if(status == FLAG) {
        untag();
        return;
    }
    if(status!=OPEN) sprite.x += sizes.x*11;
    else return;
    status = FLAG;
}

void cell::untag()
{
    sprite.x -= sizes.x*11;
    status = CLOSE;
}

SDL_FRect *cell::getSpritePtr()
{
    return &sprite;
}

SDL_FRect *cell::getRectPtr()
{
    return &rect;
}
