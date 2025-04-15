#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include "vertexexCreators.h"

class offseter{
    public:
        offseter();
        void offset(vertexes & vert, SDL_FPoint center, int ww, int wh);
};

class rotator{ 
    public: 
        rotator();
        void rotate(vertexes & vert, SDL_FPoint center, float turnAngle, offseter offst);
    
};

class scaler{
    public:
        scaler();
        void scale(vertexes & vert, SDL_FPoint center, float scaleVal);
};


