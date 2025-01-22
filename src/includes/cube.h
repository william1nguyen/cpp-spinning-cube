#include "point.h"

struct Cube {
  char buffer[SCREEN_WIDTH * SCREEN_HEIGHT];
  double zBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

  void renew() {
    std::memset(buffer, BACKGROUND_ASCII_CODE, SCREEN_WIDTH * SCREEN_HEIGHT);
    std::memset(zBuffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * CUBE_SURFACES);
  }

  void calculateSurface(Point3D P, double A, double B, double C, char ch) {
    P.rotate(A, B, C);
    P.updateBuffer(buffer, zBuffer, ch);
  }

  void rotate(double A, double B, double C) {
    for (double x = -CUBE_WIDTH; x < CUBE_WIDTH; x = x + INCREMENT_SPEED) {
      for (double y = -CUBE_WIDTH; y < CUBE_WIDTH; y = y + INCREMENT_SPEED) {
        calculateSurface(Point3D(x, y, -CUBE_WIDTH), A, B, C, '@');
        calculateSurface(Point3D(CUBE_WIDTH, y, x), A, B, C, '$');
        calculateSurface(Point3D(-CUBE_WIDTH, y, -x), A, B, C, '~');
        calculateSurface(Point3D(-x, y, CUBE_WIDTH), A, B, C, '#');
        calculateSurface(Point3D(x, -CUBE_WIDTH, -y), A, B, C, ';');
        calculateSurface(Point3D(x, CUBE_WIDTH, y), A, B, C, '+');
      }
    }
  }

  void render() {
    for (int id = 0; id < SCREEN_WIDTH * SCREEN_HEIGHT; ++id) {
      putchar(id % SCREEN_WIDTH ? buffer[id] : 10);
    }
  }
};
