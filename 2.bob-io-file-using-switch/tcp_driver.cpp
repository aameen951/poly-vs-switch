#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct TcpFileObject {
  int x;
};

TcpFileObject *tcp_open(const char *filename) {
  auto result = (TcpFileObject *)calloc(1, sizeof(TcpFileObject));
  srand(time(NULL));
  result->x = rand();
  return result;
}
void tcp_read(TcpFileObject *f, void *data, size_t size) {
  printf("DATA FROM TCP:%d\n", f->x);
  memset(data, 0, size);
}
void tcp_write(TcpFileObject *f, void *data, size_t size) {
  printf("DATA TO TCP:%d\n", f->x);
}
void tcp_close(TcpFileObject *f) {
  delete f;
}
