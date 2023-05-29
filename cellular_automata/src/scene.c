#include "scene.h"
#include <math.h>

void drawBorder(Scene* scene, float (*vdata)[3], unsigned int (*faces)[4]){
    glLineWidth(2);
    glPushMatrix();
    glTranslatef(-1, -1, -1);
    glScalef(scene->gridWidth - 2, scene->gridHeight - 2, scene->gridDepth - 2);
    glTranslatef(1, 1, 1);

    glColor3f(1, 1, 1); 
    for(int i = 0; i < 6; i++){
        glBegin(GL_LINE_LOOP);
            glVertex3fv(vdata[faces[i][0]]);
            glVertex3fv(vdata[faces[i][1]]);
            glVertex3fv(vdata[faces[i][2]]);
            glVertex3fv(vdata[faces[i][3]]);
        glEnd();
    }

    glPopMatrix();
}

void drawCube(float (*vdata)[3], unsigned int (*faces)[4]){
	glLineWidth(1);
	for(int i = 0; i < 6; i++){
		glBegin(GL_QUADS);
    		glVertex3fv(vdata[faces[i][0]]);
    		glVertex3fv(vdata[faces[i][1]]);
    		glVertex3fv(vdata[faces[i][2]]);
    		glVertex3fv(vdata[faces[i][3]]);
		glEnd();
	}
}

void initScene(Scene* scene, unsigned int width, unsigned int height, unsigned int depth, float (*vdata)[3], unsigned int (*fdata)[4]){
    // Fill both grids with zeros
    scene->vertices = vdata;
    scene->faces = fdata;

    // Extra padding to avoid out of bounds indexing
    // For further info see function updateGrid()
    scene->gridWidth = width += 2;
    scene->gridHeight = height += 2;
    scene->gridDepth = depth += 2;

    scene->neighbourCount = M;
    
    scene->grid = (int***)calloc(scene->gridWidth, sizeof(int**));
    scene->gridBuffer = (int***)calloc(scene->gridWidth, sizeof(int**));

    for(unsigned int i = 0; i < scene->gridWidth; i++){
        scene->grid[i] = (int**)calloc(scene->gridHeight, sizeof(int*));
        scene->gridBuffer[i] = (int**)calloc(scene->gridHeight, sizeof(int*));

        for(unsigned int j = 0; j < scene->gridHeight; j++){
            scene->grid[i][j] = (int*)calloc(scene->gridDepth, sizeof(int));
            scene->gridBuffer[i][j] = (int*)calloc(scene->gridDepth, sizeof(int));
        }
    }
}

void fillGrid(Scene* scene, int spawnRadius, int spawnChance){
    // Initialize with random members
    for(unsigned int i = 1; i < scene->gridWidth - 1; i++){
        for(unsigned int j = 1; j < scene->gridHeight - 1; j++){
            for(unsigned int k = 1; k < scene->gridDepth - 1; k++){
                if( (i <= scene->gridWidth/2 + spawnRadius && i >= scene->gridWidth/2 - spawnRadius) &&
                    (j <= scene->gridHeight/2 + spawnRadius && j >= scene->gridHeight/2 - spawnRadius) &&
                    (k <= scene->gridDepth/2 + spawnRadius && k >= scene->gridDepth/2 - spawnRadius)) scene->gridBuffer[i][j][k] = ((rand() % spawnChance) == 1) ? alive : dead;
            }
        }
    }
}

void clearGrid(Scene* scene){
    // Initialize with random members
    for(unsigned int i = 1; i < scene->gridWidth - 1; i++){
        for(unsigned int j = 1; j < scene->gridHeight - 1; j++){
            for(unsigned int k = 1; k < scene->gridDepth - 1; k++){
                scene->gridBuffer[i][j][k] = 0;
                scene->grid[i][j][k] = 0;
            }
        }
    }
}

void renderGrid(Scene* scene){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        for(unsigned int i = 1; i < scene->gridWidth - 1 ; i++){
            glPushMatrix();
            for(unsigned int j = 1; j < scene->gridHeight - 1; j++){
                glPushMatrix();
                for(unsigned int k = 1; k < scene->gridDepth - 1; k++){
                    if(scene->grid[i][j][k]){
                        //glColor3f(1, scene->grid[i][j][k]*(1.0/alive), 0);
                        glColor3f((double)i/scene->gridWidth, (double)j/scene->gridHeight, (double)k/scene->gridDepth);
                        /*glColor3f(abs(i-(double)scene->gridWidth/2)/(double)scene->gridWidth,
                            abs(j-(double)scene->gridHeight/2)/(double)scene->gridHeight,
                            abs(k-(double)scene->gridDepth/2)/(double)scene->gridDepth);*/

                        /*glColor3f(sqrt((i-(double)scene->gridWidth/2)*(i-(double)scene->gridWidth/2) + 
                            (j-(double)scene->gridHeight/2) * (j-(double)scene->gridHeight/2) +
                            (k-(double)scene->gridDepth/2) * (k-(double)scene->gridDepth/2))/scene->gridDepth, (double)i/scene->gridWidth, (double)j/scene->gridHeight);*/
                        /*glColor3f(sqrt((i-(double)scene->gridWidth/2)*(i-(double)scene->gridWidth/2) + 
                            (j-(double)scene->gridHeight/2) * (j-(double)scene->gridHeight/2) +
                            (k-(double)scene->gridDepth/2) * (k-(double)scene->gridDepth/2))/scene->gridDepth, 0.2 ,0.3);*/
                        drawCube(scene->vertices, scene->faces);
                    }
                    glTranslatef(0, 0, 2);
                }
                glPopMatrix();
                glTranslatef(0, 2, 0);
            }
            glPopMatrix();
            glTranslatef(2, 0, 0);
        }
    glPopMatrix();
}

void updateGrid(Scene* scene){
    // Update the grid based on rules of automata
    // Iterate over the buffergrid and write the result to grid according to the rules
    // Make buffergrid = grid

    // Overpopulation - neighbour upper bound
  	// Underpopulation - neightbour lower bound 
  	// Reproduction stage - optimal neighbour count to reproduce

    // Neighbour count
    int n = 0;
    for(unsigned int i = 1; i < scene->gridWidth - 1; i++){
        for(unsigned int j = 1; j < scene->gridHeight - 1; j++){
            for(unsigned int k = 1; k < scene->gridDepth - 1; k++){
                // Count neighours in 3x3 area around cell
                n = countAdj(scene, i, j, k);
                
                // Insert rule conditions
                // Determine the next state of the cell

                // Rule B3/S23
                //scene->grid[i][j][k] = (scene->gridBuffer[i][j][k] && !((n<2) || (n>3))) ^ (!scene->gridBuffer[i][j][k] && (n==3));

                // Rule B3678/S34678
                //scene->grid[i][j][k] = (scene->gridBuffer[i][j][k] && !(((n<3) || (n>8))) && n != 5) ^ (!scene->gridBuffer[i][j][k] && ((n == 3) || (n >= 6 && n <= 8)));


                // Rule 4/4/5/M
                /*
                if(scene->gridBuffer[i][j][k] == dead && n == 4){
                    scene->grid[i][j][k] = alive;
                }
                else if(scene->gridBuffer[i][j][k] == alive && n == 4){
                    scene->grid[i][j][k] = alive;
                }
                else if(scene->gridBuffer[i][j][k]){
                    scene->grid[i][j][k] = scene->gridBuffer[i][j][k] - 1;
                }*/


                // Rule 2,6,9/4,6,8,9/10/M
                /*if((scene->gridBuffer[i][j][k] == dead && n == 4)
                    || (scene->gridBuffer[i][j][k] == dead && n == 6)
                    || (scene->gridBuffer[i][j][k] == dead && n == 8)
                    || (scene->gridBuffer[i][j][k] == dead && n == 9)){
                    scene->grid[i][j][k] = alive;
                }
                else if((scene->gridBuffer[i][j][k] == alive && n == 2)
                        || (scene->gridBuffer[i][j][k] == alive && n == 6)
                        || (scene->gridBuffer[i][j][k] == alive && n == 9)){
                    scene->grid[i][j][k] = alive;
                }
                else if(scene->gridBuffer[i][j][k]){
                    scene->grid[i][j][k] = scene->gridBuffer[i][j][k] - 1;
                }*/

                // Rule 0-6/1,3/2/VN
                if((scene->gridBuffer[i][j][k] == dead && n == 3)){
                    scene->grid[i][j][k] = alive;
                }
                else if((scene->gridBuffer[i][j][k] == alive && n == 4)
                    || (scene->gridBuffer[i][j][k] == alive && n == 5)
                    || (scene->gridBuffer[i][j][k] == alive && n == 6)){
                    scene->grid[i][j][k] = alive;
                }
                else if(scene->gridBuffer[i][j][k]){
                    scene->grid[i][j][k] = scene->gridBuffer[i][j][k] - 1;
                }
            }
        }
    }

    // Update gridbuffer
    for(unsigned int i = 1; i < scene->gridWidth - 1; i++){
        for(unsigned int j = 1; j < scene->gridHeight - 1; j++){
            for(unsigned int k = 1; k < scene->gridDepth - 1; k++){
                scene->gridBuffer[i][j][k] = scene->grid[i][j][k];
            }
        }
    }
}

void deleteScene(Scene* scene){
    free(scene->grid);
    free(scene->gridBuffer);
}

void updateScene(unsigned long int* elapsedTime, unsigned long int* prevTime, unsigned long int* currentTime, Scene* scene){
    *currentTime = SDL_GetTicks();
    *elapsedTime += *currentTime - *prevTime;
    *prevTime = *currentTime;

    if(*elapsedTime > TICK_SPEED) {
        updateGrid(scene);
        *elapsedTime = 0;
    }
}