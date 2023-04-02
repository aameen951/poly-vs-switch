#include "driver_api.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct FileObject {
  int x;
};

void handler(FileDriverOperationData *in_out) {
  switch(in_out->type) {

    case OP_TYPE_open: {
      auto result = (FileObject *)calloc(1, sizeof(FileObject));
      srand(time(NULL));
      result->x = rand();
      in_out->open.f = result;
    } break;

    case OP_TYPE_read: {
      auto file = (FileObject *)in_out->read.f;
      printf("DATA FROM BLUETOOTH:%d\n", file->x);
      memset(in_out->read.data, 0, in_out->read.size);
    } break;
    
    case OP_TYPE_write: {
      auto file = (FileObject *)in_out->write.f;
      printf("DATA TO BLUETOOTH:%d\n", file->x);
    } break;

    case OP_TYPE_close: {
      auto file = (FileObject *)in_out->close.f;
      free(file);
    } break;

    case OP_TYPE_get_name: {
      in_out->get_name.name = "BLUETOOTH";
    } break;

  }
}

extern "C" FileDriverHandler *GetFileDriver() {
  return handler;
}
