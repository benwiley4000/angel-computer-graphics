#include "angel/Angel.h"
#include "InitShader.cpp"
#include <string>

typedef vec3 point3;

void init();
void display();

const int NumPoints = 50000;

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
  point3 points[NumPoints];

  point3 vertices[4] = { point3(-1.0,  -1.0, -1.0),
                         point3( 1.0,  -1.0, -1.0),
                         point3( 0.0,   1.0, -1.0),
                         point3( 0.0,   0.0,  1.0) };

  // arbitrary initial point
  points[0] = point3(0.0, 0.0, 0.0);

  // add NumPoints - 1 new points
  for (int k = 1; k < NumPoints; k++) {
    // pick vertex at random
    point3 vertex = vertices[rand() % 4];

    // Compute halfway point between selected vertex and last point
    points[k] = (points[k - 1] + vertex) / 2.0;
  }

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
  glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_POINTS, 0, NumPoints);
  glFlush();
}
