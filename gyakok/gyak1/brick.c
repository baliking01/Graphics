#include "brick.h"

void setSize(Brick *brick, double a, double b, double c){
	brick->a = a;
	brick->b = b;
	brick->c = c;
}

double getVolume(Brick *brick){
	return brick->a * brick->b * brick->c;
}

double getSurface(Brick *brick){
	double surface = 2 * ((brick->a * brick->a) + (brick->b * brick->b) + (brick->c * brick->c));
	return surface;
}

int hasSquareFace(Brick *brick){
	return (brick->a == brick->b || brick->a == brick->c || brick->b == brick->c) ? 1 : 0;
}
