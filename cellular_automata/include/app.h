#ifndef APP_H
#define APP_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <camera.h>

typedef struct App{
    SDL_Window* window;
    SDL_GLContext gl_context;
    Scene scene;
    Camera camera;
    unsigned long int prevTime;
    unsigned long int elapsedTime;
    unsigned long int currentTime;
    bool need_run;
}App;

void draw_origin();
void initApp(App* app, unsigned int width, unsigned int height);
void initOpenGl(App* app, unsigned int width, unsigned int height);
void handleEvents(App* app);
void renderApp(App* app);
void destroyApp(App* app);

#endif