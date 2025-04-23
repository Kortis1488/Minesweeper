#pragma once
#include "coordinateTransformator.h"
#include "shapeAssembler.h"
#include "filler.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define WW WINDOW_WIDTH
#define WH WINDOW_HEIGHT


enum mode{
    ANGLES,
    OUTLINE
};

class imageDesigner{
    private:
        std::vector<SDL_FPoint> vertex; //заменит нормальный класс
        std::vector<SDL_FPoint> outline; //заменит нормальный класс
        std::vector<SDL_FPoint> inner; //заменит нормальный класс

        lineCreator lin;    //в принипе вот они слева направо
        scaler scaler;
        offseter offseter;
        innerRegionCreator innerRegion;
        rotator rotator;
        
        void setImageWithAutoOutline(std::vector<SDL_FPoint> *points, float scale); //попизже надо сдлеать
        void setImageWithPreparedOutline(std::vector<SDL_FPoint> *points);

        static bool comparePoints(const SDL_FPoint &lpoint, const SDL_FPoint &rpoint); // не надо нахуй

    protected:
        SDL_FPoint center; // не надо нахуй
        std::vector<SDL_FPoint> points; // скорее всего не надо но я подумаюы
    public:
        imageDesigner();
        imageDesigner(std::vector<SDL_FPoint> * points, float scale);
        imageDesigner(std::vector<SDL_FPoint> * points);

        void rotate(float radian);
        std::vector<SDL_FPoint> * getPoints(); // TODO: надо буамжно подумать, скорее всего сделать их консантными.
        std::vector<SDL_FPoint> * getOutline();
        std::vector<SDL_FPoint> * getAngles();
    };