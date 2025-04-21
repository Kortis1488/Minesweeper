/* points.c ... */

/*
 * This example creates an SDL window and renderer, and then draws some points
 * to it every frame.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <vector>

#include "gameLogic/gameLogic.h"
#include "renderLogic/renderLogic.h"


/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;


static SDL_Texture *texture = NULL;
static int texture_width = 0;
static int texture_height = 0;
int rows = 20;
int cols = 30;
borders bords;

field gField(rows,cols,WW,WH);


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define WW WINDOW_WIDTH
#define WH WINDOW_HEIGHT

#define PI 3.141592653589793
#define TORADIAN PI/180


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{    
    SDL_SetAppMetadata("Minesweeper", "1.0", "bruh");
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Minesweeper", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)){
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_AppResult res = gField.createField("assets/cell.png",renderer);
    if(res==SDL_APP_FAILURE) return SDL_APP_FAILURE;

    bords = gField.getBorders();
    
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}


/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS; 
            break;
        
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if(event->button.button==SDL_BUTTON_LEFT){
                if(event->button.x >= bords.min.x && 
                    event->button.y >= bords.min.y && 
                    event->button.x <= bords.max.x && 
                    event->button.y <= bords.max.y){
                    gField.openCell({event->button.x, event->button.y});
                    std::cout << event->button.x << " " << event->button.y << "\n";
                }
            }
            break;
        default:
            break;
    }
    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void *appstate)
{       
    SDL_SetRenderDrawColor(renderer, 100, 0, 100, 100); 
    SDL_RenderClear(renderer); 
    
    gField.renderField(renderer);
   
    SDL_RenderPresent(renderer);  
    return SDL_APP_CONTINUE;  
}


void SDL_AppQuit(void *appstate, SDL_AppResult result)
{

}

// if(i==0 && j==0){
//     SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100); 
//     auto reqtprt = field[i][j].getRectPtr();
//     std::cout<< reqtprt->x << " " << reqtprt->y << '\n';

//     SDL_RenderFillRect(renderer,reqtprt);
//     continue;
// }