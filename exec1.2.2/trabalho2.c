#include "SDL2/SDL.h"
#include "SDL2_gfx-1.0.4/SDL2_gfxPrimitives.h"

int WinMain(int argc, char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("GFX",
        SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
        300,200,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
    
    SDL_SetRenderDrawColor(renderer,255,255,255,0);
    SDL_RenderClear(renderer);
    //SDL_SetRenderDrawColor(renderer,122,122,12,0);
    //(100,50)
    filledCircleRGBA(renderer,2*50,50,25,120,89,12,255);
    //(200,50)
    filledCircleRGBA(renderer,4*50,50,25,120,89,12,255);
    //(150,80),(120,120),(180,120)
    filledTrigonRGBA(renderer,150,80,120,120,180,120,0,255,255,255);
    
    filledEllipseRGBA(renderer,150,150,70,20,255,255,60,255);
    
    filledPieRGBA(renderer,2*50,50,20,0,330,0,0,0,255);
    
    filledPieRGBA(renderer,4*50,50,20,0,330,0,0,0,255);
    
    Sint16* eyebrow_xs1 = (Sint16*)malloc(sizeof(Sint16)*2);
    eyebrow_xs1[0]=20;
    eyebrow_xs1[1]=50;
    Sint16* eyebrow_ys1 = (Sint16*)malloc(sizeof(Sint16)*2);
    eyebrow_ys1[0]=40;
    eyebrow_ys1[1]=80;
    filledPolygonRGBA(renderer,eyebrow_xs1,eyebrow_ys1,4,255,0,0,255);
    
    SDL_RenderPresent(renderer);
    SDL_Delay(500);
    
    free(eyebrow_xs1);
    free(eyebrow_ys1);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}