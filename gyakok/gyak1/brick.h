#ifndef BRICK_H
#define BRICK_H

typedef struct Brick{
	double a;
	double b;
	double c;
}Brick;

void setSize(Brick *brick, double a, double b, double c);
double getVolume(Brick *brick);
double getSurface(Brick *brick);
int hasSquareFace(Brick *brick);

#endif