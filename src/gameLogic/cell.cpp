#include "cell.h"

const SDL_FPoint cell::sizes = {32, 32};


cell::cell(SDL_Texture* texture, cellType type, SDL_FPoint pos)
{   
    std::cout<< pos.x << " " << pos.y << "\n";
    sprite = {0,0,sizes.x,sizes.y};
    this->position = pos;
    rect = {position.x, position.y,sizes.x,sizes.y};
    this->texture = texture;
    this->status = CLOSE;
    this->type = type; 
}

void cell::open()
{
    if(status!=OPEN) sprite.x += sizes.x*type;
    else return;
    status = OPEN;
}

SDL_FRect *cell::getSpritePtr()
{
    return &sprite;
}

SDL_FRect *cell::getRectPtr()
{
    return &rect;
}
