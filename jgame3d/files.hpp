/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2022 - present
GPLv3 held by author
*/

#ifndef FILES_H
#define FILES_H

#include "basics.hpp"
#include "window.hpp"
#include <fstream>

// Save a model to a file
bool saveModel(const Model &what, const char *where);

// Load a model from a file
Model loadModel(const char *where);

#endif
