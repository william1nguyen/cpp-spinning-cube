#include <math.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "env.h"
#include "cube.h"

Cube cube;
double A = 0, B = 0, C = 0;

void renderCube() {
  printf("\x1b[2J");

  while (1) {
    cube.renew();
    cube.rotate(A, B, C);
    printf("\x1b[H");
    cube.render();
    A = A + INCREMENT_ANGLE;
    B = B + INCREMENT_ANGLE;
    usleep(8000 * 2);
  }
}

int main() {
  renderCube();
}
