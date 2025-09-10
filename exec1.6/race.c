#include <SDL2/SDL.h>


const int WINNING_LINE = 250;


typedef enum state_race
{
    OVER,
    ONCOURSE
}state_race;

typedef struct Race
{
    int winner;
    int competiton_checker[3];
    state_race status;
}Race;

Race* create_Race()
{
    Race* race  = (Race*)malloc(sizeof(Race));
    race->winner=-1;
    for(int i=0;i<3;i++)
    {
        race->competiton_checker[i]=0;
    }
    race->status = ONCOURSE;
    return race;
} 


void move_time_rect(SDL_Rect* rect,double delta_time)
{
    rect->x+=0.1*delta_time;
}

void check_crossing_line(SDL_Rect competitor[], Race*race)
{
    for(int i =0; i<3;i++)
    if(competitor[i].x>=WINNING_LINE && race->competiton_checker[i]==0)
        {
            if(race->winner==-1){race->winner = i;}
            race->competiton_checker[i]=1;
                
        }   
}

int check_end_of_the_race(Race* race)
{
    for(int i =0; i<3;i++)
    {
        if(race->competiton_checker[i]==0){return 0;}
    }
    race->status=OVER;
    return 1;
}



void process_input(SDL_Event* event,SDL_Rect* k_rect,SDL_Rect* m_rect, double delta_time)
{
    switch (event->type)
    {
        case SDL_KEYDOWN:
        {
            switch(event->key.keysym.sym)
            {
                case SDLK_RIGHT:
                {
                    k_rect->x+= 1 * delta_time;
                    break;
                }
            }
            break;   
        }
        
        case SDL_MOUSEMOTION:
        {
            m_rect->x+=1*delta_time;
            break;
        }
        break;
    }
}


void show_race_results(int winner)
{
    
    switch (winner)
    {
        //mouse rect
        case 0:{
            printf("keyboard rectangle wins!\n");
            break;
        }
            //keyboard_rect
        case 1:
        {
            printf("mouse rectangle wins!\n");
            break;
        }
            //time_rect
        case 2:
        {
            printf("time rectangle wins!\n");
            break;
        }
    }
}

void render_update(SDL_Renderer*renderer,SDL_Rect objects[])
{
    SDL_SetRenderDrawColor(renderer,255,255,255,0);
    SDL_RenderClear(renderer);
    
    //DRAW Winning line
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, WINNING_LINE, 0, WINNING_LINE, 300);


    //DRAW RECT_MOUSE
    SDL_SetRenderDrawColor(renderer,255,0,0,0);
    SDL_RenderFillRect(renderer,&objects[1]);
    //DRAW KEYBOARD_MOUSE
    SDL_SetRenderDrawColor(renderer,0,255,0,0);
    SDL_RenderFillRect(renderer,&objects[0]);
    //DRAW TIME_MOUSE
    SDL_SetRenderDrawColor(renderer,0,0,255,0);
    SDL_RenderFillRect(renderer,&objects[2]);
    
    //Render the scene
    SDL_RenderPresent(renderer);

}

void reset_race(SDL_Rect competitors[],Race* race)
{
    for(int i =0; i<3;i++)
    {
        competitors[i].x=0;
        race->competiton_checker[i]=0;
    }
    race->winner = -1;
    race->status=ONCOURSE;
    
}

int WinMain(int argc, char** argv)
{
    SDL_Window* window = SDL_CreateWindow("race",
        SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
        400,300,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer= SDL_CreateRenderer(window,-1,0);
    
    Race* race = create_Race();

    SDL_Rect mouse_rect = {0,100,30,30};
    
    SDL_Rect keyboard_rect = {0,200,30,30};

    SDL_Rect time_rect={0,250,30,30};
    
    SDL_Rect competitors[3]= {keyboard_rect,mouse_rect,time_rect};

    SDL_Event event;

    int running =1;
    int printed =0;
    
    Uint64 current_frame = SDL_GetPerformanceCounter();
    Uint64 last_frame = 0;
    double delta_time = 0;

    while(running)
    {
        last_frame = current_frame;
        current_frame = SDL_GetPerformanceCounter();
        delta_time = ((current_frame - last_frame)*1000/(double)SDL_GetPerformanceFrequency());
        int isEvent =SDL_WaitEventTimeout(&event,33); 
        
        //LOGIC

        if (isEvent) 
        {
            if (event.type == SDL_QUIT) 
            {
                running =0;
            }
        
            if (race->status == ONCOURSE) {
                process_input(&event, &competitors[0], &competitors[1],delta_time);
            }
        
            if (race->status == OVER && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
                reset_race(competitors, race);
                printed = 0;
            }
        }

        if (race->status == ONCOURSE) 
        {
            move_time_rect(&competitors[2], delta_time);
            check_crossing_line(competitors, race);
            check_end_of_the_race(race);
        } 
        else 
        {
            if (!printed) 
            {
                printf("Please press r to restart the race\n");
                show_race_results(race->winner);
                printed = 1;
            }
        }
        
        render_update(renderer, competitors);
    }

    free(race);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}