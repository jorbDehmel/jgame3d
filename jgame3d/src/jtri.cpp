/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
GPLv3 held by author
*/

#include "../jtri.hpp"

double dy = 1;
double h = 512;
double w = 512;
double FOVScalar = 200;
Point focus{w / 2, h / 2, 2000};

double renderMinX = -500, renderMinY = -500;
double renderMaxX = w + 500, renderMaxY = h + 500;
Uint32 windowFlags = SDL_WINDOW_OPENGL;

double drand(const double &Min, const double &Max)
{
    return Min + (double)rand() / (RAND_MAX) * (Max - Min);
}

Camera::Camera() : cameraRot{0, 0, 0}, cameraPos{0, 0, 0}
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(w, h, windowFlags, &wind, &rend);
    return;
}

Camera::~Camera()
{
    SDL_DestroyWindow(wind);
    SDL_DestroyRenderer(rend);
    SDL_Quit();
    return;
}

void Camera::clear(const SDL_Color &BGC)
{
    SDL_SetRenderDrawColor(rend, BGC.r, BGC.g, BGC.b, BGC.a);
    SDL_RenderClear(rend);
    return;
}

void Camera::present()
{
    SDL_RenderPresent(rend);
    return;
}

bool isSafe(const Point &P)
{
    if (P.x > renderMinX && P.x < renderMaxX)
    {
        if (P.y > renderMinY && P.y < renderMaxY)
        {
            if (P.z > 0 && P.z < focus.z)
            {
                return true;
            }
        }
    }
    return false;
}

struct __sortByZ
{
    bool operator()(const Triangle l, const Triangle r) const
    {
        return max(max(r.a.z, r.b.z), r.c.z) > max(max(l.a.z, l.b.z), l.c.z);
    }
};

void Camera::update()
{
    Triangle toRender;

    priority_queue<Triangle, vector<Triangle>, __sortByZ> triangles;

    for (auto o : objects)
    {
        for (auto t : o.triangles)
        {
            toRender = t;

            // Object location
            toRender = rotate(toRender, Point{0, 0, 0}, o.rot);
            toRender = move(toRender, o.offset);

            // Camera location
            toRender = move(toRender, cameraPos);

            toRender = rotate(toRender, Point{w / 2, h, 0}, cameraRot);
            if (!isSafe(toRender.a) || !isSafe(toRender.b) || !isSafe(toRender.c))
            {
                continue;
            }

            // Add to our priority queue
            triangles.push(toRender);
        }
    }

    Triangle2D projected;
    while (!triangles.empty())
    {
        projected = project(triangles.top());
        triangles.pop();

        render(projected, rend);
    }

    return;
}

Point rotate(const Point &What, const Point &About, const Rotation &By)
{
    // cout << "Rot: " << By.x << '\t' << By.y << '\t' << By.z << '\n';

    Point out{What};

    out.x -= About.x;
    out.y -= About.y;
    out.z -= About.z;

    double c = 0, s = 0;

    if (By.x != 0)
    {
        c = SDL_cosf(By.x);
        s = SDL_sinf(By.x);
        double y = out.y, z = out.z;

        out.y = y * c - z * s;
        out.z = y * s + z * c;
    }

    if (By.y != 0)
    {
        c = SDL_cosf(By.y);
        s = SDL_sinf(By.y);
        double x = out.x, z = out.z;

        out.x = x * c + z * s;
        out.z = -x * s + z * c;
    }

    if (By.z != 0)
    {
        c = SDL_cosf(By.z);
        s = SDL_sinf(By.z);
        double x = out.x, y = out.y;

        out.x = x * c - y * s;
        out.y = x * s + y * c;
    }

    out.x += About.x;
    out.y += About.y;
    out.z += About.z;

    return out;
}

Point2D rotate(const Point2D &What, const Point2D &About, const double &By)
{
    if (By == 0)
    {
        return What;
    }

    Point2D out{What};

    out.x -= About.x;
    out.y -= About.y;

    // (xcos(By) - ysin(By), ycos(By) + xsin(By))
    double c = SDL_cosf(By), s = SDL_sinf(By);
    out.x = out.x * c - out.y * s;
    out.y = out.y * c + out.x * s;

    out.x += About.x;
    out.y += About.y;

    return out;
}

Triangle rotate(const Triangle &What, const Point &About, const Rotation &By)
{
    Triangle out = What;
    out.a = rotate(What.a, About, By);
    out.b = rotate(What.b, About, By);
    out.c = rotate(What.c, About, By);
    return out;
}

Triangle2D rotate(const Triangle2D &What, const Point2D &About, const double &By)
{
    Triangle2D out = What;
    out.a = rotate(What.a, About, By);
    out.b = rotate(What.b, About, By);
    out.c = rotate(What.c, About, By);
    return out;
}

Object rotate(const Object &What, const Point &About, const Rotation &By)
{
    Object out = What;
    for (int i = 0; i < out.triangles.size(); i++)
    {
        out.triangles[i] = rotate(out.triangles[i], About, By);
    }
    return out;
}

Point move(const Point &What, const Point &By)
{
    return Point{What.x + By.x, What.y + By.y, What.z + By.z};
}

Point2D move(const Point2D &What, const Point2D &By)
{
    return Point2D{What.x + By.x, What.y + By.y};
}

Triangle move(const Triangle &What, const Point &By)
{
    Triangle out = What;
    out.a = move(What.a, By);
    out.b = move(What.b, By);
    out.c = move(What.c, By);
    return out;
}

Triangle2D move(const Triangle2D &What, const Point2D &By)
{
    Triangle2D out = What;
    out.a = move(What.a, By);
    out.b = move(What.b, By);
    out.c = move(What.c, By);
    return out;
}

Object move(const Object &What, const Point &By)
{
    Object out = What;
    for (int i = 0; i < out.triangles.size(); i++)
    {
        out.triangles[i] = move(out.triangles[i], By);
    }
    return out;
}

Point2D project(const Point &What)
{
    if (!isSafe(What))
    {
        return Point2D{renderMinX - 1, renderMinY - 1};
    }

    Point2D out{What.x - focus.x, What.y - focus.y};

    out.x *= (FOVScalar / What.z);
    out.y *= (FOVScalar / What.z);

    out.x += focus.x;
    out.y += focus.y;

    return out;
}

Triangle2D project(const Triangle &What)
{
    Triangle2D out;
    out.a = project(What.a);
    out.b = project(What.b);
    out.c = project(What.c);
    out.color = What.color;
    return out;
}

// Runs in ~(C + h/dy)
// For constant C, height h, and dy
void render(const Triangle2D &What, SDL_Renderer *With)
{
    if ((int)What.a.y == (int)What.b.y && (int)What.a.y == (int)What.c.y)
    {
        return;
    }

    SDL_SetRenderDrawColor(With, What.color.r, What.color.g, What.color.b, What.color.a);

    // Assuming
    //    A
    //   /  \      |
    //  B    \     |
    //    --  \    |
    //       --C
    // (This should work in the general case)

    // Structure as diagram above
    Triangle2D tri = What;
    bool usedMax[3] = {false, false, false};
    bool usedMin[3] = {false, false, false};

    // find top (a)
    usedMax[0] = true;
    if (What.b.y < tri.a.y)
    {
        tri.a = What.b;

        usedMax[0] = usedMax[2] = false;
        usedMax[1] = true;
    }
    if (What.c.y < tri.a.y)
    {
        tri.a = What.c;

        usedMax[0] = usedMax[1] = false;
        usedMax[2] = true;
    }

    // find bottom (c)
    usedMin[2] = true;
    if (What.a.y > tri.c.y)
    {
        tri.c = What.a;

        usedMin[1] = usedMin[2] = false;
        usedMin[0] = true;
    }
    if (What.b.y > tri.c.y)
    {
        tri.c = What.b;

        usedMin[0] = usedMin[2] = false;
        usedMin[1] = true;
    }

    // find unused as middle (b)
    if (!usedMin[0] && !usedMax[0])
    {
        tri.b = What.a;
    }
    else if (!usedMin[1] && !usedMax[1])
    {
        tri.b = What.b;
    }
    else
    {
        tri.b = What.c;
    }

    // Per unit of change in y
    double dxA, dxB, dxC;
    if (tri.b.y != tri.a.y)
    {
        dxA = (tri.b.x - tri.a.x) / (tri.b.y - tri.a.y);
    }
    else
    {
        dxA = 0;
    }

    if (tri.c.y != tri.a.y)
    {
        dxB = (tri.c.x - tri.a.x) / (tri.c.y - tri.a.y);
    }
    else
    {
        dxB = 0;
    }

    if (tri.c.y != tri.b.y)
    {
        dxC = (tri.c.x - tri.b.x) / (tri.c.y - tri.b.y);
    }
    else
    {
        dxC = 0;
    }

    // Iterate over a through b
    int i = 0;
    SDL_FRect *rects = new SDL_FRect[2 + (int)(tri.c.y - tri.a.y) / dy];

    for (double y = tri.a.y; y < tri.b.y; y += dy, i++)
    {
        rects[i].y = y;
        rects[i].h = dy;

        rects[i].x = tri.a.x + (i * dxA);
        rects[i].w = (tri.a.x + (i * dxB)) - rects[i].x;
    }

    // Iterate over b through c
    int j = 0;
    for (double y = tri.b.y; y < tri.c.y; y += dy, i++, j++)
    {
        rects[i].y = y;
        rects[i].h = dy;

        rects[i].x = tri.b.x + (j * dxC);
        rects[i].w = (tri.a.x + (i * dxB)) - rects[i].x;
    }

    // Otherwise we will have had a undetected segfault
    assert(i <= 2 + (int)(tri.c.y - tri.a.y) / dy);
    SDL_RenderFillRectsF(With, rects, i);

    delete[] rects;

    return;
}

Object merge(const Object &A, const Object &B)
{
    Object out = A;
    for (auto t : B.triangles)
    {
        out.triangles.push_back(t);
    }
    return out;
}

Object merge(const vector<Object> &Objects)
{
    Object out = Objects[0];
    for (int i = 1; i < Objects.size(); i++)
    {
        for (auto t : Objects[i].triangles)
        {
            out.triangles.push_back(t);
        }
    }
    return out;
}

Object mergeProject(const vector<Object> &Objects)
{
    Object out = Objects[0];
    for (int i = 1; i < Objects.size(); i++)
    {
        for (auto t : Objects[i].triangles)
        {
            out.triangles.push_back(move(rotate(t, Point{0, 0, 0}, Objects[i].rot), Objects[i].offset));
        }
    }
    return out;
}
