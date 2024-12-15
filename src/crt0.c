extern char _data_start__[];
extern char _data_end__[];
extern char _data_load__[];

extern char _bss_start__[];
extern char _bss_end__[];

void init_data() {
  char *src = _data_load__;
  char *dst = _data_start__;
  while (dst < _data_end__) {
    *dst++ = *src++;
  }
}

void init_bss() {
  char *dst = _bss_start__;
  while (dst < _bss_end__) {
    *dst++ = 0;
  }
}

void crt_entry() {
  init_data();
  init_bss();
}
