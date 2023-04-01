#include "driver_api.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// The code inside the driver is random and irrelevant.
struct FileObject {
  int x;
};

// NOTE: This is the inverted dependency that Bob was talking about. The driver (low level code)
// is including/depending on the driver interface (high level code).
// To clarify, it is not about using classes instead of structures, using inheritance 
// instead function signatures and function pointer, or using member functions instead of 
// normal functions. It has nothing to do with that.
// It is the fact that you can compile this file, link it to a DLL and load it into a running
// application without having to recompile the application or re-link it or even stop it
// and start it again. This is, from my understanding, what Bob means by 
// "without recompilation and redeployment".
// Now, whether that's useful to have for every class/object in the application is a separate
// issue but this is what I think he means by that.
class BluetoothDriver : public FileDriver {
public:
  const char *get_name() { return "BLUETOOTH"; }
  FileDriverHandle open(const char *filename) {
    auto result = new FileObject();
    srand(time(NULL));
    result->x = rand();
    return result;
  }
  void read(FileDriverHandle f, void *data, size_t size) {
    auto file = (FileObject *)f;
    printf("DATA FROM %s:%d\n", this->get_name(), file->x);
    memset(data, 0, size);
  }
  void write(FileDriverHandle f, void *data, size_t size) {
    auto file = (FileObject *)f;
    printf("DATA TO %s:%d\n", this->get_name(), file->x);
  }
  void close(FileDriverHandle f) {
    auto file = (FileObject *)f;
    delete file;
  }
};

extern "C" FileDriver *GetFileDriver() {
  return new BluetoothDriver();
}
