#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include <stdio.h>

class Circle: public Shape {
public:
  
  float radius;

  Circle(){}

  const char *get_name() {
    return "circle";
  }
  float area() {
    return radius * radius * 3.14159265359;
  }
  void scale(float s) {
    radius *= s;
  }
  void print() {
    printf("%s  Radius: %f\n", get_name(), radius);
  }
  void read_from_stdin(){
    printf("Radius: ");
    scanf_s("%f", &radius);
  }
  bool read_from_file(FILE *f) {
    auto read = fread(&radius, sizeof(radius), 1, f);
    return read == 1;
  }
  bool write_to_file(FILE *f) {
    auto written = fwrite(&radius, sizeof(radius), 1, f);
    return written == 1;
  }
};

#endif