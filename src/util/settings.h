#pragma once

#include "Matrix.h"

// window properties
static const int window_width {720};
static const int window_height {720};

// OpenGL projection matrix
static const mat4 projection {fov_projection_matrix(45.0f, 1.0f, 0.1f, 100.0f)};

static const int shadow_box_size {50};
static const mat4 light_projection {ortho_projection_matrix(-shadow_box_size, shadow_box_size, -shadow_box_size, shadow_box_size, 1.0f, 10000.0f)};