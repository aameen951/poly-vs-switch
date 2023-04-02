#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <assert.h>


// NOTE: The API has to know about all the drivers by including all
// the drivers source code. More specifically it has to:
//  1. Identify each driver (in the case it is the enum).
//  2. Include the source code for all the drivers.
//  3. You can avoid including the source code by only including the headers
//     but later the linker still need to link with it.
// This is what Bob calls "dependencies". The high level code (which is 
// in this file) has to include the low level code which includes the identification
// of all the drivers (enum) and the code for all the drivers.
#include "hdd_driver.cpp"
#include "ssd_driver.cpp"
#include "tcp_driver.cpp"
#include "bluetooth_driver.cpp"

enum Driver_Type {
  DRIVER_TYPE_NONE = 0,

  DRIVER_TYPE_HDD,
  DRIVER_TYPE_SSD,
  DRIVER_TYPE_TCP,
  DRIVER_TYPE_BLUETOOTH,
};

// Switch-based implementation, no polymorphism/dispatch tables whatsoever.
struct VirtualFile {
  Driver_Type driver_type;
  union {
    HddFileObject *hdd;
    SsdFileObject *ssd;
    TcpFileObject *tcp;
    BluetoothFileObject *bluetooth;
  };
};
Driver_Type determine_driver_from_file_name(const char **filename_p);

VirtualFile *open(const char *filename) {
  VirtualFile *result = (VirtualFile *)calloc(1, sizeof(VirtualFile));
  
  result->driver_type = determine_driver_from_file_name(&filename);
  if(!result->driver_type)return NULL;

  switch(result->driver_type) {
    
    case DRIVER_TYPE_HDD: result->hdd = hdd_open(filename); break;
    case DRIVER_TYPE_SSD: result->ssd = ssd_open(filename); break;
    case DRIVER_TYPE_TCP: result->tcp = tcp_open(filename); break;
    case DRIVER_TYPE_BLUETOOTH: result->bluetooth = bluetooth_open(filename); break;

    default: assert(false);
  }

  return result;
}

void read(VirtualFile *f, void *data, size_t size){
  switch(f->driver_type) {
    
    case DRIVER_TYPE_HDD: hdd_read(f->hdd, data, size); break;
    case DRIVER_TYPE_SSD: ssd_read(f->ssd, data, size); break;
    case DRIVER_TYPE_TCP: tcp_read(f->tcp, data, size); break;
    case DRIVER_TYPE_BLUETOOTH: bluetooth_read(f->bluetooth, data, size); break;

    default: assert(false);
  }
}

void write(VirtualFile *f, void *data, size_t size){
  switch(f->driver_type) {
    
    case DRIVER_TYPE_HDD: hdd_write(f->hdd, data, size); break;
    case DRIVER_TYPE_SSD: ssd_write(f->ssd, data, size); break;
    case DRIVER_TYPE_TCP: tcp_write(f->tcp, data, size); break;
    case DRIVER_TYPE_BLUETOOTH: bluetooth_write(f->bluetooth, data, size); break;

    default: assert(false);
  }
}

void close(VirtualFile *f){
  switch(f->driver_type) {
    
    case DRIVER_TYPE_HDD: hdd_close(f->hdd); break;
    case DRIVER_TYPE_SSD: ssd_close(f->ssd); break;
    case DRIVER_TYPE_TCP: tcp_close(f->tcp); break;
    case DRIVER_TYPE_BLUETOOTH: bluetooth_close(f->bluetooth); break;

    default: assert(false);
  }
  free(f);
}

// IRRELEVANT CODE

Driver_Type determine_driver_from_file_name(const char **filename_p){
  const char *filename = *filename_p;
  const char *driver_name_end = strchr(filename, ':');
  if(!driver_name_end)return DRIVER_TYPE_NONE;
  auto type_len = driver_name_end - filename;
  if(type_len <= 0)return DRIVER_TYPE_NONE;
  if(type_len > 64)return DRIVER_TYPE_NONE;

  char driver_name[65] = {};
  memcpy(driver_name, filename, type_len);

  Driver_Type result = DRIVER_TYPE_NONE;
  if(stricmp(driver_name, "HDD") == 0) {
    result = DRIVER_TYPE_HDD;
  } else if(stricmp(driver_name, "SSD") == 0) {
    result = DRIVER_TYPE_SSD;
  } else if(stricmp(driver_name, "TCP") == 0) {
    result = DRIVER_TYPE_TCP;
  } else if(stricmp(driver_name, "BLUETOOTH") == 0) {
    result = DRIVER_TYPE_BLUETOOTH;
  }

  if(result) {
    *filename_p += type_len + 1;
  }
  return result;
}

