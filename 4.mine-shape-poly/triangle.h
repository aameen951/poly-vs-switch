#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"
#include <stdio.h>

class Triangle: public Shape {
public:
  
  float base;
  float height;

  Triangle(){}

  const char *get_name() {
    return "triangle";
  }
  float area() {
    return base * height * 0.5f;
  }
  void scale(float s) {
    base *= s;
    height *= s;
  }
  void print() {
    printf("%s  Base: %f   Height: %f\n", get_name(), base, height);
  }
  void read_from_stdin(){
    printf("Base: ");
    scanf_s("%f", &base);
    printf("Height: ");
    scanf_s("%f", &height);
  }
  bool read_from_file(FILE *f) {
    auto read = fread(&base, sizeof(base), 1, f);
    read = read && fread(&height, sizeof(height), 1, f);
    return read == 1;
  }
  bool write_to_file(FILE *f) {
    auto written = fwrite(&base, sizeof(base), 1, f);
    written = written && fwrite(&height, sizeof(height), 1, f);
    return written == 1;
  }
};

#endif