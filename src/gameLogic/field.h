#pragma once
#include <SDL3_image/SDL_image.h>
#include <vector>
#include "cell.h"

struct borders{
    SDL_FPoint min;
    SDL_FPoint max;
};


class field{
    private:
        bool gameStart;
        const int cellSize = 32;
        static SDL_Texture *texture;
        const int rows;
        const int cols;
        SDL_FPoint offset;
        std::vector<std::vector<cell>> gameField;
        borders bord;
        void setMines(int x, int y);
    public:
        field(int rows, int cols, int ww, int wh);
        void renderField(SDL_Renderer *renderer);
        void openCell(SDL_FPoint point);
        borders getBorders();
        SDL_AppResult createField(const char* pathOfTexture, SDL_Renderer *renderer);
        ~field();
};