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
        void offset(vertexes & vert, int ww, int wh);
};

class rotator{ 
    public: 
        rotator();
        void rotate(vertexes & vert, float turnAngle);
    
};

class scaler{
    public:
        scaler();
        void scale(vertexes & vert, float scaleVal);
};


