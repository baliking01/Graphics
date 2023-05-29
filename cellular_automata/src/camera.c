#include "camera.h"

// Initialize the camera
void initCamera(Camera* camera, Scene* scene){
	camera->degX = 0;
	camera->degY = 0;
	camera->scaleRatio = 1;
	camera->maxZoom = getMax(scene->gridWidth, scene->gridHeight, scene->gridDepth);
}

// Change camera orientaiton
void setRotationX(Camera* camera, double degX){
	camera->degX = degX;
}
void setRotationY(Camera* camera, double degY){
	camera->degY = degY;
}

// Change camera zoom
void setScale(Camera* camera, double scaleRatio){
	camera->scaleRatio = scaleRatio;
}

// Determine optimal maximum zoom distance;


// Move the camera to the viewing position (correct distance away from rendered scene)
void normalizeCamera(Scene* scene){
    unsigned int scale = getMax(scene->gridWidth, scene->gridHeight, scene->gridDepth) * 1.6;
    glScalef(0.9/scale, 0.9/scale, 0.9/scale);
    // Move tha camera back and adjust for cell size (2) and array padding (2)
	glTranslatef(-((double)scene->gridWidth - 3), -((double)scene->gridHeight - 3), -((double)scene->gridDepth - 3));
}

// Update camera (schould be called every frame)
void updateCamera(Scene* scene, Camera* camera){
	glScalef(camera->scaleRatio, camera->scaleRatio, camera->scaleRatio);
	glRotatef(camera->degY, 1, 0, 0);
	glRotatef(camera->degX, 0, 1, 0);
	normalizeCamera(scene);
}