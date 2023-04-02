#ifndef SHAPE_H
#define SHAPE_H

#include <stdio.h>
#include <assert.h>

enum ShapeType {
  SHAPE_RECTANGLE,
  SHAPE_SQUARE,
  SHAPE_CIRCLE,
  SHAPE_TRIANGLE,
};
struct ShapeRectangle {
  float w;
  float h;
};
struct ShapeSquare {
  float side;
};
struct ShapeCircle {
  float radius;
};
struct ShapeTriangle {
  float base;
  float height;
};
struct Shape {
  ShapeType type;
  union {
    ShapeRectangle rectangle;
    ShapeSquare square;
    ShapeCircle circle;
    ShapeTriangle triangle;
  };
};

inline static const char *shape_get_name(Shape *s){
  switch(s->type) {
    case SHAPE_RECTANGLE: return "rectangle";
    case SHAPE_SQUARE: return "square";
    case SHAPE_CIRCLE: return "circle";
    case SHAPE_TRIANGLE: return "triangle";
    default: assert(false);
  }
  return "";
}

#endif