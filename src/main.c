#include <io.h>
#include <mmu.h>
#include <stdio.h>
#include <string.h>

int main() {
  printf("Hello, %s!\n", "world");
  printf("Decimal: %d\n", 42);
  printf("Hexadecimal: %x\n", 0xbeef);
  printf("Hexadecimal: %X\n", 0xbeef);

  return 0;
}
