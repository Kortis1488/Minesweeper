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

void scaler::scale(vertexes &vert, float scaleVal)
{   
    SDL_FPoint center = vert.getCenter();
    std::vector<SDL_FPoint> fg = vert.getVertexes();
    for(int i = 0; i<fg.size(); i++){
        fg[i].x += (fg[i].x-center.x)*(scaleVal-1);
        fg[i].y += (fg[i].y-center.y)*(scaleVal-1);
     }
    vert.setVertexes(fg);
}

void offseter::offset(vertexes &vert, int ww, int wh)
{   
    SDL_FPoint center = vert.getCenter();
    std::vector<SDL_FPoint> fg = vert.getVertexes();
    SDL_FPoint offsets;
    offsets.x = ww/2 - center.x;
    offsets.y = wh/2 - center.y;

    center.x +=offsets.x;
    center.y +=offsets.y;

    for(int i = 0; i<fg.size(); i++){
        fg[i].x += offsets.x;
        fg[i].y += offsets.y;  
    }
    vert.setVertexes(fg);
}

void rotator::rotate(vertexes & vert,float turnAngle)
{
    SDL_FPoint center = vert.getCenter();
    std::vector<SDL_FPoint> fg = vert.getVertexes();
    double cos = SDL_cos(turnAngle);
    double sin = SDL_sin(turnAngle);
    for(int i = 0; i<fg.size(); i++){
        float x =  fg[i].x - center.x;
        float y =  fg[i].y - center.y;
        
        fg[i].x =   (x * cos - y * sin) + center.x;
        fg[i].y =   (x * sin + y * cos) + center.y;
    }
    vert.setVertexes(fg);
}









