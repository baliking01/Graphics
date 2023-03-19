#ifndef LOAD_H
#define LOAD_H

#include "model.h"
#include <stdlib.h>
#include <stdio.h>

int loadModel(Model* model, const char* path);

void countElements(Model* model, FILE* fp);

int isDigit(char* str);

#endif