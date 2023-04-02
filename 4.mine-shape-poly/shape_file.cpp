#include <stdio.h>
#include <string.h>
#include "shape.h"
#include "square.h"
#include "rectangle.h"
#include "circle.h"
#include "triangle.h"

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
                      if(stricmp(shape_name, "square") == 0) {
                        result = new Square();
                      } else if(stricmp(shape_name, "rectangle") == 0) {
                        result = new Rectangle();
                      } else if(stricmp(shape_name, "circle") == 0) {
                        result = new Circle();
                      } else if(stricmp(shape_name, "triangle") == 0) {
                        result = new Triangle();
                      } else {
                        printf("Unknown shape '%s'\n", shape_name);
                      }
                      if(result) {
                        result->read_from_file(f);
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
          auto shape_name = s->get_name();
          unsigned int shape_name_len = strlen(shape_name)+1;
          written = fwrite(&shape_name_len, 4, 1, f);
          written = fwrite(shape_name, shape_name_len, 1, f);
          if(written == 1) {
            if(s->write_to_file(f)) {
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
