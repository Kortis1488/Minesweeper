 #pragma once
 #include <SDL3_image/SDL_image.h>
 #include <memory>
 #include <iostream>
 enum cellStatus{
    CLOSE,
    OPEN,
    FLAG = 11
 };

 enum cellType{
     EMPTY = 1,
     ONE = 2,
     TWO = 3,
     TREE = 4,
     FOUR = 5,
     FIVE = 6,
     SIX = 7,
     SEVEN = 8,
     EIGHT = 9,
     MINE = 10
    };
    

 class cell{
    private:
        SDL_FRect sprite;
        SDL_FRect rect;
        int mineCounter;
        void untag();
    public:
        void reset();
        cell(SDL_FPoint pos);
        bool open();
        void tag();
        void incMineCounter();
        int getMineCounter();
        SDL_FRect * getSpritePtr();
        SDL_FRect * getRectPtr();
        static const SDL_FPoint sizes;
        SDL_FPoint position;
        cellStatus status;
        cellType type;
 };