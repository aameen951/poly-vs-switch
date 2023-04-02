#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct HddFileObject {
  int x;
};

HddFileObject *hdd_open(const char *filename) {
  auto result = (HddFileObject *)calloc(1, sizeof(HddFileObject));
  srand(time(NULL));
  result->x = rand();
  return result;
}
void hdd_read(HddFileObject *f, void *data, size_t size) {
  printf("DATA FROM HDD:%d\n", f->x);
  memset(data, 0, size);
}
void hdd_write(HddFileObject *f, void *data, size_t size) {
  printf("DATA TO HDD:%d\n", f->x);
}
void hdd_close(HddFileObject *f) {
  delete f;
}
