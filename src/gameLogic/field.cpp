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

void field::setMines(int x, int y)
{
    gameStart = true;
    gameField[y][x].type = EMPTY;
}

field::field(int rows, int cols, int ww, int wh) : rows(rows), cols(cols), gameStart(false)
{   
    offset.x = (ww - cols*cellSize)/2;
    offset.y = (wh - rows*cellSize)/2;
    
    bord.min = offset;
    bord.max.x = cols*cellSize + offset.x;
    bord.max.y = rows*cellSize + offset.y;
}

void field::openCell(SDL_FPoint point)
{
    int x = point.x - offset.x;
    int y = point.y - offset.y;
    x = x/cellSize;
    y = y/cellSize;
    if(!gameStart) setMines(x, y);


    try {
        gameField.at(y).at(x).open();
    }
    catch (const std::exception& e) {
    }
    
}

borders field::getBorders()
{
    return bord;
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
    
    float xPos, yPos;

    int count = 0;
    for (int i = 0; i < rows; i++) {
        gameField.emplace_back();
        for (int j = 0; j < cols; j++) {
            xPos = j*cellSize+offset.x;
            yPos = i*cellSize+offset.y;
            count++;
            if(count>8) count = 0;
            gameField[i].emplace_back(cell(texture, (cellType)(ONE+count), {xPos,yPos}));
        }
    }

    return SDL_APP_CONTINUE;
}
