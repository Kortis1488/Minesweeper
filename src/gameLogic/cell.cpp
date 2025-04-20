#include "cell.h"

const SDL_FPoint cell::sizes = {16, 16};


cell::cell(SDL_Texture* texture, cellType type, SDL_FPoint pos)
{   
    std::cout<< pos.x << " " << pos.y << "\n";
    sprite = {0,0,16,16};
    this->position = pos;
    rect = {position.x, position.y,16,16};
    this->texture = texture;
    this->status = CLOSE;
    this->type = type; 
}

void cell::open()
{
    status = OPEN;
    sprite.x += 16*type;
}

SDL_FRect *cell::getSpritePtr()
{
    return &sprite;
}

SDL_FRect *cell::getRectPtr()
{
    return &rect;
}
