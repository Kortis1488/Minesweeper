/* points.c ... */

/*
 * This example creates an SDL window and renderer, and then draws some points
 * to it every frame.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include "vertexexCreators.h"
#include "Image.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <vector>



/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Uint64 last_time = 0;
regularTriangleVertexesCreator rTVC;



#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define WW WINDOW_WIDTH
#define WH WINDOW_HEIGHT

#define NUM_POINTS 500
#define MIN_PIXELS_PER_SECOND 30  /* move at least this many pixels per second. */
#define MAX_PIXELS_PER_SECOND 60  /* move this many pixels per second at most. */




/* (track everything as parallel arrays instead of a array of structs,
   so we can pass the coordinates to the renderer in a single function call.) */

/* Points are plotted as a set of X and Y coordinates.
   (0, 0) is the top left of the window, and larger numbers go down
   and to the right. This isn't how geometry works, but this is pretty
   standard in 2D graphics. */
static SDL_FPoint points[NUM_POINTS];
static float point_speeds[NUM_POINTS];



/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    
    int i;
    SDL_SetAppMetadata("Example Renderer Points", "1.0", "com.example.renderer-points");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Bruh", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* set up the data for a bunch of points. */
    for (i = 0; i < SDL_arraysize(points); i++) {
        points[i].x = SDL_randf() * ((float) WINDOW_WIDTH);
        points[i].y = SDL_randf() * ((float) WINDOW_HEIGHT);
        point_speeds[i] = MIN_PIXELS_PER_SECOND + (SDL_randf() * (MAX_PIXELS_PER_SECOND - MIN_PIXELS_PER_SECOND));
    }

    last_time = SDL_GetTicks();
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
    default:
        break;
    }
    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{   
    SDL_SetRenderDrawColor(renderer, 50, 0, 80, 100);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0, 150, 0, 100);
    SDL_RenderPoints(renderer,rTVC.getVertexes()->data(),rTVC.getVertexes()->size());
                            
    SDL_RenderPresent(renderer);
    //return SDL_APP_FAILURE;
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}
                            
/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}