#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct SsdFileObject {
  int x;
};

SsdFileObject *ssd_open(const char *filename) {
  auto result = (SsdFileObject *)calloc(1, sizeof(SsdFileObject));
  srand(time(NULL));
  result->x = rand();
  return result;
}
void ssd_read(SsdFileObject *f, void *data, size_t size) {
  printf("DATA FROM SSD:%d\n", f->x);
  memset(data, 0, size);
}
void ssd_write(SsdFileObject *f, void *data, size_t size) {
  printf("DATA TO SSD:%d\n", f->x);
}
void ssd_close(SsdFileObject *f) {
  delete f;
}
