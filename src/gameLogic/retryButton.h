#include <SDL3_image/SDL_image.h>

class retryButton{
    private:
        SDL_FRect sprite;
        SDL_FRect rect;
        SDL_Texture* texture;
    public:
        retryButton(SDL_Texture* texture);
        SDL_FRect * getSprite();
        SDL_FRect * getRect();
    };