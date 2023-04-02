#include <stdio.h>
#include <string.h>
#include "shape.h"

Shape *shape_read_from_stdin(){

  Shape *s = new Shape();
read_again:

  char shape_name[64];
  printf("What is the shape? ", shape_name);
  scanf_s("%63s", shape_name, 64);

  if(stricmp(shape_name, "square") == 0) {
    s->type = SHAPE_SQUARE;
    printf("Side: ");
    scanf_s("%f", &s->square.side);
  } else if(stricmp(shape_name, "rectangle") == 0) {
    s->type = SHAPE_RECTANGLE;
    printf("W: ");
    scanf_s("%f", &s->rectangle.w);
    printf("H: ");
    scanf_s("%f", &s->rectangle.h);
  } else if(stricmp(shape_name, "circle") == 0) {
    s->type = SHAPE_CIRCLE;
    printf("Radius: ");
    scanf_s("%f", &s->circle.radius);
  } else if(stricmp(shape_name, "triangle") == 0) {
    s->type = SHAPE_TRIANGLE;
    printf("Base: ");
    scanf_s("%f", &s->triangle.base);
    printf("Height: ");
    scanf_s("%f", &s->triangle.height);
  } else {
    printf("Unknown shape '%s'\n", shape_name);
    goto read_again;
  }

  return s;
}

void shape_print(Shape *s) {
  auto name = shape_get_name(s);
  switch(s->type) {

    case SHAPE_RECTANGLE: {
      printf("%s  W: %f   H: %f\n", name, s->rectangle.w, s->rectangle.h);
    } break;
    case SHAPE_SQUARE: {
      printf("%s  Side: %f\n", name, s->square.side);
    } break;
    case SHAPE_CIRCLE: {
      printf("%s  Radius: %f\n", name, s->circle.radius);
    } break;
    case SHAPE_TRIANGLE: {
      printf("%s  Base: %f   Height: %f\n", name, s->triangle.base, s->triangle.height);
    } break;

    default: assert(false);
  }
}
