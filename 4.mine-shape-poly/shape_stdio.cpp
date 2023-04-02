#include <stdio.h>
#include <string.h>
#include "shape.h"
#include "square.h"
#include "rectangle.h"
#include "circle.h"
#include "triangle.h"

Shape *shape_read_from_stdin(){

read_again:

  char shape_name[64];
  printf("What is the shape? ", shape_name);
  scanf_s("%63s", shape_name, 64);

  Shape *s = NULL;
  if(stricmp(shape_name, "square") == 0) {
    s = new Square();
  } else if(stricmp(shape_name, "rectangle") == 0) {
    s = new Rectangle();
  } else if(stricmp(shape_name, "circle") == 0) {
    s = new Circle();
  } else if(stricmp(shape_name, "triangle") == 0) {
    s = new Triangle();
  } else {
    printf("Unknown shape '%s'\n", shape_name);
    goto read_again;
  }

  s->read_from_stdin();

  return s;
}
