#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>


class baseAssebler{

};

class lines{
    private:
    std::vector<SDL_FPoint> lin;
    public:
        void createLines(const SDL_FPoint &lpoint, const SDL_FPoint &rpoint);
        std::vector<SDL_FPoint>* getLines();
        void clear();
};