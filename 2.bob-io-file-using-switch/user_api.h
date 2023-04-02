#include <stdlib.h>
#include <string.h>

struct VirtualFile;

VirtualFile *open(const char *filename);
void read(VirtualFile *f, void *data, size_t size);
void write(VirtualFile *f, void *data, size_t size);
void close(VirtualFile *f);


// NOTE: If you use switch statements instead of polymorphism you are 
// no longer able to load/unload drivers at runtime. Adding new drivers
// requires updating the code to include the cases to handle the new drivers
// then recompiling.
//
// This is never done in practice since it is not practical a solution. Drivers
// are usually written by different a team in a different organization and it is unfeasible
// to make the api include every possible driver that exists and recompiled and redeployed 
// on every change in any of the drivers.
//
// This is just the nature of the specific example that was setup by Bob.
// 
// bool load_driver(const char *driver_path);
// bool unload_driver(const char *driver_path);
