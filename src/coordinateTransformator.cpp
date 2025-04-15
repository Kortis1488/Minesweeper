#include "coordinateTransformator.h"

scaler::scaler()
{

}

offseter::offseter()
{

}

rotator::rotator()
{
    
}


void scaler::scale(vertexes & vert, SDL_FPoint center, float scaleVal)
{
    std::shared_ptr<std::vector<SDL_FPoint>> fg = vert.getVertexes();
    for(int i = 0; i< fg->size(); i++){
        fg->at(i).x += (fg->at(i).x-center.x)*(scaleVal-1);
        fg->at(i).y += (fg->at(i).y-center.y)*(scaleVal-1);
     }
}

void offseter::offset(vertexes &vert, SDL_FPoint center, int ww, int wh)
{
    std::shared_ptr<std::vector<SDL_FPoint>> fg = vert.getVertexes();
    SDL_FPoint offsets;
    offsets.x = ww/2 - center.x;
    offsets.y = wh/2 - center.y;

    center.x +=offsets.x;
    center.y +=offsets.y;

    for(int i = 0; i<fg->size(); i++){
        fg->at(i).x += offsets.x;
        fg->at(i).y += offsets.y;  
    }
}

void rotator::rotate(vertexes & vert, SDL_FPoint center, float turnAngle, offseter offst)
{
    std::shared_ptr<std::vector<SDL_FPoint>> fg = vert.getVertexes();
    double cos = SDL_cos(turnAngle);
    double sin = SDL_sin(turnAngle);
    for(int i = 0; i<fg->size(); i++){
        float x =  fg->at(i).x - center.x;
        float y =  fg->at(i).y - center.y;
        
        fg->at(i).x =   (x * cos - y * sin) + center.x;
        fg->at(i).y =   (x * sin + y * cos) + center.y;
    }
}









