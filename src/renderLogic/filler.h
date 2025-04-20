#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "shapeAssembler.h"



class innerRegionCreator{
    protected:
        std::vector<SDL_FPoint> innerRegion;
    public:
        void createInnReg(outlineCreator &lin);
        std::vector<SDL_FPoint> getInnerRegion();
};


