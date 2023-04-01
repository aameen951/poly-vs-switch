
// This is the interface that all drivers must implement.
// NOTE: There is no `#include`s or any kind of dependecy from this code (which 
// Bob calls it the high level code) on the code of the drivers (which Bob calls it
// low level code). On the other hand, drivers are going to include this file and
// depend on it. This is what he calls "inverted dependency". The dependency goes 
// from the low level code (the drivers) to the high level code (interface/base type).
typedef void *FileDriverHandle;
class FileDriver {
public:
  virtual const char *get_name() = 0;
  virtual FileDriverHandle open(const char *filename) = 0;
  virtual void read(FileDriverHandle f, void *data, size_t size) = 0;
  virtual void write(FileDriverHandle f, void *data, size_t size) = 0;
  virtual void close(FileDriverHandle f) = 0;
};

typedef FileDriver *GetFileDriverProc();
