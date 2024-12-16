#include <stddef.h>

void *memset(void *s, int c, size_t n) {
  unsigned char *p = s;
  while (n--) {
    *p++ = c;
  }
  return s;
}
