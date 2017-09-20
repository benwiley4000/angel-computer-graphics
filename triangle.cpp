#include "angel/Angel.h"
#include "InitShader.cpp"

typedef vec2 point2;

void init();
void display();
void mouse(int button, int state, int x, int y);
void reshape(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void idle();
void top_menu(int id);
void rotation_menu(int id);

const float Angle = 0.05 * DegreesToRadians;
const int NumVertices = 3;

point2 points[NumVertices];

int w = 512;
int h = 512;

GLuint program, loc;

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(w, h);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("Triangle");
  #ifndef __APPLE__
  glewInit();
  #endif
  init();
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);

  GLuint sub_menu = glutCreateMenu(rotation_menu);
  glutAddMenuEntry("start rotation", 2);
  glutAddMenuEntry("stop rotation", 3);
  glutCreateMenu(top_menu);
  glutAddMenuEntry("Quit", 1);
  glutAddSubMenu("start/stop rotation", sub_menu);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 0;
}

void init()
{

  program = InitShader("triangle_vertex.glsl", "triangle_fragment.glsl");
  glUseProgram(program);

  GLuint abuffer;
  glGenVertexArrays(1, &abuffer);
  glBindVertexArray(abuffer);

  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

  loc = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

  loc = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

  glDrawArrays(GL_TRIANGLES, 0, NumVertices);
  glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
  static int count = 0;
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    points[count].x = (float) x / (w/2) - 1.0;
    points[count].y = (float) (h-y) / (h/2) - 1.0;
    count++;
  }
  if(count == 3) {
    glutPostRedisplay();
    count = 0;
  }
}

void reshape(GLsizei _w, GLsizei _h)
{
  w = _w;
  h = _h;
  glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y)
{
  if (key == 'q' || key == 'Q') {
    exit(0);
  }
}

void idle()
{
  for(int i = 0; i < 3; i++) {
    float x = cos(Angle) * points[i].x - sin(Angle) * points[i].y;
    float y = sin(Angle) * points[i].x + cos(Angle) * points[i].y;
    points[i].x = x;
    points[i].y = y;
  }
  glutPostRedisplay();
}

void top_menu(int id)
{
  switch (id) {
    case 1:
      exit(0);
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void rotation_menu(int id)
{
  switch (id) {
    case 2:
      glutIdleFunc(idle);
      break;
    case 3:
      glutIdleFunc(NULL);
      break;
    default:
      break;
  }
  glutPostRedisplay();
}
