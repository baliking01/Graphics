#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#define TICK_SPEED 50

enum states{dead = 0, alive = 4};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static GLfloat vcube[8][3] = {
	{-1, 1, 1}, {1, 1, 1}, {1, -1, 1}, {-1, -1, 1},
	{-1, 1, -1}, {1, 1, -1}, {1, -1, -1}, {-1, -1, -1}
};

static GLuint faces[6][4] = {
	{1, 2, 3, 0}, {0, 4, 5, 1}, {1, 5, 6, 2},
	{2, 6, 7, 3}, {4, 0, 3, 7}, {4, 7, 6, 5}
};
#pragma GCC diagnostic pop

typedef struct Scene{
    int*** grid;    // Information about the next state gets written here
    int*** gridBuffer;  // Comparisons are done in this array to avoid data overwrite or false readings
    unsigned int gridWidth;
    unsigned int gridHeight;
    unsigned int gridDepth;
    GLfloat (*vertices)[3];
    GLuint (*faces)[4];
}Scene;

void drawBorder(Scene* scene, float (*vdata)[3], unsigned int (*faces)[4]);
void drawCube(float (*vdata)[3], unsigned int (*faces)[4]);
void initScene(Scene* scene, unsigned int width, unsigned int height, unsigned int depth, float (*vdata)[3], unsigned int (*fdata)[4]);
void fillGrid(Scene* scene, int spawnRadius, int spawnChance);
void renderGrid(Scene* scene);
void updateGrid(Scene* scene);
void updateScene(unsigned long int* elapsedTime, unsigned long int* prevTime, unsigned long int* currentTime, Scene* scene);
void deleteScene(Scene* scene);

#endif