#pragma once

namespace tree
{

// General parameters
static const float alpha {3};    // Light conversion rate
static const float sigma {0.1};  // Light sensitivity
static const float lambda {0.54}; // Branch bias (1 = bias to main branch, 0 = bias to lateral branch)

//shadow parameters
static const float a {0.2};  // shadow amount from node
static const float b {1.7};   // exponent for decreasing shadow exposure lower down 
static const float full_exposure_light {1};

static const float BM {0.02}; //{0.32}; // branch maintenance coefficient
static const float BE {1.3}; //{1.5};  // branch maintenance exponent
static const int Nmin {35};   // threshold for shedding

static const float tropism {0.1}; //how much the branches bend down because of gravity



// Default value for node properties
static const float default_radius {0.005};
static const float default_length {0.5};

}