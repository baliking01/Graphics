#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_LINE_COUNT 10
#define PI 3.14159265358979323846

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
 
 int getDistance(Point a, Point b){
 	return round(sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2)));
 }

 #pragma GCC diagnostic ignored "-Wunused-parameter"
 #pragma GCC diagnostic push
int main(int argc, char* argv[])
{
  int error_code;
  SDL_Window* window;
  bool need_run;
  SDL_Event event;
  SDL_Renderer* renderer;

  int xMouse = 0;
  int yMouse = 0;
  int point_count = 0;
  Line lines[MAX_LINE_COUNT];
  int line_count = 0;

  int tmpX = 0;
  int tmpY = 0;
  Color col = {1, 2, 3};
	
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

  Point red = {520, 230};
  Point green = {775, 230};
  Point blue = {650, 10};
  Point p = {0, 0};
  SDL_SetRenderDrawColor(renderer, 134, 12, 89, SDL_ALPHA_OPAQUE);
  for(int i = 0; i < 255; i++){
  	 p.x = red.x + i;
  	 p.y = red.y;
  	 SDL_SetRenderDrawColor(renderer, 255 - getDistance(p, red), 255 - getDistance(p, green), 255 - getDistance(p, blue), SDL_ALPHA_OPAQUE);
  	 SDL_RenderDrawPoint(renderer, p.x, p.y);
  	 for(int j = 0; j < 255 - i; j++){
  	 	p.x = red.x + i*cos(60*(PI/180)) + j;	
  	 	p.y = red.y - i*sin(60*(PI/180));
  	 	SDL_SetRenderDrawColor(renderer, 255 - getDistance(p, red), 255 - getDistance(p, green), 255 - getDistance(p, blue), SDL_ALPHA_OPAQUE);
  	 	SDL_RenderDrawPointF(renderer, p.x, p.y);
  	 }
  }
  SDL_RenderPresent(renderer);

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
		if(line_count < MAX_LINE_COUNT){
			SDL_GetMouseState(&xMouse,&yMouse);
			if(point_count == 0){	// Store mouse position when only 1 point was selected
				tmpX = xMouse;
				tmpY = yMouse;
				point_count++;
			}
			else if(point_count == 1){ // Store mouse position of 2nd point;
				lines[line_count] = (struct Line) {
					{tmpX, tmpY},
					{xMouse, yMouse},
					col
				};
				SDL_SetRenderDrawColor(renderer, 34, 245, 78, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawLine(renderer, 
					lines[line_count].begin.x, 
					lines[line_count].begin.y, 
					lines[line_count].end.x, 
					lines[line_count].end.y
				);

				line_count++;
				point_count = 0;

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
#pragma GCC diagnostic pop