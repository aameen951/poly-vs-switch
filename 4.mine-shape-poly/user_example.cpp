#include "shape.h"
#include "shape_stdio.cpp"
#include "shape_file.cpp"

#include <string.h>

int main(int arg_count, char **args) {
  char *input_file = NULL;
  char *output_file = NULL;
  bool print = false;
  bool area = false;

  for(int i=1; i<arg_count; i++) {
    if(stricmp(args[i], "-in") == 0) {
      input_file = args[++i];
    } else if(stricmp(args[i], "-out") == 0) {
      output_file = args[++i];
    } else if(stricmp(args[i], "-area") == 0) {
      area = true;
    } else if(stricmp(args[i], "-print") == 0) {
      print = true;
    }
  }

  if(!input_file) {
    printf("Error: no input specified\n");
    return 1;
  }

  Shape *s = NULL;
  if(stricmp(input_file, "-") == 0) {
    s = shape_read_from_stdin();
  } else {
    s = shape_read_from_file(input_file);
  }

  if(!s) {
    return 2;
  }

  if(print) {
    s->print();
  }
  if(area) {
    printf("Aria: %f\n", s->area());
  }

  if(output_file) {
    shape_write_to_file(output_file, s);
  }

  return 0;
}