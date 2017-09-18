#include "angel/Angel.h"
#include "InitShader.cpp"
#include <string>
#include <cmath>

typedef vec2 point2;

void init();
void display();
void triangle(point2 a, point2 b, point2 c);
void divide_triangle(point2 a, point2 b, point2 c, int k);

const int NumSubdivisions = 6;
const int NumTriangles = pow(3, NumSubdivisions);
const int NumVertices = 3 * NumTriangles;

point2 points[NumVertices];

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(512, 512);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("Sierpinski Gasket");
  #ifndef __APPLE__
  glewInit();
  #endif
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}

void init()
{
  // triangle in plane z = 0
  point2 vertices[3] = {point2(-1.0,-1.0), point2(0.0,1.0), point2(1.0,-1.0)};

  divide_triangle(vertices[0], vertices[1], vertices[2], NumSubdivisions);

  GLuint program = InitShader("sierpinski_vertex.glsl",
                              "sierpinski_fragment.glsl");
  glUseProgram(program);

  GLuint abuffer;

  glGenVertexArrays(1, &abuffer);
  glBindVertexArray(abuffer);

  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

  GLuint loc = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}

void triangle(point2 a, point2 b, point2 c)
{
  static int i = 0;
  points[i++] = a;
  points[i++] = b;
  points[i++] = c;
}

// recursively subdivide triangle areas until k is down
// to 0, and then draw the triangles
void divide_triangle(point2 a, point2 b, point2 c, int k)
{
  if (k == 0) {
    triangle(a,b,c);
    return;
  }
  // compute midpoints of sides
  point2 ab = (a + b) / 2.0;
  point2 ac = (a + c) / 2.0;
  point2 bc = (b + c) / 2.0;
  // subdivide all but inner triangle
  divide_triangle(a, ab, ac, k - 1);
  divide_triangle(c, ac, bc, k - 1);
  divide_triangle(b, bc, ab, k - 1);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, NumVertices);
  glFlush();
}
