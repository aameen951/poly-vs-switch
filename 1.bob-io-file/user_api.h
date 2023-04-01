#include <stdlib.h>
#include <string.h>

struct VirtualFile;

VirtualFile *open(const char *filename);
void read(VirtualFile *f, void *data, size_t size);
void write(VirtualFile *f, void *data, size_t size);
void close(VirtualFile *f);

bool load_driver(const char *driver_path);
bool unload_driver(const char *driver_path);
