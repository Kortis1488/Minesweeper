#include "field.h"

SDL_Texture* field::texture = nullptr;

void field::renderField(SDL_Renderer *renderer)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            SDL_RenderTexture(renderer, texture, gameField[i][j].getSpritePtr(), gameField[i][j].getRectPtr());
        }
    }
    SDL_RenderTexture(renderer, texture, button.getSprite(), button.getRect());
}


void field::reset()
{
    gameStart = false;
    lose = false;   
    for(int i = 0; i<cols; i++){
        for(int j = 0; j<rows; j++){
            gameField[j][i].reset();
        }
    }
}


void field::setMines(int x, int y)
{
    gameStart = true;
    gameField[y][x].type = EMPTY;

    std::random_device rd;             // источник случайностей
    std::mt19937 gen(rd());            // генератор (Mersenne Twister)
    std::uniform_int_distribution<> dis(1, 9); // равномерное распределение от 1 до 6
    int rn;
    for(int i = 0; i<cols; i++){
        for(int j = 0; j<rows; j++){
            rn = dis(gen); 
            if(rn == 5) {
                gameField[j][i].type = MINE;
            }
        }
    }
    analysCells();
}

void field::analysCells()
{
    for(int i = 0; i<cols; i++){
        for(int j = 0; j<rows; j++){
            if(gameField[j][i].type == MINE) continue;

            for(int x = (i-1); x<=(i+1); x++){
                for(int y = (j-1); y<=(j+1); y++){
                    if(x==i&&y==j) continue;
                    try{

                        if(gameField.at(y).at(x).type == MINE) gameField[j][i].incMineCounter();
                    }
                    catch (const std::exception& e) {
                    }
                }
                
            }
        }
    }
}

bool field::iLost()
{
    return lose;
}

field::field(int rows, int cols, int ww, int wh) : rows(rows), cols(cols), gameStart(false), lose(false), button(texture)
{   
    offset.x = (ww - cols*cellSize)/2;
    offset.y = (wh - rows*cellSize)/2;
    
    fieldBorders.min = offset;
    fieldBorders.max.x = cols*cellSize + offset.x;
    fieldBorders.max.y = rows*cellSize + offset.y;

    retryButtonBorders.min.x = button.getRect()->x;
    retryButtonBorders.min.y = button.getRect()->y;
    retryButtonBorders.max.x = retryButtonBorders.min.x+button.getRect()->w;
    retryButtonBorders.max.y = retryButtonBorders.min.y+button.getRect()->h;
}

void field::openCell(SDL_FPoint point)
{
    int x = point.x - offset.x;
    int y = point.y - offset.y;
    x = x/cellSize;
    y = y/cellSize;

    if(!gameStart) setMines(x, y);
    
    try {   
        if(gameField.at(y).at(x).status != OPEN){
            if(gameField.at(y).at(x).open()) openAllMines();
        }
        if(gameField.at(y).at(x).type == EMPTY) 
        {
            openRegionAroundEmptyCells(x, y);
            return;
        }
        if(gameField.at(y).at(x).status == OPEN) {
            openRegionAroundOpenedCells(x, y);
            return;
        };
    }
    catch (const std::exception& e) {
    }
    
}

void field::openRegionAroundEmptyCells(int x, int y)
{
    for(int xAround = (x-1); xAround<=(x+1); xAround++){
        for(int yAround = (y-1); yAround<=(y+1); yAround++){
            if(xAround==x&&yAround==y) continue;
            try{
                if(gameField.at(yAround).at(xAround).status != OPEN){
                    gameField.at(yAround).at(xAround).open();
                    if(gameField.at(yAround).at(xAround).type == EMPTY) openRegionAroundEmptyCells(xAround,yAround);
                }
            }
            catch (const std::exception& e) {
            }
        }
        
    }
}

void field::openRegionAroundOpenedCells(int x, int y)
{   
    int flagCounter = 0;
    for(int xAround = (x-1); xAround<=(x+1); xAround++){
        for(int yAround = (y-1); yAround<=(y+1); yAround++){
            if(xAround==x&&yAround==y) continue;
            try{
                if(gameField.at(yAround).at(xAround).status == FLAG) flagCounter++;
            }
            catch (const std::exception& e) {
            }
        }
    }
    if(flagCounter == gameField.at(y).at(x).getMineCounter()) {
        for(int xAround = (x-1); xAround<=(x+1); xAround++){
            for(int yAround = (y-1); yAround<=(y+1); yAround++){
                if(xAround==x&&yAround==y) continue;
                try{
                    if(gameField.at(yAround).at(xAround).open()) openAllMines();
                }
                catch (const std::exception& e) {
                }
            }
        }
    }
}

void field::openAllMines()
{
    lose = true;
    for(int i = 0; i<cols; i++){
        for(int j = 0; j<rows; j++){
            if(gameField[j][i].type == MINE) {
                gameField[j][i].open();
                
            }
        }
    }
}



void field::setFlag(SDL_FPoint point)
{
    int x = point.x - offset.x;
    int y = point.y - offset.y;
    x = x/cellSize;
    y = y/cellSize;

    try {
        gameField.at(y).at(x).tag();
    }
    catch (const std::exception& e) {
    }
}

borders field::getFieldBorders()
{
    return fieldBorders;
}

borders field::getRetryBorders()
{
    return retryButtonBorders;
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

    for (int i = 0; i < rows; i++) {
        gameField.emplace_back();
        for (int j = 0; j < cols; j++) {
            xPos = j*cellSize+offset.x;
            yPos = i*cellSize+offset.y;
            gameField[i].emplace_back(cell({xPos,yPos}));
        }
    }

    return SDL_APP_CONTINUE;
}
