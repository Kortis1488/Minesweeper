#include "filler.h"

void innerRegion::createInnReg(std::vector<SDL_FPoint> &lin)
{
    auto comparePoints = [](const SDL_FPoint &lpoint, const SDL_FPoint &rpoint)
    {   
        if (lpoint.y < rpoint.y) return true;
        if (lpoint.y > rpoint.y) return false;
        return lpoint.x < rpoint.x;
    };

    lineCreator l;
    sort(lin.begin(),lin.end(),comparePoints);

    for(int i = 0; i<lin.size()-1; i++){
        if(lin[i].y==lin[i+1].y){
            l.createLines(lin.at(i),lin.at(i+1));
        }
    }
    lin.insert(lin.end(),l.getLines()->begin(),l.getLines()->end());
}