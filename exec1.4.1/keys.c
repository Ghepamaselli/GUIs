#include <SDL2/SDL.h>
#include <stdlib.h>


int can_move_left=1;
int can_move_right=1;
int can_move_up =1;
int can_move_down=1;

int ranged_rand(int min, int max)
{
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}


typedef struct Colored_rect
{
    SDL_Rect* rect;
    int r;
    int g;
    int b;
}Colored_rect;

Colored_rect* create_new_rect(int xpos, int ypos)
{
    Colored_rect* rect = (Colored_rect*)malloc(sizeof(Colored_rect));
    rect->rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    rect->rect->x = xpos;
    rect->rect->y = ypos;
    rect->rect->w = 10;
    rect->rect->h = 10;
    int r = ranged_rand(0,255);
    int g = ranged_rand(0,255);
    int b = ranged_rand(0,255);
    rect->r = r;
    rect->g = g;
    rect->b =b;
    
    return rect;
}

typedef struct Rect_array
{
    Colored_rect** array;
    int current_index;
}Rect_array;


Rect_array* create_Rect_array()
{
    Rect_array* array=(Rect_array*)malloc(sizeof(Rect_array));
    array->array = (Colored_rect**)malloc(sizeof(Colored_rect*)*10);
    for(int i=0;i<10;i++)
    {
        array->array[i]=NULL;
    }
    array->current_index=0;
    return array;
}

void destroy_Rect_array(Rect_array* array)
{
    for(int i=0;i<10;i++)
    {
        if(array->array[i]!=NULL)
        {
            free(array->array[i]->rect);
            free(array->array[i]);
        }
    }
    free(array->array);
    free(array);
}

void place_on_rect_array(Rect_array* array,int x,int y)
{
    if(array->array[array->current_index]!=NULL)
    {
        SDL_Rect* rect = array->array[array->current_index]->rect;
        free(rect); 
    }
   
    array->array[array->current_index] = create_new_rect(x,y);
    array->current_index = (array->current_index +1)%10;
}

void draw_rect_on_the_screen(SDL_Renderer* ren,Rect_array* pool)
{
    for(int i=0;i<10;i++)
    {
        if(pool->array[i]!=NULL){
        SDL_SetRenderDrawColor(ren,pool->array[i]->r,pool->array[i]->g,pool->array[i]->b,0);
        SDL_RenderFillRect(ren,pool->array[i]->rect);
        }
    }
}


int collision_check(SDL_Rect rect)
{
    switch (rect.x)
    {
        
        case 0:{can_move_left=0;break;}   
        case 190:{can_move_right=0;break;}
        default:{
            can_move_left=1;
            can_move_right=1;
            break;
        }
    }

    switch (rect.y)
    {
        case 0:{can_move_up=0;break;}
        case 90:{can_move_down=0;break;}
        default:
        {
            can_move_up=1;
            can_move_down=1;
            break;
        }
    
    }
    
}

int WinMain (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    
    Rect_array* rect_pool = create_Rect_array();
    
    /* EXECUÇÃO */
    SDL_Rect r = { 40,20, 10,10 };
    SDL_Event evt;
    while (1) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        draw_rect_on_the_screen(ren,rect_pool);
        SDL_RenderPresent(ren);

        SDL_WaitEvent(&evt);
        switch(evt.type)
        {
            case SDL_KEYDOWN: 
            {
                if(collision_check(r)==1){}
                else{
                    switch (evt.key.keysym.sym) {
                        case SDLK_UP:
                        if(can_move_up)
                            r.y -= 5;
                            break;
                        case SDLK_DOWN:
                        if(can_move_down)
                            r.y += 5;
                            break;
                        case SDLK_LEFT:
                        if(can_move_left)
                            r.x -= 5;
                            break;
                        case SDLK_RIGHT:
                        if(can_move_right)
                            r.x += 5;
                            break;
                    }
                    if(evt.key.keysym.sym == SDLK_F4 && 
                        (evt.key.keysym.mod ==KMOD_LALT || evt.key.keysym.mod == KMOD_RALT) )
                        {
                            goto end;
                        }
                }
                break;
            }
            case SDL_WINDOWEVENT:
            {
                switch (evt.window.event)
                {                
                    case SDL_WINDOWEVENT_CLOSE:
                    {
                        goto end;
                        break;
                    }

                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                switch(evt.button.button)
                {
                    case SDL_BUTTON_LEFT:
                    {
                        place_on_rect_array(rect_pool,evt.button.x,evt.button.y);
                        break;
                    }       
                }
                break;
            }
        }
    }
        

    end:/* FINALIZACAO */
    destroy_Rect_array(rect_pool);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}