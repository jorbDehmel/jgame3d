#include "files.hpp"
#include <stream>

/*
Model file structure:

Numpoints, r, g, b, a
x, y, z...
<New polygon>

Ie
4, r, g, b, a
x, y, z, x, y, z, x, y, z, x, y, z

2, r, g, b, a
x, y, z, x, y, z
*/

bool saveModel(const Model &what, const char *where)
{
    ofstream file(where);
    if (!file.is_open())
        return false;
    
    for (auto polygon : what.polygons)
    {
        file << polygon.points.size() << ", "
             << polygon.color.r << ", " << polygon.color.g << ", "
             << polygon.color.b << ", " << polygon.color.a << '\n';
        
        for (auto point : polygon.points)
        {
            file << point.x << ", " << point.y << ", " << point.z << ", ";
        }
    }

    file.close();
    return true;
}

Model loadModel(const char *where)
{
   // Todo: implement this
}
