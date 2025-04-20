#include "field.h"

SDL_Texture* field::texture = nullptr;

void field::renderField(SDL_Renderer *renderer)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            SDL_RenderTexture(renderer, gameField[i][j].texture, gameField[i][j].getSpritePtr(), gameField[i][j].getRectPtr());
        }
    }
}

field::field(int rows, int cols) : 
rows(rows),
cols(cols)
{
    
}

field::~field()
{
    SDL_DestroyTexture(texture);
}

SDL_AppResult field::createField(const char *pathOfTexture, SDL_Renderer *renderer)
{   
    if(!(texture = IMG_LoadTexture(renderer, pathOfTexture))){
        return SDL_APP_FAILURE;
    }
    float offset = 100;
    float xPos, yPos;

    for (int i = 0; i < rows; i++) {
        gameField.emplace_back();
        for (int j = 0; j < cols; j++) {
            xPos = j*16+offset;
            yPos = i*16+offset;
            gameField[i].emplace_back(cell(texture, ONE, {xPos,yPos}));
        }
    }
    return SDL_APP_CONTINUE;
}
