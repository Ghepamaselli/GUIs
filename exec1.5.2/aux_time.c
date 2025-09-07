#include<SDL2/SDL.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms);

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms)
{

    int time = SDL_GetTicks();
    int isevent =SDL_WaitEventTimeout(evt,*ms);
    if(isevent)
    {   
        time -= *ms;
        return time;
    }
    return time;
    
}