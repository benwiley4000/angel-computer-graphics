#include "angel/Angel.h"

typedef vec3 point3;

int main()
{
  const float DegreesToRadians = M_PI / 180.0;

  point3 quad_data[342]; // 8 rows of 18 quads

  int k = 0;
  for (float phi = -80.0; phi <= 80.0; phi += 20.0) {
    float phir = phi * DegreesToRadians;
    float phir20 = (phi + 20.0) * DegreesToRadians;

    for (float theta = -180.0; theta <= 180.0; theta += 20.0) {
      float thetar = theta * DegreesToRadians;
      quad_data[k] = point3(sin(thetar) * cos(phir),
                            cos(thetar) * cos(phir),
                            sin(phir));
      std::cout << quad_data[k] << std::endl;
      k++;
      quad_data[k] = point3(sin(thetar) * cos(phir20),
                            cos(thetar) * cos(phir20),
                            sin(phir20));
      std::cout << quad_data[k] << std::endl;
      k++;
    }
  }

  k = 0;
  point3 strip_data[40];

  strip_data[k] = point3(0.0, 0.0, 1.0);
  k++;

  float sin80 = sin(80.0 * DegreesToRadians);
  float cos80 = cos(80.0 * DegreesToRadians);

  for (float theta = -180; theta <= 180.0; theta += 20.0) {
    float thetar = theta * DegreesToRadians;
    strip_data[k] = point3(sin(thetar) * cos80,
                           cos(thetar) * cos80,
                           sin80);
    std::cout << strip_data[k] << std::endl;
    k++;
  }

  strip_data[k] = point3(0.0, 0.0, -1.0);
  k++;

  for (float theta = -180; theta <= 180.0; theta += 20.0) {
    float thetar = theta * DegreesToRadians;
    strip_data[k] = point3(sin(thetar) * cos80,
                           cos(thetar) * cos80,
                           sin80);
    std::cout << strip_data[k] << std::endl;
    k++;
  }
}
