#include<SDL2/SDL.h>


int moving_right=1;
int moving_left=0;
int moving_down=0;
int moving_up=0;


int move_x=10;
int move_y=0;

int loop= 0;

void state_machine_rect(SDL_Rect* rect)
{

	if(rect->x>=100 && rect->y>=20)
	{
		moving_down=1;
		moving_right=0;
		move_y=10;
		move_x=0;	
	}
	if(rect->x>=100 && rect->y>=100)
	{
		moving_left=1;
		moving_down=0;
		move_x=-10;
		move_y=0;
	}
	if(rect->x<=20 && rect->y>=100)
	{
		moving_left=0;
		moving_up=1;
		move_y = -10;
		move_x = 0;
	}
	if(rect->x<=20 && rect->y<=20)
	{
		moving_up =0;
		moving_right=1;
		move_y=0;
		move_x=10;
		loop++;
	}
}


void move_square(SDL_Rect* rect, int x,int y)
{
	rect->x+=x;
	rect->y+=y;
}


int WinMain(int argc, char** argv)
{
	SDL_Window* window = SDL_CreateWindow("anime",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			300,200,SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);

	SDL_SetRenderDrawColor(renderer,255,255,255,0);

	SDL_RenderClear(renderer);

	SDL_Rect rect = {50,50, 20,20};

	SDL_SetRenderDrawColor(renderer,100,100,50,0);

	



	
	while(loop<10)
	{
		
		move_square(&rect,move_x,move_y);
		state_machine_rect(&rect);
		SDL_SetRenderDrawColor(renderer,255,255,255,0);

		SDL_RenderClear(renderer);
		
		SDL_SetRenderDrawColor(renderer,100,100,50,0);
		
		SDL_RenderFillRect(renderer,&rect);
		SDL_RenderPresent(renderer);
		
		SDL_Delay(33);
	}	

	SDL_Delay(500);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
