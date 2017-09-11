#include "angel/Angel.h"

typedef vec2 point2;

int main()
{
  const int NumPoints = 5000;
  point2 points[NumPoints];

  // triangle in plane z = 0
  point2 vertices[3] = {point2(-1.0,-1.0), point2(0.0,1.0), point2(1.0,-1.0)};

  // arbitrary initial point
  points[0] = point2(0.25, 0.50);

  // add NumPoints - 1 new points
  for (int k = 1; k < NumPoints; k++) {
    // pick vertex at random
    point2 vertex = vertices[rand() % 3];

    // Compute halfway point between selected vertex and last point
    points[k] = (points[k - 1] + vertex) / 2.0;
    std::cout << points[k] << std::endl;
  }
}
