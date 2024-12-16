#include <string.h>

extern char _data_start__[];
extern char _data_end__[];
extern char _data_load__[];

extern char _bss_start__[];
extern char _bss_end__[];

extern int main(int argc, char **argv);

void init_data() {
  memcpy(_data_start__, _data_load__, _data_end__ - _data_start__);
}

void init_bss() {
  memset(_bss_start__, 0, _bss_end__ - _bss_start__);
}

void crt_entry() {
  init_data();
  init_bss();
  main(0, 0);
  while (1) {}
}
