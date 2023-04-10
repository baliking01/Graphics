#ifndef CAMERA_H
#define CAMERA_H

#include "scene.h"

typedef struct Camera{
	double degX;
	double degY;
	double scaleRatio;
	double maxZoom;
}Camera;

inline unsigned int getMax(unsigned int a, unsigned int b, unsigned int c){
    if(a >= b && a >= c) return a;
    if(b >= c) return b;
    return c;
}

void initCamera(Camera* camera, Scene* scene);
void setRotationX(Camera* camera, double degX);
void setRotationY(Camera* camera, double degY);
void setScale(Camera* camera, double scaleRatio);
void normalizeCamera(Scene* scene);
void updateCamera(Scene* scene, Camera* camera);


#endif