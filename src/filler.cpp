#include "filler.h"

void innerRegionCreator::createInnReg(outlineCreator &lin)
{
    std::vector<SDL_FPoint> outline = lin.getLines();
    auto comparePoints = [](const SDL_FPoint &lpoint, const SDL_FPoint &rpoint)
    {   
        if (lpoint.y < rpoint.y) return true;
        if (lpoint.y > rpoint.y) return false;
        return lpoint.x < rpoint.x;
    };

    lineCreator l;
    sort(outline.begin(),outline.end(),comparePoints);

    for(int i = 0; i<outline.size()-1; i++){
        if(outline[i].y==outline[i+1].y){
            l.createLines(outline.at(i),outline.at(i+1));
        }
    }
    innerRegion = l.getLines();
}

std::vector<SDL_FPoint> innerRegionCreator::getInnerRegion()
{
    return innerRegion;
}
