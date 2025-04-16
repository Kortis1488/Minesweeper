#include "Image.h"




void imageDesigner::setImageWithAutoOutline(std::vector<SDL_FPoint> *pts, float scale)
{   
    // vertex.insert(vertex.end(),pts->begin(),pts->end());
    // calculateCenter(ANGLES);
    // if(scale!=1) scaler.scale(vertex, this->center, scale);
    // offseter.offset(vertex, this->center, WW, WH);
    // creatOutline();
    // inner.insert(inner.end(),outline.begin(),outline.end());
    // innerRegion.createInnReg(inner);
    // points.insert(points.end(),inner.begin(),inner.end());
}

void imageDesigner::setImageWithPreparedOutline(std::vector<SDL_FPoint> *pts)
{   
    outline.insert(outline.end(),pts->begin(),pts->end());
    inner.insert(inner.end(),outline.begin(),outline.end());
    //innerRegion.createInnReg(inner);
    points.insert(points.end(),inner.begin(),inner.end());
}

void imageDesigner:: calculateCenter(mode m)
{   
    std::vector<SDL_FPoint> *pts;
    m==ANGLES ? pts = &vertex : pts = &outline; 

    if (pts->empty()) {
        return;
    }
    
    float y = 0, x = 0;
    for(int i = 0; i<pts->size(); i++){
        x += pts->at(i).x;
        y += pts->at(i).y;
    }
    
    this->center.x = x/pts->size();
    this->center.y = y/pts->size();
}


void imageDesigner::creatOutline()
{

    for(size_t i = 0; i<vertex.size()-1; i++){
        lin.createLines(vertex[i],vertex[i+1]);
    }
    lin.createLines(vertex[0],vertex[vertex.size()-1]);
    outline.insert(outline.end(),lin.getLines().begin(),lin.getLines().end());
    lin.clear();
}


bool imageDesigner::comparePoints(const SDL_FPoint &lpoint, const SDL_FPoint &rpoint)
{
    if (lpoint.x < rpoint.x) return true;
    if (lpoint.x > rpoint.x) return false;
    return lpoint.y < rpoint.y;
}


void imageDesigner::rotate(float radian)
{   
    outline.clear();
    inner.clear();
    points.clear();

    calculateCenter(ANGLES); 
    //rotator.rotate(vertex,center,radian,offseter);

    creatOutline();
    
    // inner.insert(inner.end(),outline.begin(),outline.end());
    // innerRegion.createInnReg(inner);
    // points.insert(points.end(),inner.begin(),inner.end());


}



imageDesigner::imageDesigner(std::vector<SDL_FPoint> *points, float scale)
{
    setImageWithAutoOutline(points, scale);
}

imageDesigner::imageDesigner(std::vector<SDL_FPoint> *points)
{
    setImageWithPreparedOutline(points);
}



std::vector<SDL_FPoint> *imageDesigner::getPoints()
{
    return &points;
}

std::vector<SDL_FPoint> *imageDesigner::getOutline()
{
    return &outline;
}
std::vector<SDL_FPoint> *imageDesigner::getAngles()
{
    return &vertex;
}
imageDesigner::imageDesigner()
{

}