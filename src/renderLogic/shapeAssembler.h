#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include "vertexexCreators.h"

class lineCreator{
    protected:
        std::vector<SDL_FPoint> lines;
    public:
        void createLines(const SDL_FPoint &lpoint, const SDL_FPoint &rpoint);
        const std::vector<SDL_FPoint> getLines();
        void clear();
};

class outlineCreator: public lineCreator{
    public:
        void createOutline(vertexes & vert);
};

