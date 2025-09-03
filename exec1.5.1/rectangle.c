#include<SDL2/SDL.h>


int can_move_left=1;
int can_move_right=1;
int can_move_up =1;
int can_move_down=1;

int check_colision(SDL_Rect* rect,int screen_width, int screen_height)
{
 if (rect->x < 0) {
        rect->x = 0;
    }
    
    if (rect->x + rect->w > screen_width) {
        rect->x = screen_width - rect->w;
    }
    // Top boundary
    if (rect->y < 0) {
        rect->y = 0;
    }
    
    if (rect->y + rect->h > screen_height) {
        rect->y = screen_height - rect->h;
    }
}

void process_time_rect(SDL_Rect*t_rect,int delta_time)
{
    if(t_rect->x >=600 && t_rect->y>=400)
        {
            t_rect->x=0;
            t_rect->y=0;    
        }
        t_rect->x+=100.0f*(delta_time/1000.0f);
        t_rect->y+=100.0f*(delta_time/1000.0f);
}

void process_input(SDL_Event event,SDL_Rect* m_rect,SDL_Rect*k_rect,int delta_time)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_UP:
                {
                    if(can_move_up)
                        k_rect->y-=1000.0f*(delta_time/1000.0f);
                    break;
                }
                case SDLK_DOWN:
                {
                    if(can_move_down)
                        k_rect->y+=1000.0f*(delta_time/1000.0f);
                    break;
                }
                case SDLK_LEFT:
                {
                    if(can_move_left)
                        k_rect->x-=1000.0f*(delta_time/1000.0f);
                    break;
                }
                case SDLK_RIGHT:
                {
                    if(can_move_right)    
                        k_rect->x+=1000.0f*(delta_time/1000.0f);
                    break;
                }
                
            }
            printf("x:%d y:%d",k_rect->x,k_rect->y);
            break;
        }

        case SDL_WINDOWEVENT:
            {
                switch (event.window.event)
                {                
                    case SDL_WINDOWEVENT_CLOSE:
                    {
                        SDL_Quit();
                        break;
                    }

                }
                break;
            }
        case SDL_MOUSEMOTION:
        {
            m_rect->x = event.motion.x;
            m_rect->y = event.motion.y;
        }
    }
        
   
}


int WinMain(int argc,char** argv)
{
    SDL_Window* window = SDL_CreateWindow("anime",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			600,400,SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);

	SDL_SetRenderDrawColor(renderer,255,255,255,0);
    
    SDL_Rect mouse_rect = {300,300,30,30};
    
    SDL_Rect keyboard_rect = {300,300,30,30};

    SDL_Rect time_rect={0,0,30,30};

    
    
	SDL_RenderClear(renderer);
    SDL_Event event;
    int wait =16;
    Uint32 last = SDL_GetTicks();
    Uint32 now = 0;
    float delta_time =0;
    while(1)
    {
        now = SDL_GetTicks();
        delta_time= (float)(now-last);
        last = now;

        

        SDL_SetRenderDrawColor(renderer,255,255,255,0);
        SDL_RenderClear(renderer);

        //DRAW RECT_MOUSE
        SDL_SetRenderDrawColor(renderer,255,0,0,0);
        SDL_RenderFillRect(renderer,&mouse_rect);
        //DRAW KEYBOARD_MOUSE
        SDL_SetRenderDrawColor(renderer,0,255,0,0);
        SDL_RenderFillRect(renderer,&keyboard_rect);
        //DRAW TINE_MOUSe
        SDL_SetRenderDrawColor(renderer,0,0,255,0);
        SDL_RenderFillRect(renderer,&time_rect);
        
        SDL_RenderPresent(renderer);
        
        
        check_colision(&keyboard_rect,600,400);  
        int is_event =SDL_WaitEventTimeout(&event,wait);
        if(is_event){
            
            process_input(event,&mouse_rect,&keyboard_rect,delta_time);
        }    
        process_time_rect(&time_rect,delta_time);
        
        
    
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}