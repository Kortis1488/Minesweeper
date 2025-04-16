#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class vertexes{
    protected:
        std::vector<SDL_FPoint> vertex;
    public:
        vertexes();
        virtual SDL_FPoint getCenter();
        std::vector<SDL_FPoint> getVertexes();
        bool setVertexes(std::vector<SDL_FPoint> vert);
};

class regularTriangleVertexesCreator: public vertexes{
    public:
        regularTriangleVertexesCreator();
    };

class circleCreator: public vertexes{
    public:
        circleCreator();
        circleCreator(float centerX, float centerY, int radius);
        void createCircle(float centerX, float centerY, int radius);
};

class curveVertexesCreator: public vertexes{
    public:
        curveVertexesCreator();
        curveVertexesCreator(SDL_FPoint p0, SDL_FPoint p1, SDL_FPoint p2, float step);
        void createCurve(SDL_FPoint p0, SDL_FPoint p1, SDL_FPoint p2, float step);
};

class doubleCurveVertexesCreator: public curveVertexesCreator{
    public:
        doubleCurveVertexesCreator(SDL_FPoint p0, SDL_FPoint p1, SDL_FPoint p2, float step);
};
