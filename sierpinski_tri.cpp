#include "angel/Angel.h"
#include "InitShader.cpp"
#include <string>
#include <cmath>

typedef vec3 point3;
typedef vec3 color3;

void init();
void display();
void triangle(point3 a, point3 b, point3 c);
void tetra(point3 a, point3 b, point3 c, point3 d);
void divide_tetra(point3 a, point3 b, point3 c, point3 d, int k);


color3 base_colors[4] = {color3(1.0, 0.0, 0.0), color3(0.0, 1.0, 0.0),
                         color3(0.0, 0.0, 1.0), color3(0.0, 0.0, 0.0)};

const int NumSubdivisions = 3;
const int NumTetrahedrons = pow(4, NumSubdivisions);
const int NumTriangles = 4 * NumTetrahedrons;
const int NumVertices = 3 * NumTriangles;

point3 points[NumVertices];
color3 colors[NumVertices];

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
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
  point3 vertices[4] = { point3( 0.0, 0.0, -1.0 ),
                         point3( 0.0, 0.942809, 0.333333 ),
                         point3( -0.816497, -0.471405, 0.333333 ),
                         point3( 0.816497, -0.471405, 0.333333 ) };

  divide_tetra(vertices[0], vertices[1], vertices[2], vertices[3], NumSubdivisions);

  GLuint program = InitShader("sierpinski_vertex_tri.glsl",
                              "sierpinski_fragment.glsl");
  glUseProgram(program);

  GLuint abuffer;

  glGenVertexArrays(1, &abuffer);
  glBindVertexArray(abuffer);

  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);

  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

  GLuint loc = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  GLuint loc2 = glGetAttribLocation(program, "vColor");
  glEnableVertexAttribArray(loc2);
  glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0,
                        BUFFER_OFFSET(sizeof(points)));

  glEnable(GL_DEPTH_TEST);

  glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}

int colorindex;

void triangle(point3 a, point3 b, point3 c)
{
  static int i = 0;
  points[i] = a;
  colors[i] = base_colors[colorindex];
  i++;
  points[i] = b;
  colors[i] = base_colors[colorindex];
  i++;
  points[i] = c;
  colors[i] = base_colors[colorindex];
  i++;
}

void tetra(point3 a, point3 b, point3 c, point3 d)
{
  colorindex = 0;
  triangle(a, b, c);
  colorindex = 1;
  triangle(a, c, d);
  colorindex = 2;
  triangle(a, d, b);
  colorindex = 3;
  triangle(b, d, c);
}

// recursively subdivide tetrahedrons until k is down
// to 0, and then draw the tetrahedrons
void divide_tetra(point3 a, point3 b, point3 c, point3 d, int k)
{
  if (k == 0) {
    tetra(a, b, c, d);
    return;
  }
  point3 mid[6];
  // compute midpoints of sides
  mid[0] = (a + b) / 2.0;
  mid[1] = (a + c) / 2.0;
  mid[2] = (a + d) / 2.0;
  mid[3] = (b + c) / 2.0;
  mid[4] = (c + d) / 2.0;
  mid[5] = (b + d) / 2.0;
  // subdivide all but inner tetrahedron
  divide_tetra(a, mid[0], mid[1], mid[2], k - 1);
  divide_tetra(mid[0], b, mid[3], mid[5], k - 1);
  divide_tetra(mid[1], mid[3], c, mid[4], k - 1);
  divide_tetra(mid[2], mid[4], mid[5], d, k - 1);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, NumVertices);
  glFlush();
}
