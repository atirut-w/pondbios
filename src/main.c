#include <io.h>
#include <string.h>

#define MMU_PAGE0 0xf0
#define MMU_PAGE1 0xf1
#define MMU_PAGE2 0xf2
#define MMU_PAGE3 0xf3

int main() {
  outb(MMU_PAGE2, 0x40); // Map 0x100000 to 0x8000
  memcpy((void *)0x8000, "Hello, World!", 13);
  memset((void *)(0x8000 + 0x1000), 0x07, 13);

  return 0;
}
