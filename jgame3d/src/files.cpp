/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2022 - present
GPLv3 held by author
*/

#include "../files.hpp"

bool saveModel(const Object &what, const char *where)
{
    ofstream file(where);
    if (!file.is_open())
        return false;

    file << what.triangles.size() << '\n';
    for (auto tri : what.triangles)
    {
        file << tri.color.r << " " << tri.color.g << " "
             << tri.color.b << " " << tri.color.a << '\n';

        file << tri.a.x << ' ' << tri.a.y << ' ' << tri.a.z << '\n'
             << tri.b.x << ' ' << tri.b.y << ' ' << tri.b.z << '\n'
             << tri.c.x << ' ' << tri.c.y << ' ' << tri.c.z << '\n';

        file << "\n";
    }

    file.close();
    return true;
}

Object loadModel(const char *where)
{
    ifstream file(where);
    if (!file.is_open())
        throw runtime_error("Cannot open input file\n");

    Object out;

    int numTriangles;
    file >> numTriangles;
    for (int i = 0; i < numTriangles; i++)
    {
        Triangle toAdd;
        file >> toAdd.color.r >> toAdd.color.g >> toAdd.color.b >> toAdd.color.a;
        file >> toAdd.a.x >> toAdd.a.y >> toAdd.a.z >> toAdd.b.x >> toAdd.b.y >> toAdd.b.z >> toAdd.c.x >> toAdd.c.y >> toAdd.c.z;

        out.triangles.push_back(toAdd);
    }

    file.close();

    return out;
}
