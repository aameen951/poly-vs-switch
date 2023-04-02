#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"
#include <stdio.h>

class Rectangle: public Shape {
public:
  
  float w;
  float h;

  Rectangle(){}

  const char *get_name() {
    return "rectangle";
  }
  float area() {
    return w * h;
  }
  void scale(float s) {
    w *= s;
    h *= s;
  }
  void print() {
    printf("%s  W: %f   H: %f\n", get_name(), w, h);
  }
  void read_from_stdin(){
    printf("W: ");
    scanf_s("%f", &w);
    printf("H: ");
    scanf_s("%f", &h);
  }
  
  bool read_from_file(FILE *f) {
    auto read = fread(&w, sizeof(w), 1, f);
    read = read && fread(&h, sizeof(h), 1, f);
    return read == 1;
  }
  bool write_to_file(FILE *f) {
    auto written = fwrite(&w, sizeof(w), 1, f);
    written = written && fwrite(&h, sizeof(h), 1, f);
    return written == 1;
  }

};

#endif