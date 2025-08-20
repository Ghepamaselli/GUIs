#include <SDL2/SDL.h>

int WinMain(int argc, char** argv)
{

    SDL_Init(SDL_INIT_EVERYTHING);
    
    SDL_Window* window = 
        SDL_CreateWindow("Linhas",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            300,400,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
    
    
    SDL_SetRenderDrawColor(renderer,255,255,255,0);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer,255,0,0,0);

    SDL_Rect rect = {30,30,20,30};
    SDL_RenderFillRect(renderer,&rect);    
    SDL_RenderDrawRect(renderer,&rect);
    
    SDL_Point point_array[2] = {{10,10},{20,20}};
    SDL_SetRenderDrawColor(renderer,0,255,0,0);
    SDL_RenderDrawLines(renderer,point_array,2);

    
    
    SDL_Vertex triangle_array[3] = 
    {
        {{3*25,3*25} , {0,0,255,0},},
        {{3*50,3*25},{0,0,255,0},},
        {{3*37.5,3*50},{0,0,255,0},}
    };
    SDL_SetRenderDrawColor(renderer,0,0,255,0);
    SDL_RenderGeometry(renderer,NULL,triangle_array,3,NULL,3);
    
    SDL_SetRenderDrawColor(renderer,76,12,205,0);
    SDL_Rect other_rect = {200,100,200,100};
    SDL_RenderFillRect(renderer,&other_rect);
    SDL_RenderDrawRect(renderer,&other_rect);
    
    SDL_RenderPresent(renderer);
    
    SDL_Delay(5000);


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}