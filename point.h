struct Point2D {
  double x, y;
  double zFactor;

  Point2D() {};
  Point2D(double _x, double _y, double _factor):
    x(_x), y(_y), zFactor(_factor) {};

private:
  int getBufferIdx() {
    return (int) x + y * SCREEN_WIDTH;
  }

public:
  void transaltion(double deltaX, double deltaY) {
    x = x + deltaX;
    y = y + deltaY;
  }

  void updateBuffer(char* buffer, double* zBuffer, char chr) {
    int idx = getBufferIdx();
    if (idx < 0 || idx >= SCREEN_WIDTH * SCREEN_HEIGHT) return;
    if (zFactor > zBuffer[idx]) {
      zBuffer[idx] = zFactor;
      buffer[idx] = chr;
    }
  }
};

struct Point3D {
  double x, y, z;

  Point3D() {};
  Point3D(double _x, double _y, double _z):
    x(_x), y(_y), z(_z) {};

  double rotatedX(double A, double B, double C) {
    return
      y * std::sin(A) * std::sin(B) * std::cos(C) -
      z * std::cos(A) * std::sin(B) * std::cos(C) +
      y * std::cos(A) * std::sin(C) +
      z * std::sin(A) * std::sin(C) +
      x * std::cos(B) * std::cos(C);
  }

  double rotatedY(double A, double B, double C) {
    return
      y * std::cos(A) * std::cos(C) +
      z * std::sin(A) * std::cos(C) -
      y * std::sin(A) * std::sin(B) * std::sin(C) +
      z * std::cos(A) * std::sin(B) * std::sin(C) -
      x * std::cos(B) * std::sin(C);
  }

  double rotatedZ(double A, double B, double C) {
    return
      z * std::cos(A) * std::cos(B) -
      y * std::sin(A) * std::cos(B) +
      x * std::sin(B);
  }

  Point2D project3DTo2D() {
    int xP = (int) SCAILING_FACTOR * x / z * 2;
    int yP = (int) SCAILING_FACTOR * y / z;
    double zFactor = 1 / z;

    Point2D P = Point2D(xP, yP, zFactor);
    P.transaltion(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    return P;
  }

  void updateBuffer(char* buffer, double* zBuffer, char chr) {
    Point2D P = project3DTo2D();
    P.updateBuffer(buffer, zBuffer, chr);
  }

  // rotate_x A degree, rotate_y B degree, rotate_z C degree
  void rotate(double A, double B, double C) {
    x = rotatedX(A, B, C);
    y = rotatedY(A, B, C);
    z = rotatedZ(A, B, C) + DISTANCE_FROM_CAM;
  }

};
