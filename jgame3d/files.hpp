/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2022 - present
GPLv3 held by author
*/

#ifndef FILES_H
#define FILES_H

#include "jtri.hpp"
#include <fstream>

// Save a model to a file
bool saveModel(const Object &what, const char *where);

// Load a model from a file
Object loadModel(const char *where);

#endif
