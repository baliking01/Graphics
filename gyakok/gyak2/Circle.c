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
	 double x;
	 double y;
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

void drawCircle(SDL_Renderer *renderer, Point center, double radius, int precision){
  if(radius <= 0 || precision <= 3) return;
  double deg = 360/(double)precision;
  double side_len = (radius*sin( (deg*(PI/180))/2 )) * 2;
  double offset = radius*sin( (90 - 180/precision)*(PI/180));
  double tmpX = 0;
  double tmpY = 0;

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawPointF(renderer, center.x, center.y);

  Point p = {center.x + (side_len/2), center.y - offset};
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
  double rotation = deg;
  for(int i = 0; i < precision; i++){
    tmpX = p.x + side_len*cos(rotation*(PI/180));
    tmpY = p.y + side_len*sin(rotation*(PI/180));
    SDL_RenderDrawLineF(renderer, p.x, p.y, tmpX, tmpY);
    p.x = tmpX;
    p.y = tmpY;
    rotation += deg;
  }
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

  //Color col = {1, 2, 3};
	
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

  Point o1 = {400, 300};
  Point o2 = {200, 400};
  Point o3 = {654, 210};
  double radius = 100;
  drawCircle(renderer, o1, radius, 12);
  drawCircle(renderer, o2, radius, 7);
  drawCircle(renderer, o3, radius, 27);

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