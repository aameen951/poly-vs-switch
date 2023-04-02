#ifndef SHAPE_H
#define SHAPE_H

#include <stdio.h>

class Shape {
public:
  virtual const char *get_name() = 0;
  virtual float area() = 0;
  virtual void scale(float s) = 0;
  virtual void print() = 0;
  virtual void read_from_stdin() = 0;

  virtual bool read_from_file(FILE *f) = 0;
  virtual bool write_to_file(FILE *f) = 0;
};

#endif