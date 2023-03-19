#include "load.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

int loadModel(Model* model, const char* path){
	FILE *fp = fopen(path, "r");
	int result = 0;
	if(!fp){
		printf("Could not access %s\n", path);
		return result;
	}

	char line[BUFFER_SIZE];
	char *token;

	// Auxilliary variables for tokenizing faces
	char *auxToken;
	char *auxLine;
	char auxBuffer[BUFFER_SIZE];

	countElements(model, fp);
	fseek(fp, 0, SEEK_SET);
	allocateModel(model);

	// Increase index up to the respective count
	int remaining_vertex = model->vertex_count - 1;
	int remaining_texture_vertex = model->texture_vertex_count - 1;
	int remaining_normal = model->normal_count - 1;
	int remaining_triangles = model->triangle_count;	// Indexing of faces starts at 0

	int index;
	int triangle_point_index = 0;
	int currentLine = 0;

	while(fgets(line, BUFFER_SIZE, fp) != NULL){
		currentLine++;
		// Split line into tokens and get the first one
		token = strtok(line, " \n");
		
		// Ensure that only lines prefixed with the predefined notations get processed
		if(token != NULL){
			if(strcmp(token, "v") == 0){ // Process Vertecies
				index = model->vertex_count - remaining_vertex;

				if(!isDigit(token = strtok(NULL, " \n"))) {	printf("Invalid 'x' component of vertex at '%s' on line: %d\n", token, currentLine);	return result; }
				model->vertices[index].x = atof(token);

				if(!isDigit(token = strtok(NULL, " \n"))) {	printf("Invalid 'y' component of vertex at '%s' on line: %d\n", token, currentLine);	return result; }
				model->vertices[index].y = atof(token);

				if(!isDigit(token = strtok(NULL, " \n"))) {	printf("Invalid 'z' component of vertex at '%s' on line: %d\n", token, currentLine);	return result; }
				model->vertices[index].z = atof(token);
				remaining_vertex--;
			}
			else if(strcmp(token, "vt") == 0){ // Process Vertex textures
				index = model->texture_vertex_count - remaining_texture_vertex;

				if(!isDigit(token = strtok(NULL, " \n"))) {	printf("Invalid 'u' component of texture vertex at '%s' on line: %d\n", token, currentLine);	return result; }
				model->texture_vertices[index].u = atof(token);

				if(!isDigit(token = strtok(NULL, " \n"))) {	printf("Invalid 'v' component of texture vertex at '%s' on line: %d\n", token, currentLine);	return result; }
				model->texture_vertices[index].v = atof(token);

				remaining_texture_vertex--;
			}
			else if(strcmp(token, "vn") == 0){ // Process Vertex Normals
				index = model->normal_count - remaining_normal;

				if(!isDigit(token = strtok(NULL, " \n"))) {	printf("Invalid 'x' component of normal at '%s' on line: %d\n", token, currentLine);	return result; }
				model->normals[index].x = atof(token);

				if(!isDigit(token = strtok(NULL, " \n"))) {	printf("Invalid 'y' component of normal at '%s' on line: %d\n", token, currentLine);	return result; }
				model->normals[index].y = atof(token);

				if(!isDigit(token = strtok(NULL, " \n"))) {	printf("Invalid 'z' component vertex at '%s' on line: %d\n", token, currentLine);	return result; }
				model->normals[index].z = atof(token);
				remaining_normal--;
			}
			else if(strcmp(token, "f") == 0){ // Read face data
				index = model->triangle_count - remaining_triangles;
				for (auxLine = strtok (line, " \n"); auxLine != NULL; auxLine = strtok (auxLine + strlen (auxLine) + 1, " \n")) {
				    strncpy (auxBuffer, auxLine, sizeof (auxBuffer));
				    if(strcmp(auxBuffer, "f") != 0) {
				    	printf ("%d.Triangle: %s\n", index, auxBuffer);
					    triangle_point_index = 0;
					}
				    for (auxToken = strtok (auxBuffer, "/"); auxToken != NULL; auxToken = strtok (auxToken + strlen (auxToken) + 1, "/")) { 
				    	if(strcmp(auxBuffer, "f") != 0){
				    		printf ("%d.Token: %s\n", triangle_point_index , auxToken);
				    		switch(triangle_point_index){
				    			case 0:
				    				if(!isDigit(auxToken)) { printf("Invalid 'vertex' of point at '%s', '%s' on line: %d\n", auxLine, auxToken, currentLine); return result; }
				    				model->triangles[index].points[triangle_point_index].vertex_index = atof(auxToken);
				    				break;
				    			case 1:
				    				if(!isDigit(auxToken)) { printf("Invalid 'texture' of point at '%s', '%s' on line: %d\n", auxLine, auxToken, currentLine); return result; }
				    				model->triangles[index].points[triangle_point_index].texture_index = atof(auxToken);
				    				break;
				    			case 2:
				    			if(!isDigit(auxToken)) { printf("Invalid 'normal' of point at '%s', '%s' on line: %d\n", auxLine, auxToken, currentLine); return result; }
				    				model->triangles[index].points[triangle_point_index].normal_index = atof(auxToken);
				    				break;
				    			default:
				    				break;
				    		}
				    		triangle_point_index++;
				    	}
				    }
				}
				remaining_triangles--;
			}
		}
	}

	fclose(fp);
	result = 1;

	return result;
}

void countElements(Model* model, FILE* fp){
	char line[BUFFER_SIZE];
	char *token = NULL;

	while(fgets(line, BUFFER_SIZE, fp) != NULL){
		token = strtok(line, " \n");
		if(token != NULL){
			if(strcmp(token, "v") == 0){ // Count Vertecies
				model->vertex_count++;
			}
			else if(strcmp(token, "vt") == 0){ // Count Vertex textures
				model->texture_vertex_count++;
			}
			else if(strcmp(token, "vn") == 0){ // Count Vertex Normals
				model->normal_count++;
			}
			else if(strcmp(token, "f") == 0){ // Cout Triangles (faces)
				model->triangle_count++;
			}
		}
	}
}

int isDigit(char* str){
	if(str == NULL) return 0;
	return atof(str) || (((*str >= '0' && *str <= '9') || *str == '-') && (atof(str) == 0));
}