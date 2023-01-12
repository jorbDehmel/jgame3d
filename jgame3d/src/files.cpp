#include "../files.hpp"

bool saveModel(const Model &what, const char *where)
{
    ofstream file(where);
    if (!file.is_open())
        return false;

    for (auto polygon : what.polygons)
    {
        file << polygon.points.size() << " "
             << polygon.color.r << " " << polygon.color.g << " "
             << polygon.color.b << " " << polygon.color.a << '\n';

        for (auto point : polygon.points)
        {
            file << point.x << " " << point.y << " " << point.z << " ";
        }

        file << "\n\n";
    }

    file.close();
    return true;
}

Model loadModel(const char *where)
{
    ifstream file(where);
    if (!file.is_open())
        throw runtime_error("Cannot open output file\n");

    Model out;
    while (!file.eof())
    {
        int num;
        Polygon poly;

        file >> num;
        file >> poly.color.r >> poly.color.g >> poly.color.b >> poly.color.a;

        for (int i = 0; i < num; i++)
        {
            Point3D point;
            file >> point.x >> point.y >> point.z;
            poly.points.push_back(point);
        }

        out.polygons.push_back(poly);

        if (file.eof())
            break;
    }
    file.close();

    return out;
}
