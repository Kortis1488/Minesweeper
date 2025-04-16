#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>


class baseAssebler{

};

class lineCreator{
    private:
        std::vector<SDL_FPoint> lines;
    public:
        void createLines(const SDL_FPoint &lpoint, const SDL_FPoint &rpoint);
        const std::vector<SDL_FPoint>*  getLines();
        void clear();
};