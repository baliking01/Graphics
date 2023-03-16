#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_LINE_COUNT 10

/**
 * SDL2 example
 */
 
 typedef struct Point{
	 int x;
	 int y;
 }Point;
 
 typedef struct Color{
	 unsigned int red;
	 unsigned int green;
	 unsigned int blue;
 }Color;
 
 typedef struct Line{
	 Point begin;
	 Point end;
	 Color color;
 }Line;
 
int main(int argc, char* argv[])
{
  int error_code;
  SDL_Window* window;
  bool need_run;
  SDL_Event event;
  SDL_Renderer* renderer;
  int i;
  int xMouse = 0;
  int yMouse = 0;
  int point_count = 0;
  Line lines[MAX_LINE_COUNT];
  int current_lines_number = 0;
  Point p;
  Color col = { 1, 2 ,3};
	
  error_code = SDL_Init(SDL_INIT_EVERYTHING);
  if (error_code != 0) {
    printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
    return error_code;
  }

  window = SDL_CreateWindow(
    "Hello SDL!",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    WIDTH, HEIGHT, 0);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  
  //Color
  //SDL_SetRenderDrawColor(renderer, 255, i, 0, SDL_ALPHA_OPAQUE);

  need_run = true;
  while (need_run) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_KEYDOWN:
        case SDL_SCANCODE_Q:
        need_run = false;
        break;
      case SDL_QUIT:
        need_run = false;
        break;
	  case SDL_MOUSEBUTTONDOWN:
		if(current_lines_number < MAX_LINE_COUNT){
			SDL_GetMouseState(&xMouse,&yMouse);
			if(point_count == 2){
				SDL_RenderDrawLine(renderer, 
				lines[current_lines_number].begin.x, 
				lines[current_lines_number].begin.y, 
				lines[current_lines_number].end.x, 
				lines[current_lines_number].end.y);
				current_lines_number++;
			}
			else if(point_count == 0){
				Line l = { 
					{xMouse, yMouse},
					{-1, -1}, 
					col};
				lines[current_lines_number] = l; 
				point_count++;
			}
			else if(point_count == 1){
				Line l = { 
				{-1, -1},
				{xMouse, yMouse},
				col};
				lines[current_lines_number] = l;
				point_count++;
			}
		}
		else{
			printf("Exceeded maximum number of lines!\n");
		}
			printf("%d %d,\n", xMouse, yMouse);
		break;
	  default:
		break;
	  }
    }
	SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
