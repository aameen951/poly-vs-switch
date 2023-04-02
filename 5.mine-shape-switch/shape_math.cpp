#include "shape.h"

#define PI32 3.14159265359f

void shape_scale(Shape *s, float r) {
  switch(s->type) {

    case SHAPE_RECTANGLE: {
      s->rectangle.w *= r;
      s->rectangle.h *= r;
    } break;
    case SHAPE_SQUARE: {
      s->square.side *= r;
    } break;
    case SHAPE_CIRCLE: {
      s->circle.radius *= r;
    } break;
    case SHAPE_TRIANGLE: {
      s->triangle.base *= r;
      s->triangle.height *= r;
    } break;

    default: assert(false);
  }
}
float shape_area(Shape *s) {
  switch(s->type) {

    case SHAPE_RECTANGLE: {
      return s->rectangle.w * s->rectangle.h;
    } break;
    case SHAPE_SQUARE: {
      return s->square.side * s->square.side;
    } break;
    case SHAPE_CIRCLE: {
      return s->circle.radius * s->circle.radius * PI32;
    } break;
    case SHAPE_TRIANGLE: {
      return s->triangle.base * s->triangle.height * 0.5f;
    } break;

    default: assert(false);
  }
  return 0;
}
