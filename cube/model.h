#ifndef MODEL_H
#define MODEL_H

//vec3
typedef struct Vertex{
	double x;
	double y;
	double z;
} Vertex;

// Texture coordinates used for 2D texture mapping
typedef struct TextureVertex{
	double u;
	double v;
} TextureVertex;

// Point on the face
typedef struct FacePoint{
    int vertex_index;
    int texture_index;
    int normal_index;
} FacePoint;

// Surface face divided into triangles
typedef struct Triangle{
	FacePoint points[3];
} Triangle;


// Define an object with the following properties
typedef struct Model{
	// Size of each property
	int vertex_count;
	int texture_vertex_count;
	int normal_count;
	int triangle_count;

	// Arrays of properties
	Vertex* vertices;
	Vertex* normals;	// Use vertex struct as vec3 for normals
	TextureVertex* texture_vertices;
	Triangle* triangles;
}Model;

typedef enum {
    NONE,
    VERTEX,
    TEXTURE_VERTEX,
    NORMAL,
    FACE
} ElementType;

// Initialize model with empty values
void initModel(Model* model);

// Allocate memory for its properties
void allocateModel(Model* model);

// Free unused memory
void freeModel(Model* model);

void getProperties(Model* model);

#endif