#pragma once

#include <GLFW/glfw3.h>

bool LoadTextureFromFile(const unsigned char *filename, GLuint *out_texture, int *out_width, int *out_height);