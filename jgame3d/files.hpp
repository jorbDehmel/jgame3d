#ifndef FILES_H
#define FILES_H

#include "basics.hpp"
#include "window.hpp"

// Save a model to a file
bool saveModel(const Model &what, const char *where);;

// Load a model from a file
Model loadModel(const char *where);

#endif
