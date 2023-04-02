#include <stdio.h>
#include <string.h>
#include "shape.h"

const char FILE_SIGNATURE[] = "SHAPE";

Shape *shape_read_from_file(char *filepath){
  Shape *result = NULL;
  auto f = fopen(filepath, "rb");
  if(f) {
    char buf[sizeof(FILE_SIGNATURE)];
    auto read = fread(buf, sizeof(buf), 1, f);
    if(read == 1) {
      if(strcmp(buf, FILE_SIGNATURE) == 0) {
        unsigned char version = 0;
        read = fread(&version, sizeof(version), 1, f);
        if(read == 1) {
          if(version == 1) {
            unsigned char flags = 0;
            read = fread(&flags, sizeof(flags), 1, f);
            if(read == 1) {
              if(flags == 0) {
                unsigned int shape_name_len = 0;
                read = fread(&shape_name_len, sizeof(shape_name_len), 1, f);
                if(read == 1) {
                  if(shape_name_len < 64) {
                    char shape_name[65] = {};
                    read = fread(shape_name, shape_name_len, 1, f);
                    if(read == 1) {
                      result = new Shape();
                      if(stricmp(shape_name, "square") == 0) {
                        result->type = SHAPE_SQUARE;
                        read = fread(&result->square.side, sizeof(result->square.side), 1, f);
                      } else if(stricmp(shape_name, "rectangle") == 0) {
                        result->type = SHAPE_RECTANGLE;
                        read = fread(&result->rectangle.w, sizeof(result->rectangle.w), 1, f);
                        read = read && fread(&result->rectangle.h, sizeof(result->rectangle.h), 1, f);
                      } else if(stricmp(shape_name, "circle") == 0) {
                        result->type = SHAPE_CIRCLE;
                        read = fread(&result->circle.radius, sizeof(result->circle.radius), 1, f);
                      } else if(stricmp(shape_name, "triangle") == 0) {
                        result->type = SHAPE_TRIANGLE;
                        read = fread(&result->triangle.base, sizeof(result->triangle.base), 1, f);
                        read = read && fread(&result->triangle.height, sizeof(result->triangle.height), 1, f);
                      } else {
                        printf("Unknown shape '%s'\n", shape_name);
                      }
                      if(read) {
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    fclose(f);
  }
  return result;
}

bool shape_write_to_file(char *filepath, Shape *s){
  auto f = fopen(filepath, "wb");
  if(f) {
    char buf[sizeof(FILE_SIGNATURE)];
    auto written = fwrite(FILE_SIGNATURE, sizeof(FILE_SIGNATURE), 1, f);
    if(written == 1) {
      unsigned char version = 1;
      written = fwrite(&version, sizeof(version), 1, f);
      if(written == 1) {
        unsigned char flags = 0;
        written = fwrite(&flags, sizeof(flags), 1, f);
        if(written == 1) {
          auto shape_name = shape_get_name(s);
          unsigned int shape_name_len = strlen(shape_name)+1;
          written = fwrite(&shape_name_len, 4, 1, f);
          written = fwrite(shape_name, shape_name_len, 1, f);
          if(written == 1) {
            switch(s->type) {
              case SHAPE_RECTANGLE: {
                written = fwrite(&s->rectangle.w, sizeof(s->rectangle.w), 1, f);
                written = written && fwrite(&s->rectangle.h, sizeof(s->rectangle.h), 1, f);
              } break;
              case SHAPE_SQUARE: {
                written = fwrite(&s->square.side, sizeof(s->square.side), 1, f);
              } break;
              case SHAPE_CIRCLE: {
                written = fwrite(&s->circle.radius, sizeof(s->circle.radius), 1, f);
              } break;
              case SHAPE_TRIANGLE: {
                written = fwrite(&s->triangle.base, sizeof(s->triangle.base), 1, f);
                written = written && fwrite(&s->triangle.height, sizeof(s->triangle.height), 1, f);
              } break;
              default: assert(false);
            }
            if(written) {
              return true;
            }
          }
        }
      }
    }
    fclose(f);
  }
  return false;
}
