#include <stdio.h>
#include "brick.h"

int main(){

	Brick brick = {1, 2, 3};
	Brick brick2;
	printf("Sides: %.2lf %.2lf %.2lf\n", brick.a, brick.b, brick.c);


	setSize(&brick2, 3, 5, 3);
	printf("Sides of new brick: %.2lf %.2lf %.2lf\n", brick2.a, brick2.b, brick2.c);
	double volume = getVolume(&brick2);
	double surface = getSurface(&brick2);
	int has = hasSquareFace(&brick2);

	printf("Volume: %.2lf, Surface area: %.2lf, Has square surface: %s",
			volume, surface, (has) ? "True" : "False");

	return 0;
}