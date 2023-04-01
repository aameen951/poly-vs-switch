#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "driver_api.h"

// Polymorphic object: the API and the user code doesn't know anything about the implementation
// at compile-time or at link-time. The polymorphic object will be loaded at runtime dynamically.
// As a result, this code doesn't need to be recompiled, relinked, or stopped and started again
// every time you have a new or updated polymorphic object.
struct VirtualFile {
  FileDriver *driver;
  FileDriverHandle handle;
};

// This function will examine the scheme at the beginning of the filename
// to determine the driver and update the filename to skip the scheme.
FileDriver *determine_driver_from_file_name(const char **filename_p);

VirtualFile *open(const char *filename) {
  VirtualFile *result = (VirtualFile *)calloc(1, sizeof(VirtualFile));
  
  result->driver = determine_driver_from_file_name(&filename);
  if(!result->driver)return NULL;

  result->handle = result->driver->open(filename);

  return result;
}

void read(VirtualFile *f, void *data, size_t size){
  f->driver->read(f->handle, data, size);
}

void write(VirtualFile *f, void *data, size_t size){
  f->driver->write(f->handle, data, size);
}

void close(VirtualFile *f){
  f->driver->close(f->handle);
  free(f);
}

// IRRELEVANT CODE

FileDriver *available_drivers[256];
size_t available_drivers_count;

bool load_driver(const char *driver_path) {
  auto lib = LoadLibraryA(driver_path);
  if(!lib)return false;

  auto get_file_driver = (GetFileDriverProc *)GetProcAddress(lib, "GetFileDriver");
  if(!get_file_driver) {
    FreeLibrary(lib);
    return false;
  }
  if(available_drivers_count+1 > sizeof(available_drivers)/sizeof(available_drivers[0])){
    FreeLibrary(lib);
    return false;
  }
  available_drivers[available_drivers_count++] = get_file_driver();
  return true;
}
bool unload_driver(const char *driver_path){
  // NOT IMPLEMENTED
  return false;
}

FileDriver *determine_driver_from_file_name(const char **filename_p){
  const char *filename = *filename_p;
  const char *driver_name_end = strchr(filename, ':');
  if(!driver_name_end)return NULL;
  auto type_len = driver_name_end - filename;
  if(type_len <= 0)return NULL;
  if(type_len > 64)return NULL;

  char driver_name[65] = {};
  memcpy(driver_name, filename, type_len);
  for(size_t i=0; i<available_drivers_count; i++) {
    if(stricmp(driver_name, available_drivers[i]->get_name()) == 0) {
      *filename_p += type_len + 1;
      return available_drivers[i];
    }
  }
  return NULL;
}

