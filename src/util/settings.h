#pragma once

#include "Matrix.h"

// window properties
static int window_width = 720;
static int window_height = 720;

// OpenGL projection matrix
static mat4 projection {fov_projection_matrix(45.0f, 1.0f, 0.1f, 100.0f)};