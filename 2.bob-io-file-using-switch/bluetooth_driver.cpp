#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct BluetoothFileObject {
  int x;
};

BluetoothFileObject *bluetooth_open(const char *filename) {
  auto result = (BluetoothFileObject *)calloc(1, sizeof(BluetoothFileObject));
  srand(time(NULL));
  result->x = rand();
  return result;
}
void bluetooth_read(BluetoothFileObject *f, void *data, size_t size) {
  printf("DATA FROM BLUETOOTH:%d\n", f->x);
  memset(data, 0, size);
}
void bluetooth_write(BluetoothFileObject *f, void *data, size_t size) {
  printf("DATA TO BLUETOOTH:%d\n", f->x);
}
void bluetooth_close(BluetoothFileObject *f) {
  delete f;
}
