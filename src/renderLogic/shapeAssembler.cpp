#include"shapeAssembler.h"

void lineCreator::createLines(const SDL_FPoint &point1, const SDL_FPoint &point2)
{  
    SDL_FPoint 
        p1 = point1, 
        p2 = point2;

    p1.x = SDL_round(p1.x);
    p1.y = SDL_round(p1.y);
    p2.x = SDL_round(p2.x);
    p2.y = SDL_round(p2.y);

    float 
        dx = p2.x - p1.x, 
        dy = p2.y - p1.y;
    bool isXMajor = SDL_fabsf(dx) > SDL_fabsf(dy);
    
    if (dx == 0 && dy == 0) return;
    
    float 
        err = 0,
        signX = (dx >= 0) ? 1.0f : -1.0f,
        signY = (dy >= 0) ? 1.0f : -1.0f,
        df = isXMajor ? SDL_fabsf(dy / dx) : SDL_fabsf(dx / dy),
        *mainFlowValPtr = isXMajor ? &p1.x : &p1.y,
        *mainSignPtr = isXMajor ? &signX : &signY;
    
    
    
    while (!(p1.x == p2.x && p1.y == p2.y))
    {
        lines.push_back(p1);
        err += df;
        if (err >= 0.5f) 
        {
            err -= 1.0f;
            p1.x += signX;
            p1.y += signY;
        }
        else
        {
            *mainFlowValPtr += *mainSignPtr;
        }
    }
    lines.push_back(p1);
}


const std::vector<SDL_FPoint> lineCreator::getLines()
{
    return lines;
}

void lineCreator::clear()
{
    lines.clear();
}

void outlineCreator::createOutline(vertexes & vert)
{   
    clear();
    std::vector<SDL_FPoint> vertex = vert.getVertexes();
    for(size_t i = 0; i<vertex.size()-1; i++){
        createLines(vertex[i],vertex[i+1]);
    }
    createLines(vertex[0],vertex[vertex.size()-1]);
}
