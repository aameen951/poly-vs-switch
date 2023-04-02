#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "driver_api.h"

// Polymorphic object: This implementation is still polymorphic because 
// the handler function is a different pointer based on the type of the object.
// Using one function to pass the operation as data and switching on it in the driver doesn't 
// mean that this code is not polymorphic.
struct VirtualFile {
  FileDriverHandler *handler;
  void *handle;
};

FileDriverHandler *determine_driver_from_file_name(const char **filename_p);

VirtualFile *open(const char *filename) {
  VirtualFile *result = (VirtualFile *)calloc(1, sizeof(VirtualFile));
  
  result->handler = determine_driver_from_file_name(&filename);
  if(!result->handler)return NULL;

  FileDriverOperationData in_out = {};
  in_out.type = OP_TYPE_open;
  in_out.open.filename = filename;
  result->handler(&in_out);
  result->handle = in_out.open.f;

  return result;
}

void read(VirtualFile *f, void *data, size_t size){
  FileDriverOperationData in_out = {};
  in_out.type = OP_TYPE_read;
  in_out.read.f = f;
  in_out.read.data = data;
  in_out.read.size = size;
  f->handler(&in_out);
}

void write(VirtualFile *f, void *data, size_t size){
  FileDriverOperationData in_out = {};
  in_out.type = OP_TYPE_write;
  in_out.write.f = f;
  in_out.write.data = data;
  in_out.write.size = size;
  f->handler(&in_out);
}

void close(VirtualFile *f){
  FileDriverOperationData in_out = {};
  in_out.type = OP_TYPE_close;
  in_out.close.f = f;
  f->handler(&in_out);
  free(f);
}

// IRRELEVANT CODE

FileDriverHandler *available_drivers[256];
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

FileDriverHandler *determine_driver_from_file_name(const char **filename_p){
  const char *filename = *filename_p;
  const char *driver_name_end = strchr(filename, ':');
  if(!driver_name_end)return NULL;
  auto type_len = driver_name_end - filename;
  if(type_len <= 0)return NULL;
  if(type_len > 64)return NULL;

  char driver_name[65] = {};
  memcpy(driver_name, filename, type_len);
  for(size_t i=0; i<available_drivers_count; i++) {
    
    FileDriverOperationData in_out = {};
    in_out.type = OP_TYPE_get_name;
    available_drivers[i](&in_out);

    if(stricmp(driver_name, in_out.get_name.name) == 0) {
      *filename_p += type_len + 1;
      return available_drivers[i];
    }
  }
  return NULL;
}

