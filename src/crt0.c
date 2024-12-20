#include <string.h>

extern char _data_start__[];
extern char _data_end__[];
extern char _data_load__[];

extern char _bss_start__[];
extern char _bss_end__[];

extern char _initializer_start__[];
extern char _initializer_end__[];
extern char _initialized_start__[];

typedef struct {
  void (*init)();
} module_t;

extern module_t _modules_start__[];
extern module_t _modules_end__[];

extern int main(int argc, char **argv);

void init_data() {
  memcpy(_data_start__, _data_load__, _data_end__ - _data_start__);
  memcpy(_initialized_start__, _initializer_start__, _initializer_end__ - _initializer_start__);
}

void init_bss() {
  memset(_bss_start__, 0, _bss_end__ - _bss_start__);
}

void init_modules() {
  module_t *module;
  for (module = _modules_start__; module < _modules_end__; module++) {
    module->init();
  }
}

void crt_entry() {
  init_data();
  init_bss();
  init_modules();
  main(0, 0);
  while (1) {}
}
