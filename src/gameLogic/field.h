#pragma once
#include <SDL3_image/SDL_image.h>
#include <vector>
#include "cell.h"

class field{
    private:
        static SDL_Texture *texture;
        const int rows;
        const int cols;
        std::vector<std::vector<cell>> gameField;
    public:
        void renderField(SDL_Renderer *renderer);
        field(int rows, int cols);
        SDL_AppResult createField(const char* pathOfTexture, SDL_Renderer *renderer);
        ~field();
};