#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#define TICK_SPEED 50
#define VN 0 // Von Neumann
#define M 1 // Moore

enum states{dead = 0, alive = 1};

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
    unsigned int neighbourCount;
    unsigned int currentRule;
}Scene;

inline unsigned int countAdj(Scene* scene, unsigned int i, unsigned int j, unsigned int k){
    int n = 0;
    switch(scene->neighbourCount){
        case VN: 
            n += (scene->gridBuffer[i+1][j][k] == alive);
            n += (scene->gridBuffer[i-1][j][k] == alive);

            n += (scene->gridBuffer[i][j+1][k] == alive);
            n += (scene->gridBuffer[i][j-1][k] == alive);
            
            n += (scene->gridBuffer[i][j][k+1] == alive);
            n += (scene->gridBuffer[i][j][k-1] == alive);
            break;
        case M: 
            for(int offset = 1; offset >= -1; offset--){
                // Top row
                n += (scene->gridBuffer[i-1][j+1][k-offset] == alive);
                n += (scene->gridBuffer[i][j+1][k-offset] == alive);
                n += (scene->gridBuffer[i+1][j+1][k-offset] == alive);

                // Middle row
                n += (scene->gridBuffer[i-1][j][k-offset] == alive);
                n += (scene->gridBuffer[i][j][k-offset] == alive);
                n += (scene->gridBuffer[i+1][j][k-offset] == alive);

                // Bottom row
                n += (scene->gridBuffer[i-1][j-1][k-offset] == alive);
                n += (scene->gridBuffer[i][j-1][k-offset] == alive);
                n += (scene->gridBuffer[i+1][j-1][k-offset] == alive);
            }
            // We also counted the current cell, so we need to substract it.
            // Even if it was 0 this ensures that we have an accurate neighbour count
            n -= (scene->gridBuffer[i][j][k] > 0);
            break;
        default: break;
    }
    return n;
}

inline void applyRule(){

}

void drawBorder(Scene* scene, float (*vdata)[3], unsigned int (*faces)[4]);
void drawCube(float (*vdata)[3], unsigned int (*faces)[4]);
void initScene(Scene* scene, unsigned int width, unsigned int height, unsigned int depth, float (*vdata)[3], unsigned int (*fdata)[4]);
void fillGrid(Scene* scene, int spawnRadius, int spawnChance);
void renderGrid(Scene* scene);
void updateGrid(Scene* scene);
void updateScene(unsigned long int* elapsedTime, unsigned long int* prevTime, unsigned long int* currentTime, Scene* scene);
void deleteScene(Scene* scene);
void clearGrid(Scene* scene);

#endif