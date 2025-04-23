#pragma once
#include <SDL3_image/SDL_image.h>
#include <vector>
#include "cell.h"
#include <random>
#include "retryButton.h"

struct borders{
    SDL_FPoint min;
    SDL_FPoint max;
};




class field{
    private:
        bool gameStart;
        bool lose;
        const int cellSize = 32;
        retryButton button;
        static SDL_Texture *texture;
        const int rows;
        const int cols;
        SDL_FPoint offset;
        std::vector<std::vector<cell>> gameField;
        borders fieldBorders;
        borders retryButtonBorders;
        void setMines(int x, int y);
        void analysCells();
        void openRegionAroundEmptyCells(int x, int y);
        void openRegionAroundOpenedCells(int x, int y);
        void openAllMines();

        template<typename FuncForCell>
        void forEeachCells(FuncForCell func);
        
    public:
        field(int rows, int cols, int ww, int wh);
        bool iLost();
        void reset();
        void renderField(SDL_Renderer *renderer);
        void openCell(SDL_FPoint point);
        void setFlag(SDL_FPoint point);
        borders getFieldBorders();
        borders getRetryBorders();
        SDL_AppResult createField(const char* pathOfTexture, SDL_Renderer *renderer);
        ~field();
};

template <typename FuncForCell>
inline void field::forEeachCells(FuncForCell func)
{
    for(int i = 0; i<cols; i++){
        for(int j = 0; j<rows; j++){
                func(&gameField[j][i]);   
        }
    }
}
