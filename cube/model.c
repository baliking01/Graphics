#include "model.h"
#include <stdlib.h>
#include <stdio.h>

// Initialize model with empty values
void initModel(Model* model){
	model->vertex_count = 0;
	model->texture_vertex_count = 0;
	model->normal_count = 0;
	model->triangle_count = 0;

	model->vertices = NULL;
	model->normals = NULL;
	model->texture_vertices = NULL;
	model->triangles = NULL;
}

// Allocate memory for its properties
void allocateModel(Model* model){
	model->vertices 		= (Vertex*)			calloc(model->vertex_count + 1, sizeof(Vertex));
    model->texture_vertices = (TextureVertex*)	calloc(model->texture_vertex_count + 1, sizeof(TextureVertex));
    model->normals 			= (Vertex*)			calloc(model->normal_count + 1, sizeof(Vertex));
    model->triangles 		= (Triangle*)		calloc(model->triangle_count, sizeof(Triangle));
}

// Free unused memory and reset model properties
void clearModel(Model* model){
	free(model->vertices);
	free(model->normals);
	free(model->texture_vertices);
	free(model->triangles);

	initModel(model);
}

void getProperties(Model* model){
	if(model == NULL){
		return;
	}

	printf( "Vertex count: \t\t%d\n"
			"Texture Vertex count: \t%d\n"
			"Normal count: \t\t%d\n"
			"Triangles count: \t%d\n",
			model->vertex_count,
			model->texture_vertex_count,
			model->normal_count,
			model->triangle_count);
}