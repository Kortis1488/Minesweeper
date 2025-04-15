#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class baseVertexesCreator{
    protected:
        std::vector<SDL_FPoint> vertex;
    public:
        baseVertexesCreator();
        virtual SDL_FPoint getCenter();
        std::shared_ptr <std::vector<SDL_FPoint>> getVertex(); 
};

class regularTriangleVertexesCreator: public baseVertexesCreator{
    public:
        regularTriangleVertexesCreator();
    };

class circleCreator: public baseVertexesCreator{
    public:
        circleCreator();
        circleCreator(float centerX, float centerY, int radius);
        void createCircle(float centerX, float centerY, int radius);
};

class curveVertexesCreator: public baseVertexesCreator{
    public:
        curveVertexesCreator();
        curveVertexesCreator(SDL_FPoint p0, SDL_FPoint p1, SDL_FPoint p2, float step);
        void createCurve(SDL_FPoint p0, SDL_FPoint p1, SDL_FPoint p2, float step);
};

class doubleCurveVertexesCreator: public curveVertexesCreator{
    public:
        doubleCurveVertexesCreator(SDL_FPoint p0, SDL_FPoint p1, SDL_FPoint p2, float step);
};
