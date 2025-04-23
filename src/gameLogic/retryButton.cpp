#include "retryButton.h"

retryButton::retryButton(SDL_Texture *texture)
{
    texture = texture;
    rect = {10, 64, 128, 32};
    sprite = {0, 64, 128, 32};
}

SDL_FRect *retryButton::getSprite()
{
    return &sprite;
}

SDL_FRect *retryButton::getRect()
{
    return &rect;
}
