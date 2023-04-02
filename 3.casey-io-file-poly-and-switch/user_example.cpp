#include "user_api.h"
#include <stdio.h>



int main(int arg_count, char **args){
  if(arg_count != 2) {
    fprintf(stderr, "\n\n  Usage: user_example <driver-name>:<resource-name>\n\n");
    fprintf(stderr, "  Drivers:\n");
    fprintf(stderr, "    - HDD\n");
    fprintf(stderr, "    - SSD\n");
    fprintf(stderr, "    - BLUETOOTH\n");
    fprintf(stderr, "    - TCP\n\n");
    return 1;
  }
  
  load_driver("hdd.dll");
  load_driver("ssd.dll");
  load_driver("bluetooth.dll");
  load_driver("tcp.dll");

  {
    auto f = open(args[1]);
    if(f) {
      char data[256];
      size_t size = sizeof(data);
      read(f, data, size);
      write(f, data, size);
      close(f);
    } else {
      fprintf(stderr, "Error: failed to open file '%s'\n", args[1]);
    }
  }
}
