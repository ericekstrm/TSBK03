#pragma once

namespace tree
{

// General parameters
static const float alpha {3};    // Light conversion rate
static const float sigma {0.5};  // Light sensitivity
static const float lambda {0.48}; // Branch bias (1 = bias to main branch, 0 = bias to lateral branch)

// Default value for node properties
static const float default_radius {0.01};
static const float default_length {1};

//shadow parameters
static const float a {0.1};
static const float b {1.5};
static const float full_exposure_light {1};

static const float BM {0.01}; //{0.32}; // branch maintenance coefficient
static const float BE {1.5}; //{1.5};  // branch maintenance exponent
static const int Nmin {35};   // threshold for shedding

}