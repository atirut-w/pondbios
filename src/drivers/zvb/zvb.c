#include <io.h>
#include <mmu.h>
#include <string.h>

static char *tbuff = (char *)0x8000;
static char *abuff = (char *)0x9000;
int cursor = 0;

int puts(const char *s);

void zvb_init() {
  outb(MMU_PAGE2, 0x40); // Map 0x100000 to 0x8000
  // NOTE: Do not use `memset`, doesn't work on write-only memory
  for (int i = 0; i < 80 * 40; i++) {
    tbuff[i] = ' ';
    abuff[i] = 0x07;
  }
}

int puchar_impl(int c) {
  tbuff[cursor] = c;
  abuff[cursor] = 0x07;
  cursor++;
}

int puts(const char *s) {
  char old_map = inb(MMU_PAGE2);
  outb(MMU_PAGE2, 0x40);

  while (*s) {
    puchar_impl(*s++);
  }

  outb(MMU_PAGE2, old_map);
  return 0;
}

int putchar(int c) {
  char old_map = inb(MMU_PAGE2);
  outb(MMU_PAGE2, 0x40);
  
  puchar_impl(c);

  outb(MMU_PAGE2, old_map);
}
