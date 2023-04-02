#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"
#include <stdio.h>

class Square: public Shape {
public:
  
  float side;

  Square(){}

  const char *get_name() {
    return "square";
  }
  float area() {
    return side * side;
  }
  void scale(float s) {
    side *= s;
  }
  void print() {
    printf("%s  Side: %f\n", get_name(), side);
  }
  void read_from_stdin(){
    printf("Side: ");
    scanf_s("%f", &side);
  }
  bool read_from_file(FILE *f) {
    auto read = fread(&side, sizeof(side), 1, f);
    return read == 1;
  }
  bool write_to_file(FILE *f) {
    auto written = fwrite(&side, sizeof(side), 1, f);
    return written == 1;
  }
};

#endif