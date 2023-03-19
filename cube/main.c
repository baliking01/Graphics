#include <stdio.h>
#include "model.h"
#include "load.h"

int main(){
	printf("Model header loaded!\n");
	Model cube;
	initModel(&cube);

	getProperties(&cube);
	if(!loadModel(&cube, "test.txt")){
		printf("File not found\n");
	}

	getProperties(&cube);
	for(int i = 0; i < cube.triangle_count; i++){
		printf("%d ", cube.triangles[i].points[2].vertex_index);
	}
	return 0;
}